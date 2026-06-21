#ifndef BANCO_H
#define BANCO_H

#include <map>
#include <string>
#include "model/Conta.h"

struct ContaInfo {
    std::string tipo;
    int numero = 0;
    double saldo = 0.0;
    int pontuacao = 0;
    bool existe = false;
};

class Banco {
private:
    std::map<int, Conta*> contas;

public:
    ~Banco();

    std::string consultarConta(int numero);
    ContaInfo consultarDadosConta(int numero);
    
    void criarConta(int numero);
    void criarConta(int numero, double saldoInicial);
    void criarContaPoupanca(int numero, double saldoInicial);
    void criarContaBonus(int numero);
    Conta* buscarConta(int numero);

    bool creditar(int numero, double valor);

    bool debitar(int numero, double valor);

    double consultarSaldo(int numero);

    bool transferir(int origem, int destino, double valor);

    bool renderJuros(int numero, double taxa);
};

#endif