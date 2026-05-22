#include "doctest.h"
#include "../include/Pedido.hpp"
#include "../include/Cliente.hpp"
#include "../include/Carrinho.hpp"
#include "../include/Produto.hpp"
#include <string>

TEST_CASE("Teste do Pedido - INICIALIZACAO E CASOS BASE") {
    Cliente clienteFake("Joyce", "joyce@email.com", "senha123", "52998224725");
    Carrinho carrinhoFake(clienteFake);
    Produto livro(1, "Livro Teste", "Descricao", 50.0f, 10);
    carrinhoFake.adicionarProduto(livro, 1);
    Pedido pedido(carrinhoFake, clienteFake);
    CHECK(pedido.getStatus() == Pedido::StatusPedido::Pendente);
    CHECK(pedido.getvalorTotal() == doctest::Approx(70.0));
}

TEST_CASE("Teste do valor do frete") {
    Cliente clienteFake("Joyce", "joyce@email.com", "senha123", "52998224725");
    Carrinho carrinhoFake(clienteFake);
    Pedido pedido(carrinhoFake, clienteFake);
    pedido.informarValorFrete("Rua Exemplo, 123, Belo Horizonte, MG");
}

TEST_CASE("Teste da estimativa de entrega") {
    Cliente clienteFake("Joyce", "joyce@email.com", "senha123", "52998224725");
    Carrinho carrinhoFake(clienteFake);
    Pedido pedido(carrinhoFake, clienteFake);
    std::string estimativa = pedido.estimarDataEntrega("Rua Exemplo, 123, Belo Horizonte, MG");
    CHECK(estimativa == "Prazo estimado: 2 a 3 dias úteis, a partir da confirmação de pagamento");
    estimativa = pedido.estimarDataEntrega("Rua Exemplo, 456, São Paulo, SP");
    CHECK(estimativa == "Prazo estimado: 7 a 10 dias úteis, a partir da confirmação de pagamento.");
}

TEST_CASE("Teste do processamento de pagamento via Pix") {
    Cliente clienteFake("Joyce", "joyce@email.com", "senha123", "52998224725");
    Carrinho carrinhoFake(clienteFake);
    Pedido pedido(carrinhoFake, clienteFake);
    pedido.processarPagamentos(Pedido::MetodoPagamento::Pix);
    CHECK(pedido.getStatus() == Pedido::StatusPedido::Pago);
}

TEST_CASE("Teste do processamento de pagamento via Cartão Crédito") {
    Cliente clienteFake("Joyce", "joyce@email.com", "senha123", "52998224725");
    Carrinho carrinhoFake(clienteFake);
    Pedido pedido(carrinhoFake, clienteFake);
    pedido.processarPagamentos(Pedido::MetodoPagamento::Credito);
    CHECK(pedido.getStatus() == Pedido::StatusPedido::Pago);
}

TEST_CASE("Teste do processamento de pagamento via Cartão DEBITO") {
    Cliente clienteFake("Joyce", "joyce@email.com", "senha123", "52998224725");
    Carrinho carrinhoFake(clienteFake);
    Pedido pedido(carrinhoFake, clienteFake);
    pedido.processarPagamentos(Pedido::MetodoPagamento::Debito);
    CHECK(pedido.getStatus() == Pedido::StatusPedido::Pago);
}