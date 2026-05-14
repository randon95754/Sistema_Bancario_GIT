#ifndef CONTA_BONUS_H
#define CONTA_BONUS_H

#include "Conta.h"

class ContaBonus : public Conta {
private:
    int pontuacao;

public:
    ContaBonus();
    ContaBonus(int numero);

    int getPontuacao();
    
    bool creditar(double valor) override;
    void receberTransferencia(double valor);
};

#endif
