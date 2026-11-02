#pragma once
#include <string>
#include "FichaProduto.h"
using namespace std;

class Produto {
private:
    int id;
    string nome;
    float preco;
    string descricao;
    FichaProduto ficha;
public:
    Produto(int i, string n, float p, string des, FichaProduto fic) : id(i), nome(n), preco(p), descricao(des), ficha(fic) {}
    int getId() const {
         return id; }

    string getNome() const {
         return nome; }

    float getPreco() const {
         return preco; }

    string getDescricao() const {
         return descricao; }

    FichaProduto getFicha() const {
         return ficha; }

    void setNome(string n) {
         nome = n; }

    void setPreco(float p) {
         preco = p; }

    void setDescricao(string des) {
         descricao = des; }

    virtual void exibirDetalhes() const = 0;
    virtual char getTipo() const = 0;
    virtual string getExtra() const = 0;
    virtual ~Produto() {}
};

