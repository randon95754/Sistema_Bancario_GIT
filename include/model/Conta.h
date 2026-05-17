#ifndef CONTA_H
#define CONTA_H

class Conta {
protected:
    int numero;
    double saldo;
    
public:
    Conta();
    Conta(int numero);
    Conta(int numero, double saldoInicial);
    virtual ~Conta() = default;

    int getNumero();
    double getSaldo();

    virtual bool creditar(double valor);
    virtual bool debitar(double valor);
};

#endif