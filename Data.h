#pragma once
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

// COMPOSICAO: cada pedido tem uma Data propria.
class Data {
private:
    int dia, mes, ano;
public:
    Data(int d = 1, int m = 1, int a = 2026) : dia(d), mes(m), ano(a) {}
    static Data hoje() {
        std::time_t agora = std::time(NULL);
        std::tm* t = std::localtime(&agora);
        return Data(t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
    }
    std::string texto() const {
        std::ostringstream s;
        s << std::setfill('0') << std::setw(4) << ano << '-'
          << std::setw(2) << mes << '-' << std::setw(2) << dia;
        return s.str();
    }
    static Data ler(const std::string& s) {
        int a=0,m=0,d=0;
        char traco1, traco2;
        std::istringstream in(s);
        if (!(in >> a >> traco1 >> m >> traco2 >> d) || traco1 != '-' || traco2 != '-' || a < 2000 || m < 1 || m > 12 || d < 1 || d > 31)
            return Data::hoje();
        return Data(d,m,a);
    }
};
