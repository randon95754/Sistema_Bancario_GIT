#include "business/ServicoBanco.h"
#include "model/ContaBonus.h"

ServicoBancoImpl::ServicoBancoImpl() {}

ServicoBancoImpl::~ServicoBancoImpl() {}

void ServicoBancoImpl::criarConta(int numero) {
    repo.criarConta(numero);
}

void ServicoBancoImpl::criarContaPoupanca(int numero, double saldoInicial) {
    repo.criarContaPoupanca(numero, saldoInicial);
}

void ServicoBancoImpl::criarContaBonus(int numero) {
    repo.criarContaBonus(numero);
}

bool ServicoBancoImpl::creditar(int numero, double valor) {
    return repo.creditar(numero, valor);
}

bool ServicoBancoImpl::debitar(int numero, double valor) {
    return repo.debitar(numero, valor);
}

bool ServicoBancoImpl::transferir(int origem, int destino, double valor) {
    return repo.transferir(origem, destino, valor);
}

double ServicoBancoImpl::consultarSaldo(int numero) {
    return repo.consultarSaldo(numero);
}

std::string ServicoBancoImpl::consultarConta(int numero) {
    return repo.consultarConta(numero);
}

bool ServicoBancoImpl::consultarDadosConta(int numero, ContaInfo& info) {
    info = repo.consultarDadosConta(numero);
    return info.existe;
}

int ServicoBancoImpl::obterPontuacao(int numero) {
    Conta* conta = repo.buscarConta(numero);
    if (!conta) return 0;
    ContaBonus* bonus = dynamic_cast<ContaBonus*>(conta);
    if (bonus) return bonus->getPontuacao();
    return 0;
}
