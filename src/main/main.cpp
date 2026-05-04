#include <iostream>
#include <map>
#include "../../include/model/Conta.h"

using namespace std;

int main() {
    map<int, Conta> contas;
    int opcao;

    do {
        cout << "\n1 - Criar conta\n2 - Consultar saldo\n0 - Sair\n";
        cin >> opcao;

        int numero;

        switch (opcao) {

            case 1: {
                cout << "Digite o numero da conta: ";
                cin >> numero;

                if (numero <= 0) {
                    cout << "Numero invalido!" << endl;
                    break;
                }

                if (contas.find(numero) != contas.end()) {
                    cout << "Conta ja existe!" << endl;
                } else {
                    contas.emplace(numero, Conta(numero));
                    cout << "Conta criada com sucesso!" << endl;
                }
                break;
            }

            case 2: {
                cout << "Digite o numero da conta: ";
                cin >> numero;

                if (numero <= 0) {
                    cout << "Numero invalido!" << endl;
                    break;
                }

                auto it = contas.find(numero);

                if (it == contas.end()) {
                    cout << "Conta nao encontrada!" << endl;
                } else {
                    cout << "Saldo: " << it->second.getSaldo() << endl;
                }
                break;
            }

            case 0:
                cout << "Saindo..." << endl;
                break;

            default:
                cout << "Opcao invalida!" << endl;
        }

    } while (opcao != 0);

    return 0;
}