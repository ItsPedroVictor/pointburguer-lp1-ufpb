#pragma once
#include <string>
using namespace std;

class FichaProduto {
private:
    string categoria;
    string ingredientes;
public:
    FichaProduto(string cat = "", string ing = "") {
        categoria = cat;
        ingredientes = ing;
    }
    string getCategoria() const {
         return categoria; }

    string getIngredientes() const {
         return ingredientes; }

    void setCategoria(string cat) {
         categoria = cat; }

    void setIngredientes(string ing) {
         ingredientes = ing; }
};

