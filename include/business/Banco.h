#ifndef BANCO_H
#define BANCO_H

#include <map>
#include "model/Conta.h"

class Banco {
private:
    std::map<int, Conta> contas;

public:
    void criarConta(int numero, double saldoInicial);

    Conta* buscarConta(int numero);

    bool creditar(int numero, double valor);

    bool debitar(int numero, double valor);

    double consultarSaldo(int numero);

    bool transferir(int origem, int destino, double valor);
};

#endif