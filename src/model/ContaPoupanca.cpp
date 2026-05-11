#include "model/ContaPoupanca.h"

ContaPoupanca::ContaPoupanca(int numero)
    : Conta(numero) {
}

void ContaPoupanca::renderJuros(double taxa) {

    double juros = getSaldo() * (taxa / 100.0);

    creditar(juros);
}