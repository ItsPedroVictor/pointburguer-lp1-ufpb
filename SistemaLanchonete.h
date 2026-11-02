#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <limits>
#include <map>
#include "Produto.h"
#include "Hamburguer.h"
#include "Bebida.h"
#include "Adicional.h"
#include "Pedido.h"

// Esta classe concentra TODAS as operacoes. A main apenas inicia o sistema.
class SistemaLanchonete {
private:
    std::vector<Produto*> produtos; // POLIMORFISMO: aponta para Hamburguer e Bebida.
    std::vector<Adicional> adicionais;
    std::vector<Pedido> pedidos;
    int proximoPedido;
    std::string arquivo;

    // Evita que uma entrada invalida trave os menus.
    static int lerInteiro(const std::string& mensagem, int minimo, int maximo) {
        int valor;
        while (true) {
            std::cout << mensagem;
            if ((std::cin >> valor) && valor >= minimo && valor <= maximo) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return valor;
            }
            std::cout << "Valor invalido. Tente novamente.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    static std::string minusculo(std::string s) {
        for (std::size_t i=0;i<s.size();++i) s[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(s[i])));
        return s;
    }
    static std::vector<std::string> dividir(const std::string& linha, char separador) {
        std::vector<std::string> partes;
        std::istringstream s(linha);
        std::string parte;
        while (std::getline(s,parte,separador)) partes.push_back(parte);
        return partes;
    }
    void cadastrarCardapio() {
        // Precos e nomes do cartaz original da Point Burguer.
        struct Lanche { const char* nome; double preco; const char* ingrediente; };
        const Lanche lanches[] = {
            {"X-Salada", 13, "Pao brioche, carne bovina, queijo, presunto, tomate, alface e maionese"},
            {"X-Egg", 15, "Pao brioche, ovo, carne bovina, queijo, presunto, tomate, alface e maionese"},
            {"X-Bacon", 17, "Pao brioche, bacon, carne bovina, queijo, presunto, tomate, alface e maionese"},
            {"X-Calabresa", 18, "Pao brioche, calabresa, carne bovina, queijo, presunto, tomate, alface e maionese"},
            {"X-Banana", 19, "Pao brioche, banana, carne bovina, queijo, presunto, tomate, alface e maionese"},
            {"X-Tudo", 22, "Pao brioche, carne bovina, bacon, calabresa, queijo, presunto, tomate, alface e maionese"}
        };
        for (int i=0; i<6; ++i) {
            produtos.push_back(new Hamburguer(i+1,lanches[i].nome,static_cast<float>(lanches[i].preco),
                "Hamburguer artesanal",FichaProduto("Hamburguer",lanches[i].ingrediente),0,"Brioche"));
        }
        // Valores das bebidas combinados anteriormente; sao editaveis no codigo.
        produtos.push_back(new Bebida(7,"Coca-Cola 300 ml",4,"Refrigerante",FichaProduto("Bebida",""),0,300,"Refrigerante"));
        produtos.push_back(new Bebida(8,"Coca-Cola 1 L",9,"Refrigerante",FichaProduto("Bebida",""),0,1000,"Refrigerante"));
        produtos.push_back(new Bebida(9,"Coca-Cola 2 L",15,"Refrigerante",FichaProduto("Bebida",""),0,2000,"Refrigerante"));
        produtos.push_back(new Bebida(10,"Fanta 2 L",12,"Refrigerante",FichaProduto("Bebida",""),0,2000,"Refrigerante"));
        produtos.push_back(new Bebida(11,"Agua 500 ml",2,"Agua mineral",FichaProduto("Bebida",""),0,500,"Agua"));
    }
    void cadastrarAdicionais() {
        adicionais.push_back(Adicional(101,"Carne extra",5));
        adicionais.push_back(Adicional(102,"Ovo",5));
        adicionais.push_back(Adicional(103,"Banana",5));
    }
    Produto* encontrarProduto(int id) const {
        for (std::size_t i=0;i<produtos.size();++i)
            if (produtos[i]->getId()==id) return produtos[i];
        return NULL;
    }
    int pedidoAbertoNaMesa(int mesa) const {
        for (std::size_t i=0;i<pedidos.size();++i)
            if (pedidos[i].getMesa()==mesa && !pedidos[i].estaFinalizado()) return static_cast<int>(i);
        return -1;
    }
    void mostrarCardapio() const {
        std::cout << "\n========= CARDAPIO POINT BURGUER =========\n";
        for (std::size_t i=0;i<produtos.size();++i) {
            // A chamada virtual escolhe a versao de Hamburguer ou Bebida.
            std::cout << std::setw(2) << produtos[i]->getId() << " - "
                      << produtos[i]->getNome() << " | R$ " << produtos[i]->getPreco() << "\n";
        }
        std::cout << "----- ADICIONAIS (para hamburgueres) -----\n";
        for (std::size_t i=0;i<adicionais.size();++i)
            std::cout << adicionais[i].getId() << " - " << adicionais[i].getNome()
                      << " | R$ " << adicionais[i].getPreco() << "\n";
        std::cout << "0 - Voltar\n";
    }
    // Insere quantidades no pedido EM MEMORIA. Os adicionais tambem sao itens.
    void escolherItens(Pedido& pedido) {
        while (true) {
            mostrarCardapio();
            int id = lerInteiro("Codigo do produto (0 para terminar): ",0,103);
            if (id == 0) break;
            Produto* produto = encontrarProduto(id);
            const Adicional* extra = NULL;
            for (std::size_t i=0;i<adicionais.size();++i)
                if (adicionais[i].getId()==id) extra=&adicionais[i];
            if (!produto && !extra) {
                std::cout << "Codigo nao encontrado.\n";
                continue;
            }
            int quantidade=lerInteiro("Quantidade: ",1,100);
            if (produto) pedido.adicionar(id,produto->getNome(),quantidade,produto->getPreco());
            else pedido.adicionar(id,"Adicional: " + extra->getNome(),quantidade,extra->getPreco());
            std::cout << "Item adicionado. Total parcial: R$ " << pedido.total() << "\n";
        }
    }
