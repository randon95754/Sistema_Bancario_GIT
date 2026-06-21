#include <cassert>
#include <iostream>

#include "business/Banco.h"
#include "model/ContaBonus.h"
#include "model/ContaPoupanca.h"


void testarCriacaoConta() {

    Banco banco;

    banco.criarConta(1);

    assert(
        banco.buscarConta(1) != nullptr
    );

    std::cout << "OK - Criacao Conta\n";
}

void testarCredito() {

    Banco banco;

    banco.criarConta(1);

    bool resultado =
        banco.creditar(1,100);

    assert(resultado == true);

    assert(
        banco.consultarSaldo(1) == 100
    );

    std::cout << "OK - Credito\n";
}

void testarCreditoNegativo() {

    Banco banco;

    banco.criarConta(1);

    bool resultado =
        banco.creditar(1,-100);

    assert(resultado == false);

    assert(
        banco.consultarSaldo(1) == 0
    );

    std::cout << "OK - Credito Negativo\n";
}

void testarDebito() {

    Banco banco;

    banco.criarConta(1);

    banco.creditar(1,500);

    bool resultado =
        banco.debitar(1,200);

    assert(resultado == true);

    assert(
        banco.consultarSaldo(1) == 300
    );

    std::cout << "OK - Debito\n";
}


void testarLimiteNegativo() {

    Banco banco;

    banco.criarConta(1);

    banco.creditar(1,100);

    bool resultado1 =
        banco.debitar(1,900);

    assert(resultado1 == true);

    assert(
        banco.consultarSaldo(1) == -800
    );

    bool resultado2 =
        banco.debitar(1,500);

    assert(resultado2 == false);

    assert(
        banco.consultarSaldo(1) == -800
    );

    std::cout << "OK - Limite Negativo\n";
}


void testarTransferencia() {

    Banco banco;

    banco.criarConta(1);
    banco.criarConta(2);

    banco.creditar(1,500);

    bool resultado =
        banco.transferir(1,2,200);

    assert(resultado == true);

    assert(
        banco.consultarSaldo(1) == 300
    );

    assert(
        banco.consultarSaldo(2) == 200
    );

    std::cout << "OK - Transferencia\n";
}

void testarContaBonus() {

    Banco banco;

    banco.criarContaBonus(3);

    ContaBonus* conta =
        dynamic_cast<ContaBonus*>(
            banco.buscarConta(3)
        );

    banco.creditar(3,540);

    assert(
        conta->getPontuacao() == 15
    );

    std::cout << "OK - Conta Bonus\n";
}


void testarContaPoupanca() {

    ContaPoupanca conta(10,500);

    conta.renderJuros(10);

    assert(
        conta.getSaldo() == 550
    );

    std::cout << "OK - Conta Poupanca\n";
}


void testarConsultaConta() {

    Banco banco;

    banco.criarConta(1);

    std::string resultado =
        banco.consultarConta(1);

    assert(
        resultado.find("Conta") != std::string::npos
    );

    std::cout << "OK - Consulta Conta\n";
}

int main() {

    testarCriacaoConta();

    testarCredito();

    testarCreditoNegativo();

    testarDebito();

    testarLimiteNegativo();

    testarTransferencia();

    testarContaBonus();

    testarContaPoupanca();

    testarConsultaConta();

    std::cout
        << "\nTODOS OS TESTES PASSARAM\n";

    return 0;
}