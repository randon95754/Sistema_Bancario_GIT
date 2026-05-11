#ifndef BANCO_H
#define BANCO_H

#include <map>
#include "model/Conta.h"

class Banco {
private:
    std::map<int, Conta*> contas;

public:
    ~Banco();
    
    void criarConta(int numero);
    void criarContaBonus(int numero);
    Conta* buscarConta(int numero);

    void creditar(int numero, double valor);
    bool debitar(int numero, double valor);

    double consultarSaldo(int numero);

    bool transferir(int origem, int destino, double valor);
};

#endif
