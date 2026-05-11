#ifndef CONTA_H
#define CONTA_H

class Conta {
private:
    int numero;
    double saldo;
    
public:
    Conta();
    Conta(int numero);

    int getNumero();
    double getSaldo();

    void creditar(double valor); 
    bool debitar(double valor);  
    void transferir(int origem, int destino, double valor);
};

#endif