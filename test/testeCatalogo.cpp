#include "doctest.h"
#include "../include/Catalogo.hpp"
#include "../include/Produto.hpp"

TEST_CASE("Criacao do catalogo") {
    Catalogo catalogo;
    CHECK(true);
}

TEST_CASE("Adicionar produto ao catalogo") {
    Catalogo catalogo;
    Produto livro(1, "Livro Teste", "Descricao", 29.90f, 5);
    catalogo.adicionarProduto(livro);
    CHECK(true);
}

TEST_CASE("Buscar item no catalogo") {
    Catalogo catalogo;
    catalogo.buscarItem("Harry Potter");
    CHECK(false);
}

TEST_CASE("Ordenar catalogo por preco") {
    Catalogo catalogo;
    catalogo.ordenarPreco(true);
    CHECK(false);
}

TEST_CASE("Listar produtos por categoria") {
    Catalogo catalogo;
    catalogo.listarProdutosCategoria(CategoriaProduto::Ficcao);
    CHECK(false);
}

TEST_CASE("Exibir descricao de produto") {
    Catalogo catalogo;
    catalogo.exibirDescricao(1);
    CHECK(false);
}

TEST_CASE("Remover produto do catalogo") {
    Catalogo catalogo;
    catalogo.removerProduto(1);
    CHECK(false);
}

TEST_CASE("Criacao de resumo de pedido") {
    Catalogo::ResumoPedido pedido;
    pedido.idPedido = 10;
    pedido.nomeCliente = "Kayke";
    pedido.enderecoEntrega = "Acre";
    pedido.valorTotal = 120.50;
    pedido.pagamentoAprovado = true;
    CHECK(pedido.idPedido == 10);
    CHECK(pedido.pagamentoAprovado == true);
}