public:
    SistemaLanchonete() : proximoPedido(1), arquivo("dados_point_burguer.txt") {
        cadastrarAdicionais();
        carregar();
    }
    ~SistemaLanchonete() {
        for (std::size_t i=0;i<produtos.size();++i) delete produtos[i];
    }
    // Evita copia acidental dos ponteiros (que causaria double delete).
    SistemaLanchonete(const SistemaLanchonete&) = delete;
    SistemaLanchonete& operator=(const SistemaLanchonete&) = delete;

    // EXIGENCIA: recebe string, permite nome inteiro ou prefixo e retorna indice.
    // Como o sistema nao cadastra clientes, o "nome" e "Mesa 1", "Mesa 2", etc.
    int Pesquisar(std::string nome) const {
        std::string busca=minusculo(nome);
        if (busca.empty()) return -1;
        std::vector<int> encontrados;
        for (std::size_t i=0;i<pedidos.size();++i) {
            std::string rotulo=minusculo(pedidos[i].getNome());
            if (rotulo.compare(0,busca.size(),busca)==0) encontrados.push_back(static_cast<int>(i));
        }
        if (encontrados.empty()) { std::cout << "Nenhum pedido encontrado.\n"; return -1; }
        if (encontrados.size()==1) return encontrados[0];
        std::cout << "\nMais de um pedido encontrado. Escolha pelo indice:\n";
        for (std::size_t i=0;i<encontrados.size();++i) {
            const Pedido& p=pedidos[encontrados[i]];
            std::cout << "Indice " << encontrados[i] << " | Pedido #" << p.getNumero()
                      << " | " << p.getNome() << " | "
                      << (p.estaFinalizado()?"FINALIZADO":"ABERTO") << " | " << p.getData().texto() << "\n";
        }
        while (true) {
            int indice=lerInteiro("Indice desejado (-1 cancela): ",-1,static_cast<int>(pedidos.size())-1);
            if (indice==-1) return -1;
            if (std::find(encontrados.begin(),encontrados.end(),indice)!=encontrados.end()) return indice;
            std::cout << "Escolha um indice mostrado acima.\n";
        }
    }
    int solicitarPesquisa() const {
        std::string nome;
        std::cout << "Digite o nome da mesa (ex.: Mesa 2, ou Mesa): ";
        std::getline(std::cin,nome);
        return Pesquisar(nome);
    }
    void inserir() {
        int mesa=lerInteiro("Mesa do novo pedido (1 a 4): ",1,4);
        if (pedidoAbertoNaMesa(mesa)!=-1) {
            std::cout << "Ja existe um pedido aberto nessa mesa. Use Alterar.\n";
            return;
        }
        Pedido pedido(proximoPedido,mesa,Data::hoje());
        escolherItens(pedido);
        if (pedido.getItens().empty()) { std::cout << "Pedido vazio nao foi criado.\n"; return; }
        pedidos.push_back(pedido);
        ++proximoPedido;
        std::cout << "Pedido criado com sucesso! Numero #" << pedido.getNumero() << "\n";
    }
    void listarTodos() const {
        std::cout << "\n========== TODOS OS PEDIDOS ==========\n";
        if (pedidos.empty()) { std::cout << "Nenhum pedido cadastrado.\n"; return; }
        for (std::size_t i=0;i<pedidos.size();++i) pedidos[i].exibir();
    }
    void exibirUm() const {
        int indice=solicitarPesquisa();
        if (indice>=0) pedidos[indice].exibir();
    }
    void alterar() {
        int indice=solicitarPesquisa();
        if (indice<0) return;
        Pedido& pedido=pedidos[indice];
        if (pedido.estaFinalizado()) { std::cout << "Venda finalizada nao pode ser alterada.\n"; return; }
        while (true) {
            pedido.exibir();
            std::cout << "\n1 - Adicionar itens\n2 - Retirar itens\n3 - Finalizar venda\n0 - Voltar\n";
            int op=lerInteiro("Escolha: ",0,3);
            if (op==0) break;
            if (op==1) escolherItens(pedido);
            else if (op==2) {
                if (pedido.getItens().empty()) { std::cout << "Pedido vazio.\n"; continue; }
                int item=lerInteiro("Numero da linha para retirar: ",1,static_cast<int>(pedido.getItens().size()));
                int quantidade=lerInteiro("Quantidade para retirar: ",1,100);
                pedido.retirar(item-1,quantidade);
                std::cout << "Pedido atualizado.\n";
            } else {
                if (pedido.getItens().empty()) { std::cout << "Adicione itens antes de finalizar.\n"; continue; }
                pedido.finalizar();
                std::cout << "Venda finalizada. Total: R$ " << pedido.total() << "\n";
                break;
            }
        }
    }
    void remover() {
        int indice=solicitarPesquisa();
        if (indice<0) return;
        pedidos[indice].exibir();
        if (pedidos[indice].estaFinalizado()) {
            std::cout << "Venda finalizada: nao e possivel cancelar (mantem o historico).\n";
            return;
        }
        int confirmar=lerInteiro("Cancelar e remover este pedido? (1 sim / 0 nao): ",0,1);
        if (confirmar==1) { pedidos.erase(pedidos.begin()+indice); std::cout << "Pedido cancelado.\n"; }
    }
    void exibirRelatorio() const {
        std::cout << "\n========== RELATORIO DE VENDAS ==========" << "\n";
        std::cout << "1 - Vendas de hoje (" << Data::hoje().texto() << ")\n2 - Todas as datas\n";
        int periodo=lerInteiro("Periodo: ",1,2);
        int concluidas=0, abertas=0;
        double faturamento=0;
        std::map<std::string,int> quantidades;
        double totalPorMesa[4]={0,0,0,0};
        for (std::size_t i=0;i<pedidos.size();++i) {
            const Pedido& p=pedidos[i];
            if (periodo==1 && p.getData().texto()!=Data::hoje().texto()) continue;
            if (!p.estaFinalizado()) { ++abertas; continue; }
            ++concluidas;
            faturamento += p.total();
            totalPorMesa[p.getMesa()-1] += p.total();
            const std::vector<ItemPedido>& itens=p.getItens();
            for (std::size_t j=0;j<itens.size();++j)
                quantidades[itens[j].getNome()] += itens[j].getQuantidade();
        }
        std::cout << "Vendas finalizadas: " << concluidas << "\nPedidos abertos: " << abertas << "\n";
        std::cout << "Faturamento de vendas finalizadas: R$ " << faturamento << "\n";
        std::cout << "\nQuantidade vendida por produto:\n";
        if (quantidades.empty()) std::cout << "Nenhuma venda finalizada nesse periodo.\n";
        for (std::map<std::string,int>::const_iterator it=quantidades.begin(); it!=quantidades.end(); ++it)
            std::cout << "  " << it->first << ": " << it->second << " unidade(s)\n";
        std::cout << "\nFaturamento por mesa:\n";
        for (int mesa=1;mesa<=4;++mesa) std::cout << "  Mesa " << mesa << ": R$ " << totalPorMesa[mesa-1] << "\n";
    }
    void salvar() const {
        std::ofstream out(arquivo.c_str());
        if (!out) { std::cout << "ERRO: nao foi possivel salvar " << arquivo << "\n"; return; }
        out << "POINTBURGUER|1\n";
        out << "SEQUENCIA|" << proximoPedido << "\n";
        // UM arquivo para dados das duas subclasses do vetor polimorfico.
        for (std::size_t i=0;i<produtos.size();++i) {
            const Produto* p=produtos[i];
            out << "PRODUTO|" << p->getTipo() << '|' << p->getId() << '|' << p->getNome()
                << '|' << p->getPreco() << '|' << p->getDescricao() << '|' << p->getEstoque()
                << '|' << p->getFicha().getCategoria() << '|' << p->getFicha().getIngredientes();
            if (p->getTipo()=="H") {
                const Hamburguer* h=dynamic_cast<const Hamburguer*>(p);
                out << '|' << h->getTipoPao();
            } else {
                const Bebida* b=dynamic_cast<const Bebida*>(p);
                out << '|' << b->getVolumeMl() << '|' << b->getTipoBebida();
            }
            out << "\n";
        }
        for (std::size_t i=0;i<pedidos.size();++i) {
            const Pedido& p=pedidos[i];
            out << "PEDIDO|" << p.getNumero() << '|' << p.getMesa() << '|'
                << (p.estaFinalizado()?1:0) << '|' << p.getData().texto() << "\n";
            const std::vector<ItemPedido>& itens=p.getItens();
            for (std::size_t j=0;j<itens.size();++j)
                out << "ITEM|" << p.getNumero() << '|' << itens[j].getIdProduto() << '|'
                    << itens[j].getNome() << '|' << itens[j].getQuantidade() << '|'
                    << itens[j].getPrecoUnitario() << "\n";
        }
        if (!out.good()) std::cout << "ERRO durante a gravacao do arquivo.\n";
    }
    void carregar() {
        std::ifstream in(arquivo.c_str());
        if (!in) { cadastrarCardapio(); return; }
        std::string linha;
        std::getline(in,linha);
        if (linha!="POINTBURGUER|1") {
            std::cout << "Arquivo em formato desconhecido. Cardapio padrao sera usado.\n";
            cadastrarCardapio(); return;
        }
        std::map<int,std::vector<ItemPedido> > itensPorPedido;
        while (std::getline(in,linha)) {
            std::vector<std::string> v=dividir(linha,'|');
            try {
                if (v.empty()) continue;
                if (v[0]=="SEQUENCIA" && v.size()>=2) proximoPedido=std::stoi(v[1]);
                else if (v[0]=="PRODUTO" && v.size()>=10) {
                    int id=std::stoi(v[2]), estoque=std::stoi(v[6]);
                    float preco=std::stof(v[4]);
                    FichaProduto ficha(v[7],v[8]);
                    if (v[1]=="H") produtos.push_back(new Hamburguer(id,v[3],preco,v[5],ficha,estoque,v[9]));
                    else if (v[1]=="B" && v.size()>=11)
                        produtos.push_back(new Bebida(id,v[3],preco,v[5],ficha,estoque,std::stoi(v[9]),v[10]));
                } else if (v[0]=="PEDIDO" && v.size()>=5) {
                    Pedido p(std::stoi(v[1]),std::stoi(v[2]),Data::ler(v[4]));
                    if (v[3]=="1") p.finalizar();
                    pedidos.push_back(p);
                    proximoPedido=std::max(proximoPedido,p.getNumero()+1);
                } else if (v[0]=="ITEM" && v.size()>=6) {
                    int numero=std::stoi(v[1]);
                    itensPorPedido[numero].push_back(ItemPedido(std::stoi(v[2]),v[3],std::stoi(v[4]),std::stod(v[5])));
                }
            } catch (...) { std::cout << "Aviso: linha de dados ignorada (formato invalido).\n"; }
        }
        for (std::size_t i=0;i<pedidos.size();++i) {
            std::vector<ItemPedido>& itens=itensPorPedido[pedidos[i].getNumero()];
            for (std::size_t j=0;j<itens.size();++j)
                pedidos[i].adicionar(itens[j].getIdProduto(),itens[j].getNome(),itens[j].getQuantidade(),itens[j].getPrecoUnitario());
        }
        if (produtos.empty()) cadastrarCardapio();
    }
    void executar() {
        std::cout << std::fixed << std::setprecision(2);
        while (true) {
            std::cout << "\n====== POINT BURGUER - VENDAS POR MESA ======\n"
                      << "1. Inserir\n2. Listar todos\n3. Exibir um (pesquisar por nome)\n"
                      << "4. Alterar (pesquisar por nome)\n5. Remover (pesquisar por nome)\n"
                      << "6. Exibir Relatorio\n7. Sair\n";
            int op=lerInteiro("Opcao: ",1,7);
            switch(op) {
                case 1: inserir(); break;
                case 2: listarTodos(); break;
                case 3: exibirUm(); break;
                case 4: alterar(); break;
                case 5: remover(); break;
                case 6: exibirRelatorio(); break;
                case 7: salvar(); std::cout << "Dados salvos. Ate logo!\n"; return;
            }
        }
    }
};
