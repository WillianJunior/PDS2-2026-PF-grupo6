#include "doctest.h"
#include "Estoque.hpp"
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

static void removerArquivo(const std::string& nome) {
    std::remove(nome.c_str());
}

static void criarArquivoEstoque(
        const std::string& nome,
        const std::string& conteudo) {

    std::ofstream f(nome);
    f << conteudo;
}

// ── Construtor ───────────────────────────────────────

TEST_CASE("Estoque - produtos padrao quando arquivo nao existe") {

    const std::string arquivo = "te_padrao.txt";
    removerArquivo(arquivo);

    Estoque estoque(arquivo);

    std::vector<Produto> inv = estoque.obterInventario();
    CHECK(!inv.empty());

    CHECK(estoque.impedirVendasAcimaMaximo(1, 1) == true);

    removerArquivo(arquivo);
}

TEST_CASE("Estoque - carrega produtos do arquivo existente") {

    const std::string arquivo = "te_carrega.txt";

    criarArquivoEstoque(arquivo,
        "1;Livro A;Descricao A;49.90;8;Ficcao\n"
        "2;Livro B;Descricao B;29.90;0;Romance\n");

    Estoque estoque(arquivo);

    CHECK(estoque.impedirVendasAcimaMaximo(1, 8) == true);
    CHECK(estoque.impedirVendasAcimaMaximo(1, 9) == false);
    CHECK(estoque.impedirVendasAcimaMaximo(2, 1) == false);

    removerArquivo(arquivo);
}

TEST_CASE("Estoque - obterInventario retorna vetor populado") {

    const std::string arquivo = "te_disp.txt";
    removerArquivo(arquivo);

    Estoque estoque(arquivo);

    std::vector<Produto> inventario = estoque.obterInventario();

    CHECK(!inventario.empty());

    removerArquivo(arquivo);
}

TEST_CASE("Estoque - alerta produtos com estoque critico") {

    const std::string arquivo = "te_critico.txt";
    removerArquivo(arquivo);

    Estoque estoque(arquivo);

    std::vector<Produto> alertas = estoque.obterProdutosEmAlerta();

    CHECK(alertas.size() == 2);

    removerArquivo(arquivo);
}

TEST_CASE("Estoque - sem alerta quando todos em estoque suficiente") {

    const std::string arquivo = "te_sem_alerta.txt";

    criarArquivoEstoque(arquivo,
        "1;Livro A;Desc;49.90;10;Ficcao\n"
        "2;Livro B;Desc;29.90;20;Romance\n");

    Estoque estoque(arquivo);

    std::vector<Produto> alertas = estoque.obterProdutosEmAlerta();

    CHECK(alertas.empty());

    removerArquivo(arquivo);
}

TEST_CASE("Estoque - congelarQuantidades valido") {

    const std::string arquivo = "te_cong_ok.txt";
    removerArquivo(arquivo);

    Estoque estoque(arquivo);

    CHECK_NOTHROW(estoque.congelarQuantidades(1, 5));

    removerArquivo(arquivo);
}

TEST_CASE("Estoque - congelarQuantidades quantidade invalida") {

    const std::string arquivo = "te_cong_inv.txt";
    removerArquivo(arquivo);

    Estoque estoque(arquivo);

    CHECK_THROWS_AS(
        estoque.congelarQuantidades(1, 0),
        std::invalid_argument);

    CHECK_THROWS_AS(
        estoque.congelarQuantidades(1, -1),
        std::invalid_argument);

    removerArquivo(arquivo);
}

TEST_CASE("Estoque - congelarQuantidades produto nao encontrado") {

    const std::string arquivo = "te_cong_nf.txt";
    removerArquivo(arquivo);

    Estoque estoque(arquivo);

    CHECK_THROWS_AS(
        estoque.congelarQuantidades(999, 1),
        std::runtime_error);

    removerArquivo(arquivo);
}

TEST_CASE("Estoque - congelarQuantidades estoque insuficiente") {

    const std::string arquivo = "te_cong_ins.txt";
    removerArquivo(arquivo);

    Estoque estoque(arquivo);

    CHECK_THROWS_AS(
        estoque.congelarQuantidades(1, 11),
        std::runtime_error);

    removerArquivo(arquivo);
}


TEST_CASE("Estoque - efetuarSubtracao valido") {

    const std::string arquivo = "te_sub_ok.txt";

    criarArquivoEstoque(arquivo,
        "1;Livro A;Desc;49.90;10;Ficcao\n");

    Estoque estoque(arquivo);

    CHECK_NOTHROW(estoque.efetuarSubtracao(1, 3));

    CHECK(estoque.impedirVendasAcimaMaximo(1, 7) == true);
    CHECK(estoque.impedirVendasAcimaMaximo(1, 8) == false);

    removerArquivo(arquivo);
}

TEST_CASE("Estoque - efetuarSubtracao quantidade invalida") {

    const std::string arquivo = "te_sub_inv.txt";
    removerArquivo(arquivo);

    Estoque estoque(arquivo);

    CHECK_THROWS_AS(
        estoque.efetuarSubtracao(1, 0),
        std::invalid_argument);

    CHECK_THROWS_AS(
        estoque.efetuarSubtracao(1, -5),
        std::invalid_argument);

    removerArquivo(arquivo);
}

TEST_CASE("Estoque - efetuarSubtracao produto nao encontrado") {

    const std::string arquivo = "te_sub_nf.txt";
    removerArquivo(arquivo);

    Estoque estoque(arquivo);

    CHECK_THROWS_AS(
        estoque.efetuarSubtracao(999, 1),
        std::runtime_error);

    removerArquivo(arquivo);
}

TEST_CASE("Estoque - efetuarSubtracao estoque insuficiente") {

    const std::string arquivo = "te_sub_ins.txt";

    criarArquivoEstoque(arquivo,
        "3;Design Patterns;Desc;120.00;0;Tecnico\n");

    Estoque estoque(arquivo);

    CHECK_THROWS_AS(
        estoque.efetuarSubtracao(3, 1),
        std::runtime_error);

    removerArquivo(arquivo);
}


TEST_CASE("Estoque - impedirVendasAcimaMaximo") {

    const std::string arquivo = "te_impedir.txt";

    criarArquivoEstoque(arquivo,
        "1;Livro A;Desc;49.90;5;Ficcao\n");

    Estoque estoque(arquivo);

    CHECK(estoque.impedirVendasAcimaMaximo(1, 5) == true);
    CHECK(estoque.impedirVendasAcimaMaximo(1, 6) == false);

    CHECK(estoque.impedirVendasAcimaMaximo(99, 1) == false);

    removerArquivo(arquivo);
}


TEST_CASE("Estoque - persistencia entre execucoes") {

    const std::string arquivo = "te_persist.txt";
    removerArquivo(arquivo);

    {
        Estoque estoque(arquivo);
        estoque.efetuarSubtracao(1, 2);
    }

    {
        Estoque estoque(arquivo);
        CHECK(estoque.impedirVendasAcimaMaximo(1, 8) == true);
        CHECK(estoque.impedirVendasAcimaMaximo(1, 9) == false);
    }

    removerArquivo(arquivo);
}