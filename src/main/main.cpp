#include <iostream>
#include "business/Banco.h"
#include "model/ContaBonus.h"
#include "model/ContaPoupanca.h"

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
    banco.criarContaPoupanca(10, 500); // Criar conta poupança com saldo inicial de 500

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

    // ========== TESTE CONTA BONUS ==========
    std::cout << "\n========== TESTE CONTA BONUS ==========" << std::endl;
    
    // Criar contas bonus
    banco.criarContaBonus(3);
    banco.criarContaBonus(4);
    
    // Verificar pontuacao inicial
    ContaBonus* contaBonus3 = dynamic_cast<ContaBonus*>(banco.buscarConta(3));
    std::cout << "\nConta 3 (Bonus) criada - Pontuacao inicial: " << contaBonus3->getPontuacao() << " pontos" << std::endl;
    
    // Teste 1: Deposito de 540 = 5 pontos (1 ponto por 100)
    std::cout << "\nTeste 1: Deposito de R$ 540,00 na conta 3" << std::endl;
    banco.creditar(3, 540);
    std::cout << "Saldo: R$ " << banco.consultarSaldo(3) << std::endl;
    std::cout << "Pontuacao: " << contaBonus3->getPontuacao() << " pontos (esperado: 15)" << std::endl;
    
    // Teste 2: Transferencia recebida de 540 = 2 pontos (1 ponto por 200)
    std::cout << "\nTeste 2: Transferencia de R$ 540,00 da conta 3 para conta 4" << std::endl;
    banco.transferir(3, 4, 540);
    ContaBonus* contaBonus4 = dynamic_cast<ContaBonus*>(banco.buscarConta(4));
    
    std::cout << "Saldo conta 3: R$ " << banco.consultarSaldo(3) << std::endl;
    std::cout << "Pontuacao conta 3: " << contaBonus3->getPontuacao() << " pontos" << std::endl;
    
    std::cout << "Saldo conta 4: R$ " << banco.consultarSaldo(4) << std::endl;
    std::cout << "Pontuacao conta 4: " << contaBonus4->getPontuacao() << " pontos (esperado: 12)" << std::endl;
    
    // Teste 3: Multiplos depositos
    std::cout << "\nTeste 3: Deposito de R$ 250,00 na conta 4" << std::endl;
    banco.creditar(4, 250);
    std::cout << "Saldo: R$ " << banco.consultarSaldo(4) << std::endl;
    std::cout << "Pontuacao: " << contaBonus4->getPontuacao() << " pontos (esperado: 14)" << std::endl;


    std::cout << "\n========== TESTE LIMITE NEGATIVO ==========\n" << std::endl;

banco.criarConta(50);

banco.creditar(50, 100);

if (banco.debitar(50, 900)) {
    std::cout << "Debito permitido" << std::endl;
} else {
    std::cout << "Debito bloqueado" << std::endl;
}

std::cout << "Saldo atual: "
          << banco.consultarSaldo(50)
          << std::endl;

if (banco.debitar(50, 500)) {
    std::cout << "Debito permitido" << std::endl;
} else {
    std::cout << "Debito bloqueado corretamente" << std::endl;
}

std::cout << "Saldo atual: "
          << banco.consultarSaldo(50)
          << std::endl;

    

    std::cout << "\n========== TESTE CONTA POUPANCA ==========\n" 
          << std::endl;

    ContaPoupanca poupanca(5, 200);

    poupanca.creditar(200);

    std::cout << "Saldo inicial: R$ "
          << poupanca.getSaldo()
          << std::endl;

    std::cout << "Aplicando juros de 10.5%" 
          << std::endl;

    poupanca.renderJuros(10.5);

    std::cout << "Saldo final: R$ "
          << poupanca.getSaldo()
          << std::endl;

    return 0;
}
