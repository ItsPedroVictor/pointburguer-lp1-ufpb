#pragma once
#include <iostream>
#include "Produto.h"
using namespace std;

class Hamburguer : public Produto {
private:
    string tipoPao;
public:
    Hamburguer(int i, string n, float p, string des, FichaProduto fic, string pao) : Produto(i, n, p, des, fic), tipoPao(pao) {}

    void exibirDetalhes() const override {
        cout << getId() << " - " << getNome() << " | R$ " << getPreco() << " | Pao: " << tipoPao << endl;
    }

    char getTipo() const override {
         return 'H'; }

    string getExtra() const override { return tipoPao; }
};

