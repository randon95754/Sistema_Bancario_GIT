#include "business/Banco.h"

void Banco::creditar(int numero, double valor) {
    Conta* conta = buscarConta(numero);
    if (conta != nullptr) {
        conta->creditar(valor);
    }
}

void Banco::debitar(int numero, double valor) {
    Conta* conta = buscarConta(numero);
    if (conta != nullptr) {
        conta->debitar(valor);
    }
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


double Banco::consultarSaldo(int numero) {
    Conta* conta = buscarConta(numero);
    if (conta != nullptr) {
        return conta->getSaldo();
    }
    return 0.0;
}
