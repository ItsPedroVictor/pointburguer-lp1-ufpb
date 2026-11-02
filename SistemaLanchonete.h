#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
#include <limits>
#include <cctype>
#include "Hamburguer.h"
#include "Bebida.h"
#include "Adicional.h"
#include "Pedido.h"
using namespace std;

class SistemaLanchonete {
private:
    vector<Produto*> produtos;
    vector<Adicional> adicionais;
    vector<Pedido> pedidos;
    int proximoPedido;
    string arquivo;

    int lerNumero(string pergunta, int minimo, int maximo) const {
        int numero;
        while (true) {
            cout << pergunta;
            if (cin >> numero && numero >= minimo && numero <= maximo) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return numero;
            }
            cout << "Opcao invalida.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    vector<string> separar(string linha) const {
        vector<string> campos;
        string campo;
        stringstream s(linha);
        while (getline(s, campo, '|')) campos.push_back(campo);
        return campos;
    }
    void criarCardapio() {
        produtos.push_back(new Hamburguer(1, "X-Salada", 13, "Hamburguer", FichaProduto("Hamburguer", "Pao, carne bovina, queijo, presunto, tomate, alface e maionese"), "Brioche"));
        produtos.push_back(new Hamburguer(2, "X-Egg", 15, "Hamburguer", FichaProduto("Hamburguer", "Pao, ovo, carne bovina, queijo, presunto, tomate, alface e maionese"), "Brioche"));
        produtos.push_back(new Hamburguer(3, "X-Bacon", 17, "Hamburguer", FichaProduto("Hamburguer", "Pao, bacon, carne bovina, queijo, presunto, tomate, alface e maionese"), "Brioche"));
        produtos.push_back(new Hamburguer(4, "X-Calabresa", 18, "Hamburguer", FichaProduto("Hamburguer", "Pao, calabresa, carne bovina, queijo, presunto, tomate, alface e maionese"), "Brioche"));
        produtos.push_back(new Hamburguer(5, "X-Banana", 19, "Hamburguer", FichaProduto("Hamburguer", "Pao, banana, carne bovina, queijo, presunto, tomate, alface e maionese"), "Brioche"));
        produtos.push_back(new Hamburguer(6, "X-Tudo", 22, "Hamburguer", FichaProduto("Hamburguer", "Pao, carne bovina, bacon, calabresa, queijo, presunto, tomate, alface e maionese"), "Brioche"));
        produtos.push_back(new Bebida(7, "Coca-Cola 300 ml", 4, "Refrigerante", FichaProduto("Bebida", ""), 300));
        produtos.push_back(new Bebida(8, "Coca-Cola 1 L", 9, "Refrigerante", FichaProduto("Bebida", ""), 1000));
        produtos.push_back(new Bebida(9, "Coca-Cola 2 L", 15, "Refrigerante", FichaProduto("Bebida", ""), 2000));
        produtos.push_back(new Bebida(10, "Fanta 2 L", 12, "Refrigerante", FichaProduto("Bebida", ""), 2000));
        produtos.push_back(new Bebida(11, "Agua 500 ml", 2, "Agua", FichaProduto("Bebida", ""), 500));
    }
    void mostrarCardapio() const {
        cout << "\n--- CARDAPIO ---\n";

        for (int i = 0; i < (int)produtos.size(); i++)
            produtos[i]->exibirDetalhes();
        cout << "--- ADICIONAIS ---\n";

        for (int i = 0; i < (int)adicionais.size(); i++)
            cout << adicionais[i].getId() << " - " << adicionais[i].getNome() << " | R$ " << adicionais[i].getPreco() << endl;
            cout << "0 - Terminar\n";
    }
    void escolherItens(Pedido& pedido) {
        while (true) {
            mostrarCardapio();
            int codigo = lerNumero("Codigo: ", 0, 103);
            if (codigo == 0) return;
            string nome;
            float preco = 0;
            for (int i = 0; i < (int)produtos.size(); i++) {
                if (produtos[i]->getId() == codigo) {
                    nome = produtos[i]->getNome();
                    preco = produtos[i]->getPreco();
                }
            }
            for (int i = 0; i < (int)adicionais.size(); i++) {
                if (adicionais[i].getId() == codigo) {
                    nome = "Adicional: " + adicionais[i].getNome();
                    preco = adicionais[i].getPreco();
                }
            }
            if (nome.empty()) { cout << "Produto nao encontrado.\n"; continue; }
            int qtd = lerNumero("Quantidade: ", 1, 100);
            pedido.adicionar(codigo, nome, qtd, preco);
            cout << "Total parcial: R$ " << pedido.total() << endl;
        }
    }

