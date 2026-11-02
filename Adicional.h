#pragma once
#include <string>

// ADICIONAL
// Representa algo que pode ser acrescentado a um hamburguer.
// Adicional e uma classe independente: nao herda de Produto.
class Adicional {
private:
    int id;
    std::string nome;
    float preco;

public:
    // O construtor inicializa os tres atributos do adicional.
    Adicional(int i = 0, std::string n = "", float p = 0.0f)
        : id(i), nome(n), preco(p) {}

    // Getters: consultam os dados.
    int getId() const { return id; }
    std::string getNome() const { return nome; }
    float getPreco() const { return preco; }

    // Setters: modificam nome e preco.
    void setNome(const std::string& n) { nome = n; }
    void setPreco(float p) { preco = p; }
};
