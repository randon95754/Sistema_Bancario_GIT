#include "business/Banco.h"
#include "model/ContaBonus.h"

Banco::~Banco() {
    for (auto& pair : contas) {
        delete pair.second;
    }
    contas.clear();
}

void Banco::creditar(int numero, double valor) {
    Conta* conta = buscarConta(numero);
    if (conta != nullptr) {
        conta->creditar(valor);
    }
}

bool Banco::debitar(int numero, double valor) {
    Conta* conta = buscarConta(numero);
    if (conta != nullptr) {
        return conta->debitar(valor);
    }
    return false;
}

void Banco::criarConta(int numero) {
    contas[numero] = new Conta(numero);
}

void Banco::criarContaBonus(int numero) {
    contas[numero] = new ContaBonus(numero);
}

Conta* Banco::buscarConta(int numero) {
    if (contas.find(numero) != contas.end()) {
        return contas[numero];
    }
    return nullptr;
}

bool Banco::transferir(int origem, int destino, double valor) {
    Conta* contaOrigem = buscarConta(origem);
    Conta* contaDestino = buscarConta(destino);

    if (contaOrigem != nullptr && contaDestino != nullptr) {
        if (contaOrigem->debitar(valor)) {
            // Verifica se a conta destino é uma ContaBonus
            ContaBonus* contaBonusDestino = dynamic_cast<ContaBonus*>(contaDestino);
            if (contaBonusDestino != nullptr) {
                contaBonusDestino->receberTransferencia(valor);
            } else {
                contaDestino->creditar(valor);
            }
            return true;
        }
    }
    return false;
}


double Banco::consultarSaldo(int numero) {
    Conta* conta = buscarConta(numero);
    if (conta != nullptr) {
        return conta->getSaldo();
    }
    return 0.0;
}
