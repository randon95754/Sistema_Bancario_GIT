#ifndef CONTA_H
#define CONTA_H

class Conta {
private:
    int numero;
    double saldo;

public:
    Conta(int numero);

    int getNumero();
    double getSaldo();
};

#endif