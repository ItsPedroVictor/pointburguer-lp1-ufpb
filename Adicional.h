#pragma once
#include <string>
using namespace std;

class Adicional {
private:
    int id;
    string nome;
    float preco;
public:
    Adicional(int i, string n, float p) {
        id = i;
        nome = n;
        preco = p;
    }
    int getId() const {
         return id; }

    string getNome() const {
         return nome; }

    float getPreco() const {
         return preco; }

    void setNome(string n) {
         nome = n; }

    void setPreco(float p) {
         preco = p; }
};

