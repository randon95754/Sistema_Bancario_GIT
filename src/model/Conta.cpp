#include "model/Conta.h"

Conta::Conta() {
    numero = 0;
    saldo = 0.0;
}

Conta::Conta(int numero) {
    this->numero = numero;
    this->saldo = 0.0;
}

int Conta::getNumero() {
    return numero;
}

double Conta::getSaldo() {
    return saldo;
}

void Conta::creditar(double valor) {
    saldo += valor;
}

void Conta::debitar(double valor) {
    saldo -= valor;
}
