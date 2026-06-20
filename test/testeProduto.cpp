#include "doctest.h"
#include <stdexcept>
#include "../include/Produto.hpp"

TEST_CASE("Testando a classe Produto - Fluxo Completo com Excecoes") {

    Produto p(1, "A Fundação", "Ficção científica de Isaac Asimov", 50.00, 10, CategoriaProduto::Ficcao);

    SUBCASE("Validação dos métodos de leitura (Getters)") {
        CHECK(p.getId() == 1);
        CHECK(p.getNome() == "A Fundação");
        CHECK(p.getDescricao() == "Ficção científica de Isaac Asimov");
        CHECK(p.getPreco() == 50.00);
        CHECK(p.getQuantidadeEstoque() == 10);
        CHECK(p.getCategoria() == CategoriaProduto::Ficcao);
    }

    SUBCASE("Construtor barrando valores inválidos (Exceções)") {

        CHECK_THROWS_AS(Produto(2, "Livro", "Desc", -10.0, 5, CategoriaProduto::Tecnico), std::invalid_argument);
        CHECK_THROWS_AS(Produto(3, "Livro", "Desc", 10.0, -5, CategoriaProduto::Tecnico), std::invalid_argument);
    }

    SUBCASE("Testando alteração de preço (Setters)") {
        CHECK_NOTHROW(p.setPreco(60.50));
        CHECK(p.getPreco() == 60.50);

        CHECK_THROWS_AS(p.setPreco(-10.00), std::invalid_argument);
        CHECK(p.getPreco() == 60.50); 
    }

    SUBCASE("Testando a gestão de estoque defensiva") {
        CHECK_NOTHROW(p.adicionarEstoque(5));
        CHECK(p.getQuantidadeEstoque() == 15);

        CHECK_THROWS_AS(p.adicionarEstoque(-2), std::invalid_argument);
        CHECK(p.getQuantidadeEstoque() == 15); 

        CHECK(p.debitarEstoque(5) == true);
        CHECK(p.getQuantidadeEstoque() == 10);

        CHECK(p.debitarEstoque(20) == false);
        CHECK(p.getQuantidadeEstoque() == 10);

        CHECK(p.debitarEstoque(-5) == false);
        CHECK(p.getQuantidadeEstoque() == 10);
    }
}