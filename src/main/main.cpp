#include <iostream>
#include "business/Banco.h"

int main() {
    Banco banco;

    // Criar contas
    banco.criarConta(1);
    banco.criarConta(2);

    // Movimentações
    banco.creditar(1, 100);
    banco.debitar(1, 30);

    // Transferência
    banco.transferir(1, 2, 40);

    // Consultar saldo
    std::cout << "Saldo conta 1: " << banco.consultarSaldo(1) << std::endl;
    std::cout << "Saldo conta 2: " << banco.consultarSaldo(2) << std::endl;

    return 0;
}
