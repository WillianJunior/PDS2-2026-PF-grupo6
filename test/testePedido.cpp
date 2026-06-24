//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "Pedido.hpp"
#include "Cliente.hpp"
#include "Carrinho.hpp"
#include "Produto.hpp"

#include <fstream>
#include <string>
#include <cstdio>
#include <stdexcept>

TEST_CASE("Teste de Unidade Isolado - Classe Pedido") {

    Cliente clienteMock(
        "Joao Silva",
        "joao@email.com",
        "senha123",
        "11144477735",
        "Resposta"
    );

    clienteMock.adicionarEndereco(
        "Rua das Flores, 123, Belo Horizonte, MG"
    );

    Carrinho carrinhoMock(clienteMock);

    carrinhoMock.limparCarrinho();

    Produto produtoMock(
        1,
        "Livro Teste",
        "Descricao do livro",
        100.0f,
        10,
        CategoriaProduto::Tecnico
    );

    carrinhoMock.adicionarProduto(
        produtoMock,
        1
    );

    Pedido pedido(
        carrinhoMock,
        clienteMock
    );

    SUBCASE("Construtor inicializa corretamente") {

        CHECK(
            pedido.getValorFrete() ==
            doctest::Approx(15.0)
        );

        CHECK(
            pedido.getValorTotal() ==
            doctest::Approx(115.0)
        );

        CHECK(
            pedido.getStatus() ==
            Pedido::StatusPedido::Pendente
        );
    }

    SUBCASE("Informar valor do frete") {

        std::string resultado =
            pedido.informarValorFrete(
                clienteMock.getEndereco()
            );

        CHECK(
            resultado.find("15.00")
            != std::string::npos
        );
    }

    SUBCASE("Entrega para MG") {

        std::string prazo =
            pedido.estimarDataEntrega(
                clienteMock.getEndereco()
            );

        CHECK(
            prazo.find("2 a 3 dias")
            != std::string::npos
        );
    }

    SUBCASE("Entrega fora de MG") {

        std::string prazo =
            pedido.estimarDataEntrega(
                "Av. Paulista, Sao Paulo, SP"
            );

        CHECK(
            prazo.find("7 a 10 dias")
            != std::string::npos
        );
    }

    SUBCASE("Pagamento via PIX") {

        std::string resultado =
            pedido.processarPagamentos(
                Pedido::MetodoPagamento::Pix
            );

        CHECK(
            resultado.find(
                "Pagamento confirmado"
            ) != std::string::npos
        );

        CHECK(
            pedido.getStatus() ==
            Pedido::StatusPedido::Pago
        );
    }

    SUBCASE("Pagamento via Credito") {

        std::string resultado =
            pedido.processarPagamentos(
                Pedido::MetodoPagamento::Credito
            );

        CHECK(
            resultado.find(
                "Pagamento confirmado"
            ) != std::string::npos
        );

        CHECK(
            pedido.getStatus() ==
            Pedido::StatusPedido::Pago
        );
    }

    SUBCASE("Pagamento via Debito") {

        std::string resultado =
            pedido.processarPagamentos(
                Pedido::MetodoPagamento::Debito
            );

        CHECK(
            resultado.find(
                "Pagamento confirmado"
            ) != std::string::npos
        );

        CHECK(
            pedido.getStatus() ==
            Pedido::StatusPedido::Pago
        );
    }

    SUBCASE("Resumo de faturamento") {

        std::string resumo =
            pedido.gerarResumoFaturamento(
                clienteMock,
                carrinhoMock
            );

        CHECK(
            resumo.find("Subtotal")
            != std::string::npos
        );

        CHECK(
            resumo.find("Frete")
            != std::string::npos
        );

        CHECK(
            resumo.find("Total")
            != std::string::npos
        );
    }

    SUBCASE("Mensagem aguardando pagamento") {

        CHECK(
            pedido.exibirMensagemConfirmacao()
            ==
            "Aguardando pagamento.\n"
        );
    }

    SUBCASE("Mensagem pagamento confirmado") {

        pedido.processarPagamentos(
            Pedido::MetodoPagamento::Pix
        );

        CHECK(
            pedido.exibirMensagemConfirmacao()
            ==
            "Pagamento confirmado!\n"
        );
    }

    SUBCASE("Mudanca de status") {

        pedido.gerenciarStatus(
            Pedido::StatusPedido::Enviado
        );

        CHECK(
            pedido.getStatus()
            ==
            Pedido::StatusPedido::Enviado
        );

        pedido.gerenciarStatus(
            Pedido::StatusPedido::Entregue
        );

        CHECK(
            pedido.getStatus()
            ==
            Pedido::StatusPedido::Entregue
        );
    }

    SUBCASE("Salvar pedido em arquivo") {

        pedido.salvarEmArquivo(
            clienteMock,
            carrinhoMock
        );

        std::string nomeArquivo =
            "pedido_11144477735.txt";

        std::ifstream arquivo(
            nomeArquivo
        );

        REQUIRE(
            arquivo.is_open()
        );

        std::string linha;

        bool encontrouCpf = false;
        bool encontrouEndereco = false;
        bool encontrouProduto = false;

        while (
            std::getline(
                arquivo,
                linha
            )
        ) {

            if (
                linha.find(
                    "11144477735"
                )
                != std::string::npos
            ) {
                encontrouCpf = true;
            }

            if (
                linha.find(
                    "Belo Horizonte"
                )
                != std::string::npos
            ) {
                encontrouEndereco = true;
            }

            if (
                linha.find(
                    "Livro Teste"
                )
                != std::string::npos
            ) {
                encontrouProduto = true;
            }
        }

        arquivo.close();

        CHECK(encontrouCpf);
        CHECK(encontrouEndereco);
        CHECK(encontrouProduto);

        std::remove(
            nomeArquivo.c_str()
        );
    }

    SUBCASE("Excecao endereco vazio para entrega") {

        CHECK_THROWS_AS(
            pedido.estimarDataEntrega(""),
            std::invalid_argument
        );
    }

    SUBCASE("Excecao endereco vazio para frete") {

        CHECK_THROWS_AS(
            pedido.informarValorFrete(""),
            std::invalid_argument
        );
    }

    SUBCASE("Excecao pagamento duplicado") {

        pedido.processarPagamentos(
            Pedido::MetodoPagamento::Pix
        );

        CHECK_THROWS_AS(
            pedido.processarPagamentos(
                Pedido::MetodoPagamento::Pix
            ),
            std::runtime_error
        );
    }

    SUBCASE("Excecao pagamento apos envio") {

        pedido.gerenciarStatus(
            Pedido::StatusPedido::Enviado
        );

        CHECK_THROWS_AS(
            pedido.processarPagamentos(
                Pedido::MetodoPagamento::Pix
            ),
            std::runtime_error
        );
    }

    SUBCASE("Excecao carrinho vazio") {

        Carrinho vazio(clienteMock);

        vazio.limparCarrinho();

        CHECK_THROWS_AS(
            Pedido(
                vazio,
                clienteMock
            ),
            std::runtime_error
        );
    }
}