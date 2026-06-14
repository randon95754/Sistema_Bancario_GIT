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
    contas[numero] = new Conta(numero);
}

void Banco::criarContaBonus(int numero) {
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

void Banco::criarContaPoupanca(int numero, double saldoInicial) {
    contas[numero] = new ContaPoupanca(numero, saldoInicial);
}

std::string Banco::consultarConta(int numero) {
    Conta* conta = buscarConta(numero);

    if (conta == nullptr) {
        return "Conta nao encontrada";
    }

    std::stringstream ss;

    if (dynamic_cast<ContaBonus*>(conta)) {
        ContaBonus* bonus =
            dynamic_cast<ContaBonus*>(conta);

        ss << "Tipo: Conta Bonus\n";
        ss << "Numero: " << bonus->getNumero() << "\n";
        ss << "Saldo: " << bonus->getSaldo() << "\n";
        ss << "Pontuacao: "
           << bonus->getPontuacao();
    }
    else if (dynamic_cast<ContaPoupanca*>(conta)) {

        ss << "Tipo: Conta Poupanca\n";
        ss << "Numero: " << conta->getNumero() << "\n";
        ss << "Saldo: " << conta->getSaldo();
    }
    else {

        ss << "Tipo: Conta Simples\n";
        ss << "Numero: " << conta->getNumero() << "\n";
        ss << "Saldo: " << conta->getSaldo();
    }

    return ss.str();
}