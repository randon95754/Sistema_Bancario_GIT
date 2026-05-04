#include <iostream>
#include "../../include/model/Conta.h"

using namespace std;

int main() {
    int numero;

    cout << "Digite o numero da conta: ";
    cin >> numero;

    if (numero <= 0) {
        cout << "Numero invalido!" << endl;
        return 1;
    }

    Conta conta(numero);

    cout << "Conta criada com sucesso!" << endl;
    cout << "Numero: " << conta.getNumero() << endl;
    cout << "Saldo: " << conta.getSaldo() << endl;

    return 0;
}