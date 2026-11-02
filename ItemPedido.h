#pragma once
#include <string>
using namespace std;

class ItemPedido {
private:
    int id;
    string nome;
    int quantidade;
    float preco;
public:
    ItemPedido(int i, string n, int q, float p) : id(i), nome(n), quantidade(q), preco(p) {}
    int getId() const {
         return id; }

    string getNome() const {
         return nome; }

    int getQuantidade() const {
         return quantidade; }

    float getPreco() const {
         return preco; }

    void setQuantidade(int q) {
         quantidade = q; }

    float subtotal() const {
         return quantidade * preco; }
};
