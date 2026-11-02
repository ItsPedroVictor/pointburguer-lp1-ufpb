#pragma once
#include "Produto.h"
#include <iostream>

// HERANCA: Bebida tambem e um Produto.
// Esta subclasse acrescenta volume e tipo de bebida.
class Bebida : public Produto {
private:
    int volumeMl;
    std::string tipoBebida;

public:
    // Inicializa primeiro a parte herdada de Produto e depois os dados de Bebida.
    Bebida(int i, std::string n, float p, std::string des,
           FichaProduto fic, int qtd, int volume, std::string tipo)
        : Produto(i, n, p, des, fic, qtd),
          volumeMl(volume), tipoBebida(tipo) {}

    int getVolumeMl() const { return volumeMl; }
    std::string getTipoBebida() const { return tipoBebida; }

    void setVolumeMl(int volume) { volumeMl = volume; }
    void setTipoBebida(const std::string& tipo) { tipoBebida = tipo; }

    // SOBRESCRITA: mostra os atributos comuns e os dados especificos da bebida.
    void exibirDetalhes() const override {
        std::cout << "[BEBIDA] " << getNome()
                  << " | R$ " << getPreco()
                  << " | Estoque: " << getEstoque()
                  << " | Volume: " << volumeMl << " ml"
                  << " | Tipo: " << tipoBebida
                  << " | Descricao: " << getDescricao() << "\n";
    }

    // O sistema grava "B" para reconhecer uma Bebida no arquivo.
    std::string getTipo() const override { return "B"; }
};
