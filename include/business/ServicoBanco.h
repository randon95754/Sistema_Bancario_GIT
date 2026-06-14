#ifndef SERVICO_BANCO_H
#define SERVICO_BANCO_H

#include <string>
#include "business/Banco.h"

class ServicoBanco {
public:
    virtual ~ServicoBanco() = default;

    virtual void criarConta(int numero) = 0;
    virtual void criarContaPoupanca(int numero, double saldoInicial) = 0;
    virtual void criarContaBonus(int numero) = 0;

    virtual bool creditar(int numero, double valor) = 0;
    virtual bool debitar(int numero, double valor) = 0;
    virtual bool transferir(int origem, int destino, double valor) = 0;

    virtual double consultarSaldo(int numero) = 0;
    virtual std::string consultarConta(int numero) = 0;

    // Retorna pontuação para ContaBonus, 0 para outros tipos
    virtual int obterPontuacao(int numero) = 0;
};

class ServicoBancoImpl : public ServicoBanco {
public:
    ServicoBancoImpl();
    ~ServicoBancoImpl() override;

    void criarConta(int numero) override;
    void criarContaPoupanca(int numero, double saldoInicial) override;
    void criarContaBonus(int numero) override;

    bool creditar(int numero, double valor) override;
    bool debitar(int numero, double valor) override;
    bool transferir(int origem, int destino, double valor) override;

    double consultarSaldo(int numero) override;
    std::string consultarConta(int numero) override;

    int obterPontuacao(int numero) override;

private:
    Banco repo;
};

#endif
