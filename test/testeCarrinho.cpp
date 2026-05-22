#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Carrinho.hpp"
#include "Produto.hpp"
#include "Cliente.hpp"

TEST_CASE("Carrinho - fluxo principal de livros") {

    Cliente cliente("12345678900");
    Carrinho carrinho(cliente);

Produto livro1(1, "Harry Potter", "Fantasia", 100.0f, 10);
    Produto livro2(2, "Morte no Nilo", "Suspense", 150.0f, 5);

    SUBCASE("Adicionar produtos") {
        carrinho.adicionarProduto(livro1, 2);
        carrinho.adicionarProduto(livro2, 1);

        CHECK(carrinho.getQuantidadeItens() == 2);
        CHECK(carrinho.calcularSubtotal() == doctest::Approx(350.0));
    }

    SUBCASE("Atualizar quantidade") {
        carrinho.adicionarProduto(livro1, 1);
        carrinho.atualizarQuantidade(1, 3);

        CHECK(carrinho.calcularSubtotal() == doctest::Approx(300.0));
    }

    SUBCASE("Remover produto") {
        carrinho.adicionarProduto(livro1, 1);
        carrinho.removerProduto(1);

        CHECK(carrinho.vazio() == true);
    }
}

TEST_CASE("Carrinho - regras de frete") {

    Cliente cliente("11111111111");
    Carrinho carrinho(cliente);

    Produto livro1(1, "Livro A", "X", 50.0f, 10);

    SUBCASE("Frete 0 quando vazio") {
        CHECK(carrinho.calcularValorFrete() == 0.0);
    }

    SUBCASE("Frete 20 abaixo de 100") {
        carrinho.adicionarProduto(livro1, 1);
        CHECK(carrinho.calcularValorFrete() == 20.0);
    }

    SUBCASE("Frete 15 entre 100 e 299") {
        carrinho.adicionarProduto(livro1, 3); 
        CHECK(carrinho.calcularValorFrete() == 15.0);
    }

    SUBCASE("Frete gratis acima de 300") {
        carrinho.adicionarProduto(livro1, 7); 
        CHECK(carrinho.calcularValorFrete() == 0.0);
    }
}

TEST_CASE("Carrinho - casos invalidos") {

    Cliente cliente("99999999999");
    Carrinho carrinho(cliente);

    Produto livro1(1, "Livro Teste", "X", 100.0f, 5);

    SUBCASE("Quantidade zero nao adiciona") {
        carrinho.adicionarProduto(livro1, 0);
        CHECK(carrinho.vazio() == true);
    }

    SUBCASE("Quantidade negativa nao adiciona") {
        carrinho.adicionarProduto(livro1, -2);
        CHECK(carrinho.vazio() == true);
    }

    SUBCASE("Estoque insuficiente ignora produto") {
        carrinho.adicionarProduto(livro1, 10);
        CHECK(carrinho.vazio() == true);
    }

    SUBCASE("Atualizar para negativo nao altera") {
        carrinho.adicionarProduto(livro1, 1);
        carrinho.atualizarQuantidade(1, -5);

        CHECK(carrinho.getQuantidadeItens() == 1);
    }

    SUBCASE("Remover produto inexistente nao quebra") {
        carrinho.removerProduto(999);
        CHECK(carrinho.vazio() == true);
    }
}