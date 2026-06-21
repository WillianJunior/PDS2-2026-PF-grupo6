#include "doctest.h"
#include "../include/Catalogo.hpp"
#include "../include/Produto.hpp"
#include <cstdio>
#include <stdexcept>
#include <string>

TEST_CASE("Catalogo - Inicializacao e Excecoes Defensivas (Caminhos Tristes)") {
    std::remove("catalogo.txt"); 
    Catalogo catalogo;

    SUBCASE("Buscar item sem arquivo físico") {
        CHECK_THROWS_AS(catalogo.buscarItem("Teste"), std::runtime_error);
    }
    SUBCASE("Listar categorias sem arquivo físico") {
        CHECK_THROWS_AS(catalogo.listarProdutosCategoria(CategoriaProduto::Ficcao), std::runtime_error);
    }
    SUBCASE("Ordenar precos sem arquivo físico") {
        CHECK_THROWS_AS(catalogo.ordenarPreco(true), std::runtime_error);
    }
    SUBCASE("Exibir descricao sem arquivo físico") {
        CHECK_THROWS_AS(catalogo.exibirDescricao(1), std::runtime_error);
    }
    SUBCASE("Remover produto sem arquivo físico") {
        CHECK_THROWS_AS(catalogo.removerProduto(1), std::runtime_error);
    }
}

TEST_CASE("Catalogo - Operacoes de Adicao, Leitura e Remocao (Caminho Feliz)") {

    std::remove("catalogo.txt"); 
    Catalogo catalogo;

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

    SUBCASE("Listar por Categoria (Padrão de salvamento)") {
    
        std::string resFiccao = catalogo.listarProdutosCategoria(CategoriaProduto::Ficcao);
        CHECK(resFiccao.find("O Senhor dos Aneis") != std::string::npos);
        CHECK(resFiccao.find("Clean Code") != std::string::npos);

        std::string resTecnico = catalogo.listarProdutosCategoria(CategoriaProduto::Tecnico);
        CHECK(resTecnico.empty()); 
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

    SUBCASE("Remover Produto do Catalogo") {
        CHECK_NOTHROW(catalogo.removerProduto(2));
        
        std::string buscaAposRemocao = catalogo.buscarItem("Clean Code");
        CHECK(buscaAposRemocao.empty());
        
     
        std::string buscaRestante = catalogo.buscarItem("1984");
        CHECK(buscaRestante.find("1984") != std::string::npos);
    }

 
    std::remove("catalogo.txt"); 
}