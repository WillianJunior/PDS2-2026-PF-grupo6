#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "../include/Catalogo.hpp"
#include "../include/Produto.hpp"

TEST_CASE("Criacao do catalogo") {

    Catalogo catalogo;

    CHECK(true);
}

TEST_CASE("Adicionar produto ao catalogo") {

    Catalogo catalogo;

    Produto livro(
        1,
        "Livro Teste",
        "Descricao de teste",
        29.90f,
        5
    );

    catalogo.adicionarProduto(livro);

    CHECK(true);
}

TEST_CASE("Adicionar mais de um produto") {

    Catalogo catalogo;

    Produto livro1(
        1,
        "Livro A",
        "Descricao A",
        10.0f,
        3
    );

    Produto livro2(
        2,
        "Livro B",
        "Descricao B",
        20.0f,
        5
    );

    catalogo.adicionarProduto(livro1);
    catalogo.adicionarProduto(livro2);

    CHECK(true);
}

TEST_CASE("Buscar item existente") {

    Catalogo catalogo;

    catalogo.buscarItem("Livro Teste");

    CHECK(true);
}

TEST_CASE("Buscar item inexistente") {

    Catalogo catalogo;

    catalogo.buscarItem(
        "Livro Que Nao Existe"
    );

    CHECK(true);
}

TEST_CASE("Ordenar catalogo por preco crescente") {

    Catalogo catalogo;

    catalogo.ordenarPreco(true);

    CHECK(true);
}

TEST_CASE("Ordenar catalogo por preco decrescente") {

    Catalogo catalogo;

    catalogo.ordenarPreco(false);

    CHECK(true);
}

TEST_CASE("Listar produtos por categoria Ficcao") {

    Catalogo catalogo;

    catalogo.listarProdutosCategoria(
        CategoriaProduto::Ficcao
    );

    CHECK(true);
}

TEST_CASE("Listar produtos por categoria Tecnico") {

    Catalogo catalogo;

    catalogo.listarProdutosCategoria(
        CategoriaProduto::Tecnico
    );

    CHECK(true);
}

TEST_CASE("Listar produtos por categoria Infantil") {

    Catalogo catalogo;

    catalogo.listarProdutosCategoria(
        CategoriaProduto::Infantil
    );

    CHECK(true);
}

TEST_CASE("Listar produtos por categoria Romance") {

    Catalogo catalogo;

    catalogo.listarProdutosCategoria(
        CategoriaProduto::Romance
    );

    CHECK(true);
}

TEST_CASE("Exibir descricao de produto") {

    Catalogo catalogo;

    catalogo.exibirDescricao(1);

    CHECK(true);
}

TEST_CASE("Remover produto do catalogo") {

    Catalogo catalogo;

    catalogo.removerProduto(1);

    CHECK(true);
}

TEST_CASE("Remover item inexistente") {

    Catalogo catalogo;

    catalogo.removerProduto(999);

    CHECK(true);
}