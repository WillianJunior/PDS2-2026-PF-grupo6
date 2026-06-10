#include "doctest.h"
#include "../include/Produto.hpp"

TEST_CASE("Testando a classe Produto - Fluxo Completo") {

    Produto p(1, "A Fundação", "Ficção científica de Isaac Asimov", 50.00, 10, CategoriaProduto::Ficcao);

    SUBCASE("Validação dos métodos de leitura (Getters)") {
        CHECK(p.getId() == 1);
        CHECK(p.getNome() == "A Fundação");
        CHECK(p.getDescricao() == "Ficção científica de Isaac Asimov");
        CHECK(p.getPreco() == 50.00);
        CHECK(p.getQuantidadeEstoque() == 10);
        CHECK(p.getCategoria() == CategoriaProduto::Ficcao);
    }

    SUBCASE("Testando alteração de preço (Setters)") {
  
        CHECK(p.setPreco(60.50) == true);
        CHECK(p.getPreco() == 60.50);

    
        CHECK(p.setPreco(-10.00) == false);
        CHECK(p.getPreco() == 60.50); 
    }

    SUBCASE("Testando a gestão de estoque") {
    
        p.adicionarEstoque(5);
        CHECK(p.getQuantidadeEstoque() == 15);

        p.adicionarEstoque(-2);
        CHECK(p.getQuantidadeEstoque() == 15);

        CHECK(p.debitarEstoque(5) == true);
        CHECK(p.getQuantidadeEstoque() == 10);

        CHECK(p.debitarEstoque(20) == false);
        CHECK(p.getQuantidadeEstoque() == 10);
    }
}