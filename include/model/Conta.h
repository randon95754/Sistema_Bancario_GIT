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

    void creditar(double valor); 
    void debitar(double valor);  
    void transferir(int origem, int destino, double valor);
};

#endif