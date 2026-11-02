#pragma once
#include <iostream>
#include <vector>
#include "Data.h"
#include "ItemPedido.h"
using namespace std;

class Pedido {
private:
    int numero;
    int mesa;
    vector<ItemPedido> itens;
    bool finalizado;
    Data data;
public:
    Pedido(int n, int m, Data d = Data::hoje()) : numero(n), mesa(m), finalizado(false), data(d) {}
    int getNumero() const {
         return numero; }

    int getMesa() const {
         return mesa; }

    string getNome() const {
         return "Mesa " + to_string(mesa); }

    bool estaFinalizado() const {
         return finalizado; }

    Data getData() const {
         return data; }

    const vector<ItemPedido>& getItens() const {
         return itens; }

    void finalizar() {
         finalizado = true; }

    void adicionar(int id, string nome, int qtd, float preco) {
        for (int i = 0; i < (int)itens.size(); i++) {
            if (itens[i].getId() == id) {
                itens[i].setQuantidade(itens[i].getQuantidade() + qtd);
                return;
            }
        }
        itens.push_back(ItemPedido(id, nome, qtd, preco));
    }

    void retirar(int pos, int qtd) {
        if (pos < 0 || pos >= (int)itens.size()) return;
        int restante = itens[pos].getQuantidade() - qtd;
        if (restante <= 0) itens.erase(itens.begin() + pos);
        else itens[pos].setQuantidade(restante);
    }

    float total() const {
        float soma = 0;
        for (int i = 0; i < (int)itens.size(); i++) soma += itens[i].subtotal();
        return soma;
    }
    void exibir() const {
        cout << "\nPedido " << numero << " - " << getNome() << " (" << (finalizado ? "FINALIZADO" : "ABERTO") << ") " << data.getTexto() << endl;
        for (int i = 0; i < (int)itens.size(); i++) {
            cout << i + 1 << " - " << itens[i].getNome() << " x" << itens[i].getQuantidade() << " = R$ " << itens[i].subtotal() << endl;
        }
        cout << "TOTAL: R$ " << total() << endl;
    }
};

