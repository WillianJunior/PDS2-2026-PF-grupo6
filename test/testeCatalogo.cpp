#include "doctest.h"
#include "../include/Catalogo.hpp"
#include "../include/Produto.hpp"
#include <cstdio>
#include <stdexcept>
#include <string>

// Usamos um arquivo FAKE de teste para nao destruir o banco de dados real
const std::string ARQUIVO_TESTE = "catalogo_teste.txt";

TEST_CASE("Catalogo - Inicializacao e Excecoes Defensivas (Caminhos Tristes)") {
    std::remove(ARQUIVO_TESTE.c_str()); 
    Catalogo catalogo(ARQUIVO_TESTE);
    
    // Forçamos a exclusão do arquivo com a classe rodando para simular um erro no disco
    std::remove(ARQUIVO_TESTE.c_str()); 

    SUBCASE("Disparos de erro sem arquivo fisico") {
        CHECK_THROWS_AS(catalogo.buscarItem("Teste"), std::runtime_error);
        CHECK_THROWS_AS(catalogo.listarProdutosCategoria(CategoriaProduto::Ficcao), std::runtime_error);
        CHECK_THROWS_AS(catalogo.ordenarPreco(true), std::runtime_error);
        CHECK_THROWS_AS(catalogo.exibirDescricao(1), std::runtime_error);
        CHECK_THROWS_AS(catalogo.removerProduto(1), std::runtime_error);
        CHECK_THROWS_AS(catalogo.buscarProdutoPorId(1), std::runtime_error);
        
        CHECK(catalogo.listarProdutosDisponiveis() == "");
    }
}

TEST_CASE("Catalogo - Operacoes de Adicao, Leitura e Integracao com Carrinho") {

    std::remove(ARQUIVO_TESTE.c_str()); 
    Catalogo catalogo(ARQUIVO_TESTE);

    Produto p1(1, "O Senhor dos Aneis", "Fantasia Epica", 120.50f, 10, CategoriaProduto::Fantasia);
    Produto p2(2, "Clean Code", "Engenharia de Software", 89.90f, 5, CategoriaProduto::Tecnico);
    Produto p3(3, "1984", "Ficcao Distopica", 45.00f, 15, CategoriaProduto::Ficcao);

    CHECK_NOTHROW(catalogo.adicionarProduto(p1));
    CHECK_NOTHROW(catalogo.adicionarProduto(p2));
    CHECK_NOTHROW(catalogo.adicionarProduto(p3));

    SUBCASE("Buscar Item Especifico") {
        std::string resExistente = catalogo.buscarItem("Clean");
        CHECK(resExistente.find("Clean Code") != std::string::npos);

        std::string resInexistente = catalogo.buscarItem("Harry Potter");
        CHECK(resInexistente.empty());
    }

    SUBCASE("Listar por Categoria") {
        std::string resFiccao = catalogo.listarProdutosCategoria(CategoriaProduto::Ficcao);
        CHECK(resFiccao.find("1984") != std::string::npos);

        std::string resTecnico = catalogo.listarProdutosCategoria(CategoriaProduto::Tecnico);
        CHECK(resTecnico.find("Clean Code") != std::string::npos); 
    }

    SUBCASE("Ordenar Preco via Bubble Sort") {
        std::string resCrescente = catalogo.ordenarPreco(true);
        CHECK(resCrescente.find("1984") < resCrescente.find("Clean Code"));
        CHECK(resCrescente.find("Clean Code") < resCrescente.find("O Senhor dos Aneis"));

        std::string resDecrescente = catalogo.ordenarPreco(false);
        CHECK(resDecrescente.find("O Senhor dos Aneis") < resDecrescente.find("Clean Code"));
    }

    SUBCASE("Exibir Descricao do Produto") {
        std::string desc = catalogo.exibirDescricao(2);
        CHECK(desc == "Engenharia de Software");

        std::string descVazia = catalogo.exibirDescricao(99);
        CHECK(descVazia.empty());
    }

    SUBCASE("Listar Produtos Disponiveis para a Interface do Carrinho") {
        std::string resDisp = catalogo.listarProdutosDisponiveis();
        CHECK(resDisp.find("ID: 1") != std::string::npos);
        CHECK(resDisp.find("Clean Code") != std::string::npos);
         
        CHECK(resDisp.find("R$ 45") != std::string::npos); 
    }

    SUBCASE("Buscar Produto instanciado pelo ID") {
        Produto busca = catalogo.buscarProdutoPorId(2);
        CHECK(busca.getNome() == "Clean Code");
        CHECK(busca.getQuantidadeEstoque() == 5);
        CHECK(busca.getCategoria() == CategoriaProduto::Tecnico);
        
        Produto buscaFantasia = catalogo.buscarProdutoPorId(1);
        CHECK(buscaFantasia.getCategoria() == CategoriaProduto::Fantasia);

        CHECK_THROWS_AS(catalogo.buscarProdutoPorId(999), std::invalid_argument);
    }

    SUBCASE("Remover Produto do Catalogo") {
        CHECK_NOTHROW(catalogo.removerProduto(2));
        
        std::string buscaAposRemocao = catalogo.buscarItem("Clean Code");
        CHECK(buscaAposRemocao.empty());
        
        std::string buscaRestante = catalogo.buscarItem("1984");
        CHECK(buscaRestante.find("1984") != std::string::npos);
    }

    std::remove(ARQUIVO_TESTE.c_str()); 
}