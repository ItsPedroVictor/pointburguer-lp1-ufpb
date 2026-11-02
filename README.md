# Point Burguer — Sistema de Vendas

**Universidade:** Universidade Federal da Paraíba (UFPB)  
**Projeto:** Point Burguer — Sistema de Vendas por Mesa  
**Linguagem:** C++

## Integrantes

- Pedro Victor Gonçalves Justino
- Jonas Gabriel Evangelista Da Silva

## Sobre o projeto

O Point Burguer é um programa de terminal para registrar vendas de uma lanchonete com quatro mesas (1 a 4). Ele permite criar pedidos, adicionar hambúrgueres, bebidas e adicionais, consultar e alterar pedidos, cancelar pedidos ainda abertos e finalizar vendas. Também calcula os valores automaticamente e apresenta um relatório das vendas.

## Como executar

### Pelo Code::Blocks (recomendado)

1. Extraia o arquivo ZIP do projeto para uma pasta no computador.
2. Abra o **Code::Blocks** e vá em **File → Open**.
3. Selecione o arquivo **`Point_Burguer.cbp`** dentro da pasta do projeto.
4. Confira se o arquivo **`main.cpp`** e todos os arquivos **`.h`** estão na pasta do projeto.
5. Clique em **Build and Run (F9)** para compilar e executar.

**Requisito:** ter o compilador C++ configurado no Code::Blocks, com suporte a C++11.

### Pelo terminal (alternativo)

Com o compilador `g++` instalado, abra o terminal na pasta do projeto e execute:

```bash
g++ -std=c++11 main.cpp -o Point_Burguer
```

Depois, execute `Point_Burguer.exe` no Windows ou `./Point_Burguer` no Linux.

## Como usar

No menu do programa, digite o número da operação desejada:

1. **Inserir:** inicia um pedido para uma das mesas. Digite o código e a quantidade de cada produto; repita para incluir vários itens no mesmo pedido. Digite **0** para terminar a seleção.
2. **Listar todos:** mostra os pedidos cadastrados.
3. **Exibir um:** pesquisa um pedido pelo nome da mesa, por exemplo, `Mesa 2`.
4. **Alterar:** permite adicionar ou retirar itens e finalizar uma venda.
5. **Remover:** cancela um pedido ainda aberto.
6. **Exibir Relatório:** mostra vendas, faturamento e quantidades vendidas.
7. **Sair:** salva os dados e fecha o programa.

## Salvamento dos dados

Os pedidos e produtos são salvos no arquivo **`dados_point_burguer.txt`** quando o usuário escolhe **7 — Sair**. Ao abrir o programa novamente, os dados são carregados automaticamente. O arquivo é criado na pasta de execução do programa.

**Observação:** mantenha os arquivos do projeto juntos e não exclua `dados_point_burguer.txt` se quiser preservar as vendas já registradas.
