#include "business/Banco.h"
#include <sstream>
#include "model/ContaBonus.h"
#include "model/ContaPoupanca.h"

Banco::~Banco() {
    for (auto& pair : contas) {
        delete pair.second;
    }
    contas.clear();
}

bool Banco::creditar(int numero, double valor) {
    Conta* conta = buscarConta(numero);

    if (conta != nullptr) {
        return conta->creditar(valor);
    }

    return false;
}

bool Banco::debitar(int numero, double valor) {
    Conta* conta = buscarConta(numero);

    if (conta != nullptr) {
        return conta->debitar(valor);
    }

    return false;
}

void Banco::criarConta(int numero) {
    auto it = contas.find(numero);
    if (it != contas.end()) {
        delete it->second;
    }
    contas[numero] = new Conta(numero);
}

void Banco::criarContaBonus(int numero) {
    auto it = contas.find(numero);
    if (it != contas.end()) {
        delete it->second;
    }
    contas[numero] = new ContaBonus(numero);
}

Conta* Banco::buscarConta(int numero) {
    if (contas.find(numero) != contas.end()) {
        return contas[numero];
    }

    return nullptr;
}

bool Banco::transferir(int origem, int destino, double valor) {
    Conta* contaOrigem = buscarConta(origem);
    Conta* contaDestino = buscarConta(destino);

    if (contaOrigem != nullptr && contaDestino != nullptr) {
        if (contaOrigem->debitar(valor)) {
            // Verifica se a conta destino é uma ContaBonus
            ContaBonus* contaBonusDestino = dynamic_cast<ContaBonus*>(contaDestino);
            if (contaBonusDestino != nullptr) {
                contaBonusDestino->receberTransferencia(valor);
            } else {
                contaDestino->creditar(valor);
            }
            return true;
        }
    }

    return false;
}

double Banco::consultarSaldo(int numero) {
    Conta* conta = buscarConta(numero);

    if (conta != nullptr) {
        return conta->getSaldo();
    }

    return 0.0;
}

ContaInfo Banco::consultarDadosConta(int numero) {
    ContaInfo info;
    Conta* conta = buscarConta(numero);

    if (conta == nullptr) {
        return info;
    }

    info.existe = true;
    info.numero = conta->getNumero();
    info.saldo = conta->getSaldo();

    if (auto bonus = dynamic_cast<ContaBonus*>(conta)) {
        info.tipo = "Conta Bonus";
        info.pontuacao = bonus->getPontuacao();
    }
    else if (dynamic_cast<ContaPoupanca*>(conta)) {
        info.tipo = "Conta Poupanca";
    }
    else {
        info.tipo = "Conta Simples";
    }

    return info;
}

void Banco::criarContaPoupanca(int numero, double saldoInicial) {
    auto it = contas.find(numero);
    if (it != contas.end()) {
        delete it->second;
    }
    contas[numero] = new ContaPoupanca(numero, saldoInicial);
}

std::string Banco::consultarConta(int numero) {
    ContaInfo info = consultarDadosConta(numero);

    if (!info.existe) {
        return "Conta nao encontrada";
    }

    std::stringstream ss;
    ss << "Tipo: " << info.tipo << "\n";
    ss << "Numero: " << info.numero << "\n";
    ss << "Saldo: " << info.saldo;

    if (info.tipo == "Conta Bonus") {
        ss << "\nPontuacao: " << info.pontuacao;
    }

    return ss.str();
}
