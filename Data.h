#pragma once
#include <ctime>
#include <string>
using namespace std;

class Data {
private:
    string texto;
public:
    Data(string valor = "") : texto(valor) {}
    string getTexto() const {
         return texto; }

    static Data hoje() {
        time_t agora = time(NULL);
        tm* t = localtime(&agora);
        char s[11];
        strftime(s, sizeof(s), "%Y-%m-%d", t);
        return Data(s);
    }
};

