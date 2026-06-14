#ifndef BANCO_H
#define BANCO_H

#include <map>
#include <string>
#include "model/Conta.h"

class Banco {
private:
    std::map<int, Conta*> contas;

public:
    ~Banco();

    std::string consultarConta(int numero);
    
    void criarConta(int numero);

    void criarContaPoupanca(int numero, double saldoInicial);

    void criarContaBonus(int numero);
    Conta* buscarConta(int numero);

    bool creditar(int numero, double valor);

    bool debitar(int numero, double valor);

    double consultarSaldo(int numero);

    bool transferir(int origem, int destino, double valor);

    
};

#endif