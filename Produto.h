#pragma once
#include <string>
#include <iostream>
#include "FichaProduto.h"

// PRODUTO: SUPERCLASSE
// Hamburguer e Bebida sao tipos especificos de Produto e herdam desta classe.
// Os atributos ficam privados para proteger os dados (encapsulamento).
class Produto {
private:
    int id;                    // Identificador unico do produto.
    std::string nome;          // Nome usado na pesquisa.
    float preco;               // Preco unitario.
    std::string descricao;     // Descricao geral do item.
    FichaProduto ficha;        // COMPOSICAO: Produto possui uma FichaProduto.
    int estoque;               // Quantidade disponivel.

public:
    // Construtor: recebe todos os dados comuns a qualquer produto.
    // A lista depois de ":" inicializa os atributos antes do corpo do construtor.
    Produto(int i, std::string n, float p, std::string des,
            FichaProduto fic, int qtd = 0)
        : id(i), nome(n), preco(p), descricao(des), ficha(fic), estoque(qtd) {}

    // Destrutor virtual: importante porque os objetos derivados sao apagados
    // por meio de ponteiros do tipo Produto*.
    virtual ~Produto() {}

    // GETTERS: permitem consultar os atributos privados.
    int getId() const { return id; }
    std::string getNome() const { return nome; }
    float getPreco() const { return preco; }
    std::string getDescricao() const { return descricao; }
    FichaProduto getFicha() const { return ficha; }
    int getEstoque() const { return estoque; }

    // SETTERS: permitem alterar os dados sem acessar os atributos diretamente.
    void setNome(const std::string& n) { nome = n; }
    void setPreco(float p) { preco = p; }
    void setDescricao(const std::string& des) { descricao = des; }
    void setFicha(const FichaProduto& fic) { ficha = fic; }
    void setEstoque(int qtd) { estoque = qtd; }

    // METODO VIRTUAL PURO:
    // A classe Produto nao define como os detalhes serao exibidos.
    // Cada subclasse e obrigada a implementar sua propria versao.
    virtual void exibirDetalhes() const = 0;

    // Retorna uma identificacao curta ("H" ou "B") para salvar o tipo no arquivo.
    // Ao carregar, o sistema usa essa identificacao para recriar a subclasse correta.
    virtual std::string getTipo() const = 0;
};