    int mesaAberta(int mesa) const {
        for (int i = 0; i < (int)pedidos.size(); i++)
            if (pedidos[i].getMesa() == mesa && !pedidos[i].estaFinalizado()) return i;
        return -1;
    }
public:
    SistemaLanchonete() : proximoPedido(1), arquivo("dados_point_burguer.txt") {
        adicionais.push_back(Adicional(101, "Carne extra", 5));
        adicionais.push_back(Adicional(102, "Ovo", 5));
        adicionais.push_back(Adicional(103, "Banana", 5));
        carregar();
    }
    ~SistemaLanchonete() {
        for (int i = 0; i < (int)produtos.size(); i++) delete produtos[i];
    }
    SistemaLanchonete(const SistemaLanchonete&) = delete;
    SistemaLanchonete& operator=(const SistemaLanchonete&) = delete;

    int Pesquisar(string nome) const {
        for (int j = 0; j < (int)nome.size(); j++) nome[j] = tolower((unsigned char)nome[j]);
        vector<int> achados;

        for (int i = 0; i < (int)pedidos.size(); i++) {
            string mesa = pedidos[i].getNome();
            for (int j = 0; j < (int)mesa.size(); j++) mesa[j] = tolower((unsigned char)mesa[j]);
            if (!nome.empty() && mesa.find(nome) == 0) achados.push_back(i);
        }

        if (achados.empty()) { cout << "Nenhum pedido encontrado.\n"; return -1; }
        if (achados.size() == 1) return achados[0];
        cout << "Pedidos encontrados:\n";

        for (int i = 0; i < (int)achados.size(); i++) {
            int pos = achados[i];
            cout << "Indice " << pos << " - Pedido " << pedidos[pos].getNumero() << " - " << pedidos[pos].getNome() << endl;
        }

        int pos = lerNumero("Escolha o indice (-1 cancela): ", -1, (int)pedidos.size()-1);
        for (int i = 0; i < (int)achados.size(); i++) if (achados[i] == pos) return pos;
        cout << "Indice nao corresponde aos resultados.\n";
        return -1;
    }

    int buscarPedido() const {
        string nome;
        cout << "Nome da mesa (ex.: Mesa 2): ";
        getline(cin, nome);
        return Pesquisar(nome);
    }
    void inserir() {
        int mesa = lerNumero("Mesa (1 a 4): ", 1, 4);
        if (mesaAberta(mesa) != -1) { cout << "Esta mesa ja tem pedido aberto. Use Alterar.\n"; return; }
        Pedido novo(proximoPedido, mesa);
        escolherItens(novo);
        if (novo.getItens().empty()) { cout << "Pedido vazio nao foi criado.\n"; return; }
        pedidos.push_back(novo);
        proximoPedido++;
        cout << "Pedido criado com sucesso.\n";
    }
    void listarTodos() const {
        if (pedidos.empty()) cout << "Nenhum pedido cadastrado.\n";
        for (int i = 0; i < (int)pedidos.size(); i++) pedidos[i].exibir();
    }
    void exibirUm() const {
        int i = buscarPedido();
        if (i != -1) pedidos[i].exibir();
    }
    void alterar() {
        int i = buscarPedido();
        if (i == -1) return;
        if (pedidos[i].estaFinalizado()) {
                cout << "Venda ja finalizada.\n"; return; }

        pedidos[i].exibir();
        cout << "1 - Adicionar itens\n2 - Retirar itens\n3 - Finalizar venda\n0 - Voltar\n";
        int op = lerNumero("Opcao: ", 0, 3);
        if (op == 1) escolherItens(pedidos[i]);
        if (op == 2) {
            if (pedidos[i].getItens().empty()) {
                    cout << "Pedido vazio.\n"; return; }

            int linha = lerNumero("Numero do item: ", 1, (int)pedidos[i].getItens().size());
            int qtd = lerNumero("Quantidade a retirar: ", 1, 100);
            pedidos[i].retirar(linha - 1, qtd);
            cout << "Item atualizado.\n";
        }
        if (op == 3) {
            if (pedidos[i].getItens().empty()) {
                    cout << "Pedido vazio nao pode ser finalizado.\n"; return; }

            pedidos[i].finalizar();
            cout << "Venda finalizada: R$ " << pedidos[i].total() << endl;
        }
    }

    void remover() {
        int i = buscarPedido();
        if (i == -1) return;
        if (pedidos[i].estaFinalizado()) {
                cout << "Venda finalizada nao pode ser cancelada.\n"; return; }

        int confirmar = lerNumero("Cancelar este pedido? (1 sim, 0 nao): ", 0, 1);

        if (confirmar == 1) {
                pedidos.erase(pedidos.begin() + i); cout << "Pedido cancelado.\n"; }
    }

