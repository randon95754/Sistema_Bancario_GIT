#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#error REST server currently supported only on Windows.
#endif

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include "business/ServicoBanco.h"

static bool startsWith(const std::string& text, const std::string& prefix) {
    return text.rfind(prefix, 0) == 0;
}

static std::string readRequest(SOCKET client) {
    std::string request;
    char buffer[4096];
    size_t totalBytes = 0;

    while (true) {
        int bytesReceived = recv(client, buffer, static_cast<int>(sizeof(buffer)), 0);
        if (bytesReceived <= 0) {
            break;
        }
        request.append(buffer, bytesReceived);
        totalBytes += static_cast<size_t>(bytesReceived);

        size_t headerEnd = request.find("\r\n\r\n");
        if (headerEnd == std::string::npos) {
            if (totalBytes >= 65536) {
                break;
            }
            continue;
        }

        std::string headers = request.substr(0, headerEnd);
        std::string lowerHeaders = headers;
        std::transform(lowerHeaders.begin(), lowerHeaders.end(), lowerHeaders.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

        size_t contentLength = 0;
        size_t pos = lowerHeaders.find("content-length:");
        if (pos != std::string::npos) {
            pos += strlen("content-length:");
            while (pos < lowerHeaders.size() && std::isspace(static_cast<unsigned char>(lowerHeaders[pos]))) {
                pos++;
            }
            size_t end = pos;
            while (end < lowerHeaders.size() && std::isdigit(static_cast<unsigned char>(lowerHeaders[end]))) {
                end++;
            }
            if (end > pos) {
                try {
                    contentLength = std::stoul(lowerHeaders.substr(pos, end - pos));
                } catch (...) {
                    contentLength = 0;
                }
            }
        }

        size_t bodyStart = headerEnd + 4;
        if (request.size() >= bodyStart + contentLength) {
            break;
        }

        if (totalBytes >= 65536) {
            break;
        }
    }

    return request;
}

static void sendAll(SOCKET client, const std::string& data) {
    size_t totalSent = 0;
    while (totalSent < data.size()) {
        int sent = send(client, data.c_str() + totalSent, static_cast<int>(data.size() - totalSent), 0);
        if (sent == SOCKET_ERROR || sent == 0) {
            break;
        }
        totalSent += sent;
    }
}

static void sendResponse(SOCKET client, const std::string& status, const std::string& body, const std::string& contentType = "application/json") {
    std::ostringstream response;
    response << "HTTP/1.1 " << status << "\r\n";
    response << "Content-Type: " << contentType << "\r\n";
    response << "Content-Length: " << body.size() << "\r\n";
    response << "Connection: close\r\n";
    response << "\r\n";
    response << body;
    sendAll(client, response.str());
}

static std::string toJson(const ContaInfo& info) {
    std::ostringstream out;
    out << "{";
    out << "\"tipo\":\"" << info.tipo << "\",";
    out << "\"numero\":" << info.numero << ",";
    out << "\"saldo\":" << info.saldo << ",";
    out << "\"pontuacao\":" << info.pontuacao;
    out << "}";
    return out.str();
}

static int extractJsonInt(const std::string& body, const std::string& key, int defaultValue = 0) {
    std::string marker = "\"" + key + "\"";
    size_t pos = body.find(marker);
    if (pos == std::string::npos) {
        return defaultValue;
    }
    size_t colon = body.find(':', pos + marker.size());
    if (colon == std::string::npos) {
        return defaultValue;
    }
    size_t start = colon + 1;
    while (start < body.size() && std::isspace(static_cast<unsigned char>(body[start]))) {
        start++;
    }
    size_t end = start;
    while (end < body.size() && (std::isdigit(static_cast<unsigned char>(body[end])) || body[end] == '-' || body[end] == '.')) {
        end++;
    }
    if (start >= end) {
        return defaultValue;
    }
    try {
        return std::stoi(body.substr(start, end - start));
    } catch (...) {
        return defaultValue;
    }
}

static double extractJsonDouble(const std::string& body, const std::string& key, double defaultValue = 0.0) {
    std::string marker = "\"" + key + "\"";
    size_t pos = body.find(marker);
    if (pos == std::string::npos) {
        return defaultValue;
    }
    size_t colon = body.find(':', pos + marker.size());
    if (colon == std::string::npos) {
        return defaultValue;
    }
    size_t start = colon + 1;
    while (start < body.size() && std::isspace(static_cast<unsigned char>(body[start]))) {
        start++;
    }
    size_t end = start;
    while (end < body.size() && (std::isdigit(static_cast<unsigned char>(body[end])) || body[end] == '-' || body[end] == '.')) {
        end++;
    }
    if (start >= end) {
        return defaultValue;
    }
    try {
        return std::stod(body.substr(start, end - start));
    } catch (...) {
        return defaultValue;
    }
}

static std::string extractJsonString(const std::string& body, const std::string& key, const std::string& defaultValue = "") {
    std::string marker = "\"" + key + "\"";
    size_t pos = body.find(marker);
    if (pos == std::string::npos) {
        return defaultValue;
    }
    size_t colon = body.find(':', pos + marker.size());
    if (colon == std::string::npos) {
        return defaultValue;
    }
    size_t start = body.find('"', colon + 1);
    if (start == std::string::npos) {
        return defaultValue;
    }
    size_t end = body.find('"', start + 1);
    if (end == std::string::npos) {
        return defaultValue;
    }
    return body.substr(start + 1, end - start - 1);
}

static bool parseContaPath(const std::string& path, int& numero, std::string& action) {
    const std::string prefix = "/banco/conta";
    if (!startsWith(path, prefix)) {
        return false;
    }

    std::string tail = path.substr(prefix.size());
    if (tail.empty()) {
        return false;
    }

    if (tail[0] == '/') {
        tail = tail.substr(1);
    }

    size_t query = tail.find('?');
    if (query != std::string::npos) {
        tail = tail.substr(0, query);
    }

    if (tail.empty()) {
        return false;
    }

    size_t slash = tail.find('/');
    std::string numeroPart = (slash == std::string::npos) ? tail : tail.substr(0, slash);
    if (numeroPart.empty()) {
        return false;
    }

    try {
        numero = std::stoi(numeroPart);
    } catch (...) {
        return false;
    }

    if (slash == std::string::npos) {
        action.clear();
    } else {
        action = tail.substr(slash + 1);
    }

    return true;
}

int main() {
    Banco banco;

    // Criar contas com saldo inicial
    banco.criarConta(1, 100.0);
    banco.criarConta(2, 50.0);

    // Movimentações
    banco.creditar(1, 100);
    banco.debitar(1, 30);

    // Transferência
    banco.transferir(1, 2, 40);

    // Consultar saldo
    std::cout << "Saldo conta 1: " << banco.consultarSaldo(1) << std::endl;
    std::cout << "Saldo conta 2: " << banco.consultarSaldo(2) << std::endl;

    // Teste: tentar debitar mais do que o saldo
    std::cout << "\nTentando debitar 200 da conta 1 (saldo atual: " << banco.consultarSaldo(1) << ")" << std::endl;
    if (banco.debitar(1, 200)) {
        std::cout << "Debito realizado com sucesso." << std::endl;
    } else {
        std::cout << "Falha: saldo insuficiente para debito." << std::endl;
    }
    std::cout << "Saldo conta 1 apos tentativa: " << banco.consultarSaldo(1) << std::endl;

    // Teste: tentar transferir mais do que o saldo
    std::cout << "\nTentando transferir 100 da conta 1 para conta 2 (saldo conta 1: " << banco.consultarSaldo(1) << ")" << std::endl;
    if (banco.transferir(1, 2, 100)) {
        std::cout << "Transferencia realizada com sucesso." << std::endl;
    } else {
        std::cout << "Falha: saldo insuficiente para transferencia." << std::endl;
    }
    std::cout << "Saldo conta 1: " << banco.consultarSaldo(1) << std::endl;
    std::cout << "Saldo conta 2: " << banco.consultarSaldo(2) << std::endl;

    // ========== TESTE CONTA BONUS ==========
    std::cout << "\n========== TESTE CONTA BONUS ==========" << std::endl;
    
    // Criar contas bonus
    banco.criarContaBonus(3);
    banco.criarContaBonus(4);
    
    // Verificar pontuacao inicial
    ContaBonus* contaBonus3 = dynamic_cast<ContaBonus*>(banco.buscarConta(3));
    std::cout << "\nConta 3 (Bonus) criada - Pontuacao inicial: " << contaBonus3->getPontuacao() << " pontos" << std::endl;
    
    // Teste 1: Deposito de 540 = 5 pontos (1 ponto por 100)
    std::cout << "\nTeste 1: Deposito de R$ 540,00 na conta 3" << std::endl;
    banco.creditar(3, 540);
    std::cout << "Saldo: R$ " << banco.consultarSaldo(3) << std::endl;
    std::cout << "Pontuacao: " << contaBonus3->getPontuacao() << " pontos (esperado: 15)" << std::endl;
    
    // Teste 2: Transferencia recebida de 540 = 2 pontos (1 ponto por 200)
    std::cout << "\nTeste 2: Transferencia de R$ 540,00 da conta 3 para conta 4" << std::endl;
    banco.transferir(3, 4, 540);
    ContaBonus* contaBonus4 = dynamic_cast<ContaBonus*>(banco.buscarConta(4));
    
    std::cout << "Saldo conta 3: R$ " << banco.consultarSaldo(3) << std::endl;
    std::cout << "Pontuacao conta 3: " << contaBonus3->getPontuacao() << " pontos" << std::endl;
    
    std::cout << "Saldo conta 4: R$ " << banco.consultarSaldo(4) << std::endl;
    std::cout << "Pontuacao conta 4: " << contaBonus4->getPontuacao() << " pontos (esperado: 12)" << std::endl;
    
    // Teste 3: Multiplos depositos
    std::cout << "\nTeste 3: Deposito de R$ 250,00 na conta 4" << std::endl;
    banco.creditar(4, 250);
    std::cout << "Saldo: R$ " << banco.consultarSaldo(4) << std::endl;
    std::cout << "Pontuacao: " << contaBonus4->getPontuacao() << " pontos (esperado: 14)" << std::endl;



    std::cout << "\n========== TESTE CONTA POUPANCA ==========\n" 
          << std::endl;

    ContaPoupanca poupanca(5);

    poupanca.creditar(200);

    std::cout << "Saldo inicial: R$ "
          << poupanca.getSaldo()
          << std::endl;

    std::cout << "Aplicando juros de 10.5%" 
          << std::endl;

    poupanca.renderJuros(10.5);

    std::cout << "Saldo final: R$ "
          << poupanca.getSaldo()
          << std::endl;
    return 0;
}
