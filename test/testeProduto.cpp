#include "doctest.h"
#include "Produto.hpp"

TEST_CASE("Testando a classe Produto") {
    Produto p(1, "A Fundação", "Ficção científica de Isaac Asimov", 50.00, 10);

    SUBCASE("Validação dos métodos de leitura (Getters)") {
        CHECK(p.getId() == 1);
        CHECK(p.getNome() == "A Fundação");
        CHECK(p.getDescricao() == "Ficção científica de Isaac Asimov");
        CHECK(p.getPreco() == 50.00);
        CHECK(p.getQuantidadeEstoque() == 10);
    }
}
