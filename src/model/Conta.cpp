#include "../../include/model/Conta.h"

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