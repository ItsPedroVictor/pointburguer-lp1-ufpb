#pragma once
#include "Produto.h"
#include "Adicional.h"
#include <vector>
#include <iostream>

// HERANCA: Hamburguer e um tipo de Produto.
// Ele recebe os atributos comuns da superclasse e acrescenta dados proprios.
class Hamburguer : public Produto {
private:
    std::string tipoPao;
    std::vector<Adicional> adicionais; // Um hamburguer pode ter varios adicionais.

public:
    // Primeiro chama o construtor de Produto; depois inicializa tipoPao.
    Hamburguer(int i, std::string n, float p, std::string des,
               FichaProduto fic, int qtd, std::string pao)
        : Produto(i, n, p, des, fic, qtd), tipoPao(pao) {}

    std::string getTipoPao() const { return tipoPao; }
    void setTipoPao(const std::string& pao) { tipoPao = pao; }

    // push_back adiciona um adicional ao final do vetor de adicionais.
    void adicionarAdicional(const Adicional& a) { adicionais.push_back(a); }

    // Retorna uma referencia constante: permite consultar a lista sem copia-la
    // e sem permitir que quem recebeu a referencia altere o vetor.
    const std::vector<Adicional>& getAdicionais() const { return adicionais; }

    // POLIMORFISMO / SOBRESCRITA:
    // Esta funcao tem a mesma assinatura da funcao virtual de Produto,
    // mas mostra tambem as informacoes especificas de um hamburguer.
    void exibirDetalhes() const override {
        std::cout << "[HAMBURGUER] " << getNome()
                  << " | R$ " << getPreco()
                  << " | Estoque: " << getEstoque()
                  << " | Pao: " << tipoPao
                  << " | Categoria: " << getFicha().getCategoria()
                  << " | Ingredientes: " << getFicha().getIngredientes()
                  << " | Descricao: " << getDescricao() << "\n";

        // Percorre o vetor e mostra os adicionais disponiveis.
        if (!adicionais.empty()) {
            std::cout << "  Adicionais disponiveis: ";
            for (std::size_t i = 0; i < adicionais.size(); ++i) {
                std::cout << adicionais[i].getNome()
                          << " (R$ " << adicionais[i].getPreco() << ")";
                if (i + 1 < adicionais.size()) std::cout << ", ";
            }
            std::cout << "\n";
        }
    }

    // O sistema grava "H" no arquivo para reconhecer um Hamburguer.
    std::string getTipo() const override { return "H"; }
};
