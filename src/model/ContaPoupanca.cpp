#include "model/ContaPoupanca.h"

ContaPoupanca::ContaPoupanca(int numero, double saldoInicial)
    : Conta(numero) {
        saldo = saldoInicial;
}

void ContaPoupanca::renderJuros(double taxa) {

    double juros = getSaldo() * (taxa / 100.0);

    creditar(juros);
}