    void exibirRelatorio() const {
        cout << "1 - Vendas de hoje\n2 - Todas as vendas\n";
        int periodo = lerNumero("Periodo: ", 1, 2);
        string hoje = Data::hoje().getTexto();
        int vendas = 0, abertos = 0;
        float faturamento = 0, porMesa[4] = {0, 0, 0, 0};
        map<string, int> quantidades;

        for (int i = 0; i < (int)pedidos.size(); i++) {
            const Pedido& p = pedidos[i];
            if (periodo == 1 && p.getData().getTexto() != hoje) continue;
            if (!p.estaFinalizado()) { abertos++; continue; }
            vendas++;
            faturamento += p.total();
            porMesa[p.getMesa()-1] += p.total();

            for (int j = 0; j < (int)p.getItens().size(); j++)
                quantidades[p.getItens()[j].getNome()] += p.getItens()[j].getQuantidade();
        }
        cout << "\n--- RELATORIO ---\nVendas finalizadas: " << vendas << "\nPedidos abertos: " << abertos << "\nFaturamento: R$ " << faturamento << endl;
        cout << "Produtos vendidos:\n";

        for (map<string, int>::iterator it = quantidades.begin(); it != quantidades.end(); ++it)
            cout << it->first << ": " << it->second << " unidade(s)\n";

        for (int mesa = 1; mesa <= 4; mesa++)
            cout << "Mesa " << mesa << ": R$ " << porMesa[mesa-1] << endl;
    }
    void salvar() const {
        ofstream out(arquivo.c_str());
        if (!out) { cout << "Erro ao salvar os dados.\n"; return; }
        out << proximoPedido << '\n' << produtos.size() << '\n';
        for (int i = 0; i < (int)produtos.size(); i++) {
            Produto* p = produtos[i];
            out << p->getTipo() << '|' << p->getId() << '|' << p->getNome() << '|'
                << p->getPreco() << '|' << p->getDescricao() << '|'
                << p->getFicha().getCategoria() << '|'
                << p->getFicha().getIngredientes() << '|' << p->getExtra() << '\n';
        }
        out << pedidos.size() << '\n';

        for (int i = 0; i < (int)pedidos.size(); i++) {
            const Pedido& p = pedidos[i];
            out << p.getNumero() << '|' << p.getMesa() << '|'
                << p.estaFinalizado() << '|' << p.getData().getTexto() << '|'
                << p.getItens().size() << '\n';

            for (int j = 0; j < (int)p.getItens().size(); j++) {
                const ItemPedido& item = p.getItens()[j];
                out << item.getId() << '|' << item.getNome() << '|'
                    << item.getQuantidade() << '|' << item.getPreco() << '\n';
            }
        }
    }
    void carregar() {
        ifstream in(arquivo.c_str());
      if (!in) { criarCardapio(); return; }
        int nProdutos, nPedidos;
        if (!(in >> proximoPedido >> nProdutos) || nProdutos < 0 || nProdutos > 1000) {
            criarCardapio(); return;
        }
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        string linha;
        for (int i = 0; i < nProdutos && getline(in, linha); i++) {
            vector<string> v = separar(linha);
            if (v.size() != 8) continue;
            try {
                int id = stoi(v[1]);
                float preco = stof(v[3]);
                FichaProduto ficha(v[5], v[6]);
                if (v[0] == "H") produtos.push_back(new Hamburguer(id, v[2], preco, v[4], ficha, v[7]));
                if (v[0] == "B") produtos.push_back(new Bebida(id, v[2], preco, v[4], ficha, stoi(v[7])));
            } catch (...) { cout << "Produto invalido no arquivo.\n"; }
        }
        if (produtos.empty()) criarCardapio();
        if (!(in >> nPedidos) || nPedidos < 0 || nPedidos > 100000) return;
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        for (int i = 0; i < nPedidos && getline(in, linha); i++) {
            vector<string> v = separar(linha);
            if (v.size() != 5) break;
            try {
                Pedido pedido(stoi(v[0]), stoi(v[1]), Data(v[3]));
                int quantidadeItens = stoi(v[4]);
                for (int j = 0; j < quantidadeItens; j++) {
                    if (!getline(in, linha)) break;
                    vector<string> item = separar(linha);
                    if (item.size() == 4)
                        pedido.adicionar(stoi(item[0]), item[1], stoi(item[2]), stof(item[3]));
                }
                if (v[2] == "1") pedido.finalizar();
                pedidos.push_back(pedido);
                if (proximoPedido <= pedido.getNumero()) proximoPedido = pedido.getNumero() + 1;
            } catch (...) { cout << "Pedido invalido no arquivo.\n"; }
        }
    }
    void executar() {
        cout << fixed << setprecision(2);
        while (true) {
            cout << "\n=== POINT BURGUER ===\n"
                 << "1. Inserir\n2. Listar todos\n3. Exibir um (pesquisar por nome)\n"
                 << "4. Alterar (pesquisar por nome)\n5. Remover (pesquisar por nome)\n"
                 << "6. Exibir Relatorio\n7. Sair\n";
            int op = lerNumero("Opcao: ", 1, 7);
            switch (op) {
                case 1: inserir(); break;
                case 2: listarTodos(); break;
                case 3: exibirUm(); break;
                case 4: alterar(); break;
                case 5: remover(); break;
                case 6: exibirRelatorio(); break;
                case 7: salvar(); cout << "Dados salvos. Ate logo!\n"; return;
            }
        }
    }
};
