#ifndef BANCO_H
#define BANCO_H

#include <map>
#include "model/Conta.h"

class Banco {
private:
    std::map<int, Conta> contas;

public:
    void criarConta(int numero);
    Conta* buscarConta(int numero);

    void creditar(int numero, double valor);
    void debitar(int numero, double valor);

    double consultarSaldo(int numero);

    void transferir(int origem, int destino, double valor);
};

#endif
