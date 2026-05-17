#include "model/Conta.h"

Conta::Conta() {
    numero = 0;
    saldo = 0.0;
}

Conta::Conta(int numero) {
    this->numero = numero;
    this->saldo = 0.0;
}

Conta::Conta(int numero, double saldoInicial) {
    this->numero = numero;
    this->saldo = saldoInicial;
}

int Conta::getNumero() {
    return numero;
}

double Conta::getSaldo() {
    return saldo;
}

bool Conta::creditar(double valor) {
    if (valor > 0) {
        saldo += valor;
        return true;
    }

    return false;
}

bool Conta::debitar(double valor) {
    if (valor > 0 && saldo >= valor) {
        saldo -= valor;
        return true;
    }

    return false;
}