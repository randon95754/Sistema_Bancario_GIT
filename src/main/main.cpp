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

static bool parseAccountNumber(const std::string& path, int& numero) {
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
        size_t query = tail.find('?');
        if (query != std::string::npos) {
            tail = tail.substr(0, query);
        }
        if (tail.empty()) {
            return false;
        }
        try {
            numero = std::stoi(tail);
            return true;
        } catch (...) {
            return false;
        }
    }
    if (tail[0] == '?') {
        size_t pos = tail.find("numero=");
        if (pos == std::string::npos) {
            return false;
        }
        std::string value = tail.substr(pos + 7);
        size_t end = value.find('&');
        if (end != std::string::npos) {
            value = value.substr(0, end);
        }
        try {
            numero = std::stoi(value);
            return true;
        } catch (...) {
            return false;
        }
    }
    return false;
}

int main() {
    ServicoBancoImpl banco;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Falha ao inicializar Winsock." << std::endl;
        return 1;
    }

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "Falha ao criar socket." << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(8080);

    if (bind(listenSocket, reinterpret_cast<sockaddr*>(&service), sizeof(service)) == SOCKET_ERROR) {
        std::cerr << "Falha ao associar o socket na porta 8080." << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Falha ao escutar conexoes." << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Servidor REST ativo em http://localhost:8080" << std::endl;
    std::cout << "POST /banco/conta/   - cria conta" << std::endl;
    std::cout << "GET  /banco/conta/{numero} - consulta conta" << std::endl;

    while (true) {
        SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            continue;
        }

        std::string request = readRequest(clientSocket);
        if (request.empty()) {
            closesocket(clientSocket);
            continue;
        }

        std::istringstream requestStream(request);
        std::string requestLine;
        std::getline(requestStream, requestLine);
        if (!requestLine.empty() && requestLine.back() == '\r') {
            requestLine.pop_back();
        }

        std::istringstream lineStream(requestLine);
        std::string method;
        std::string path;
        std::string version;
        lineStream >> method >> path >> version;

        std::string responseBody;
        std::string status;

        size_t bodyPos = request.find("\r\n\r\n");
        std::string body;
        if (bodyPos != std::string::npos) {
            body = request.substr(bodyPos + 4);
        }

        std::cout << "[DEBUG] rawRequest=" << request << std::endl;
        std::cout << "[DEBUG] requestLine='" << requestLine << "'" << std::endl;
        std::cout << "[DEBUG] path='" << path << "' method='" << method << "' body='" << body << "'" << std::endl;

        if (method == "GET" && startsWith(path, "/banco/conta")) {
            int numero;
            if (!parseAccountNumber(path, numero)) {
                status = "400 Bad Request";
                responseBody = "{\"error\":\"numero invalido\"}";
            } else {
                ContaInfo info;
                if (!banco.consultarDadosConta(numero, info)) {
                    status = "404 Not Found";
                    responseBody = "{\"error\":\"Conta nao encontrada\"}";
                } else {
                    status = "200 OK";
                    responseBody = toJson(info);
                }
            }
        } else if (method == "POST" && (path == "/banco/conta" || path == "/banco/conta/")) {
            int numero = extractJsonInt(body, "numero", -1);
            if (numero <= 0) {
                status = "400 Bad Request";
                responseBody = "{\"error\":\"numero invalido\"}";
            } else {
                std::string tipo = extractJsonString(body, "tipo", "simples");
                std::transform(tipo.begin(), tipo.end(), tipo.begin(), [](unsigned char c) { return std::tolower(c); });

                if (tipo == "poupanca") {
                    double saldoInicial = extractJsonDouble(body, "saldoInicial", 0.0);
                    banco.criarContaPoupanca(numero, saldoInicial);
                } else if (tipo == "bonus") {
                    banco.criarContaBonus(numero);
                } else {
                    banco.criarConta(numero);
                }

                std::ostringstream out;
                out << "{\"status\":\"created\",\"numero\":" << numero << "}";
                status = "201 Created";
                responseBody = out.str();
            }
        } else {
            status = "404 Not Found";
            responseBody = "{\"error\":\"Endpoint nao encontrado\"}";
        }

        sendResponse(clientSocket, status, responseBody);
        closesocket(clientSocket);
    }

    closesocket(listenSocket);
    WSACleanup();
    return 0;
}
