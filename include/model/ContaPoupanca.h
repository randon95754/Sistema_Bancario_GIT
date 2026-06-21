#ifndef CONTAPOUPANCA_H
#define CONTAPOUPANCA_H

#include "model/Conta.h"

class ContaPoupanca : public Conta {

public:

    ContaPoupanca(int numero, double saldoInicial);

    void renderJuros(double taxa);
};

#endif