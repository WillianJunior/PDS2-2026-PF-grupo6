#include "doctest.h"
#include "../include/Estoque.hpp"

TEST_CASE("Estoque - construtor nao lanca excecao") {
    CHECK_NOTHROW(Estoque());
}

TEST_CASE("Estoque - exibirQuantidadeDisponiveis nao lanca excecao") {
    Estoque e;
    CHECK_NOTHROW(e.exibirQuantidadeDisponiveis());
}

TEST_CASE("Estoque - alertarEstoqueCritico nao lanca excecao") {
    Estoque e;
    CHECK_NOTHROW(e.alertarEstoqueCritico());
}

TEST_CASE("Estoque - impedirVendasAcimaMaximo permite venda valida") {
    Estoque e;
    CHECK(e.impedirVendasAcimaMaximo(1, 5)  == true);
    CHECK(e.impedirVendasAcimaMaximo(1, 10) == true);
    CHECK(e.impedirVendasAcimaMaximo(1, 11) == false);
}

TEST_CASE("Estoque - impedirVendasAcimaMaximo bloqueia produto sem estoque") {
    Estoque e;
    CHECK(e.impedirVendasAcimaMaximo(3, 1) == false);
}

TEST_CASE("Estoque - impedirVendasAcimaMaximo produto inexistente") {
    Estoque e;
    CHECK(e.impedirVendasAcimaMaximo(99, 1) == false);
}

TEST_CASE("Estoque - congelarQuantidades nao lanca excecao") {
    Estoque e;
    CHECK_NOTHROW(e.congelarQuantidades(1, 5));
    CHECK_NOTHROW(e.congelarQuantidades(99, 5));
}

TEST_CASE("Estoque - efetuarSubtracao nao lanca excecao") {
    Estoque e;
    CHECK_NOTHROW(e.efetuarSubtracao(1, 5));
    CHECK_NOTHROW(e.efetuarSubtracao(99, 5));
}