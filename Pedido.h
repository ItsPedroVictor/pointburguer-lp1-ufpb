#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include "Data.h"
#include "ItemPedido.h"

// OBJETO PRINCIPAL: 5 atributos privados, incluindo Data e vetor de ItemPedido.
class Pedido {
private:
    int numero;
    int mesa;
    std::vector<ItemPedido> itens;
    bool finalizado;
    Data dataPedido;
public:
    Pedido(int n = 0, int m = 1, Data d = Data::hoje())
        : numero(n), mesa(m), finalizado(false), dataPedido(d) {}
    int getNumero() const { return numero; }
    int getMesa() const { return mesa; }
    std::string getNome() const { return "Mesa " + std::to_string(mesa); }
    bool estaFinalizado() const { return finalizado; }
    Data getData() const { return dataPedido; }
    const std::vector<ItemPedido>& getItens() const { return itens; }
    void finalizar() { finalizado = true; }
    double total() const {
        double soma=0;
        for (std::size_t i=0; i<itens.size(); ++i) soma += itens[i].subtotal();
        return soma;
    }
    void adicionar(int id, const std::string& nome, int quantidade, double preco) {
        for (std::size_t i=0; i<itens.size(); ++i) {
            if (itens[i].getIdProduto() == id) {
                itens[i].setQuantidade(itens[i].getQuantidade() + quantidade);
                return;
            }
        }
        itens.push_back(ItemPedido(id,nome,quantidade,preco));
    }
    bool retirar(int pos, int quantidade) {
        if (pos < 0 || pos >= static_cast<int>(itens.size()) || quantidade < 1) return false;
        int restante = itens[pos].getQuantidade() - quantidade;
        if (restante <= 0) itens.erase(itens.begin() + pos);
        else itens[pos].setQuantidade(restante);
        return true;
    }
    void exibir() const {
        std::cout << "\nPedido #" << numero << " - " << getNome()
                  << " | " << (finalizado ? "FINALIZADO" : "ABERTO")
                  << " | Data: " << dataPedido.texto() << "\n";
        if (itens.empty()) std::cout << "  Nenhum item.\n";
        for (std::size_t i=0; i<itens.size(); ++i) {
            std::cout << "  " << i+1 << ". " << itens[i].getNome()
                      << " | Qtd: " << itens[i].getQuantidade()
                      << " | Unitario: R$ " << itens[i].getPrecoUnitario()
                      << " | Subtotal: R$ " << itens[i].subtotal() << "\n";
        }
        std::cout << "  TOTAL: R$ " << total() << "\n";
    }
};
