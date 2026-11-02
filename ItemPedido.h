#pragma once
#include <string>

// Uma linha do pedido: copia nome e preco no momento da venda.
// Assim uma venda antiga nao muda se o cardapio mudar depois.
class ItemPedido {
private:
    int idProduto;
    std::string nome;
    int quantidade;
    double precoUnitario;
public:
    ItemPedido(int id = 0, std::string n = "", int q = 0, double p = 0)
        : idProduto(id), nome(n), quantidade(q), precoUnitario(p) {}
    int getIdProduto() const { return idProduto; }
    std::string getNome() const { return nome; }
    int getQuantidade() const { return quantidade; }
    double getPrecoUnitario() const { return precoUnitario; }
    double subtotal() const { return quantidade * precoUnitario; }
    void setQuantidade(int q) { quantidade = q; }
};
