#include "model/ContaBonus.h"

ContaBonus::ContaBonus() : Conta() {
    pontuacao = 10;
}

ContaBonus::ContaBonus(int numero) : Conta(numero) {
    pontuacao = 10;
}

int ContaBonus::getPontuacao() {
    return pontuacao;
}

// Depositar dinheiro na conta e ganhar pontos
void ContaBonus::creditar(double valor) {
    Conta::creditar(valor);
    // 1 ponto para cada R$ 100,00 de depósito
    int pontosGanhos = (int)(valor / 100.0);
    pontuacao += pontosGanhos;
}

//Receber Transferencia e ganhar pontos
void ContaBonus::receberTransferencia(double valor) {
    Conta::creditar(valor);
    // 1 ponto para cada R$ 200,00 recebidos em transferência
    int pontosGanhos = (int)(valor / 200.0);
    pontuacao += pontosGanhos;
}
