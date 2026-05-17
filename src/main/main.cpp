#include <iostream>
#include "business/Banco.h"

int main() {
    Banco banco;

    // Criar contas com saldo inicial
    banco.criarConta(1, 100.0);
    banco.criarConta(2, 50.0);

    // Movimentações
    banco.creditar(1, 100);
    banco.debitar(1, 30);

    // Transferência
    banco.transferir(1, 2, 40);

    // Consultar saldo
    std::cout << "Saldo conta 1: " << banco.consultarSaldo(1) << std::endl;
    std::cout << "Saldo conta 2: " << banco.consultarSaldo(2) << std::endl;

    // Teste: tentar debitar mais do que o saldo
    std::cout << "\nTentando debitar 200 da conta 1 (saldo atual: " << banco.consultarSaldo(1) << ")" << std::endl;
    if (banco.debitar(1, 200)) {
        std::cout << "Debito realizado com sucesso." << std::endl;
    } else {
        std::cout << "Falha: saldo insuficiente para debito." << std::endl;
    }
    std::cout << "Saldo conta 1 apos tentativa: " << banco.consultarSaldo(1) << std::endl;

    // Teste: tentar transferir mais do que o saldo
    std::cout << "\nTentando transferir 100 da conta 1 para conta 2 (saldo conta 1: " << banco.consultarSaldo(1) << ")" << std::endl;
    if (banco.transferir(1, 2, 100)) {
        std::cout << "Transferencia realizada com sucesso." << std::endl;
    } else {
        std::cout << "Falha: saldo insuficiente para transferencia." << std::endl;
    }
    std::cout << "Saldo conta 1: " << banco.consultarSaldo(1) << std::endl;
    std::cout << "Saldo conta 2: " << banco.consultarSaldo(2) << std::endl;

    return 0;
}
