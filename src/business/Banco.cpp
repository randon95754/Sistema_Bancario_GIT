#include "business/Banco.h"

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
    contas.emplace(numero, Conta(numero));
}

Conta* Banco::buscarConta(int numero) {
    if (contas.find(numero) != contas.end()) {
        return &contas[numero];
    }

    return nullptr;
}

bool Banco::transferir(int origem, int destino, double valor) {
    Conta* contaOrigem = buscarConta(origem);
    Conta* contaDestino = buscarConta(destino);

    if (contaOrigem != nullptr &&
        contaDestino != nullptr &&
        valor > 0 &&
        contaOrigem->debitar(valor)) {

        contaDestino->creditar(valor);
        return true;
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