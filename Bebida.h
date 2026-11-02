#pragma once
#include <iostream>
#include "Produto.h"
using namespace std;

class Bebida : public Produto {
private:
    int volumeMl;
public:
    Bebida(int i, string n, float p, string des, FichaProduto fic, int volume) : Produto(i, n, p, des, fic), volumeMl(volume) {}
    void exibirDetalhes() const override {
        cout << getId() << " - " << getNome() << " | R$ " << getPreco() << " | " << volumeMl << " ml" << endl;
    }

    char getTipo() const override {
         return 'B'; }

    string getExtra() const override {
         return to_string(volumeMl); }
};

