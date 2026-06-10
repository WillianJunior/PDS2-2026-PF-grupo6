#include "Pedido.hpp"
#include "Cliente.hpp"
#include "Carrinho.hpp"
#include "doctest.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>


TEST_CASE("Teste de Unidade Isolado - Ciclo de Vida do Pedido") {
    Cliente clienteMock("Nome", "email", "senha", "11144477735", "Resposta");
    Carrinho carrinhoMock(clienteMock);

    Pedido pedido(carrinhoMock, clienteMock);

    SUBCASE("Cenário 1: Inicialização e Faturamento do Construtor") {
        CHECK(pedido.getValorTotal() == 125.00);
        CHECK(pedido.getValorFrete() == 25.00);
        CHECK(pedido.getStatus() == Pedido::StatusPedido::Pendente);

    }

    SUBCASE("Cenário 2: Regras de Estimativa Logística de Entrega") {
        std::string prazoLocal = pedido.estimarDataEntrega(clienteMock.getEndereco());
        CHECK(prazoLocal.find("2 a 3 dias úteis") != std::string::npos);

        std::string prazoExterno = pedido.estimarDataEntrega("Av. Paulista, 1000, São Paulo, SP");
        CHECK(prazoExterno.find("7 a 10 dias úteis") != std::string::npos);
    }

    SUBCASE("Cenário 3: Fluxo de Transição e Confirmação de Pagamento") {
        pedido.processarPagamentos(Pedido::MetodoPagamento::Pix);
        CHECK(pedido.getStatus() == Pedido::StatusPedido::Pago);
    }

    SUBCASE("Cenário 4: Geração de Cupom Fiscal e Escrita em Arquivo") {
        pedido.salvarEmArquivo(clienteMock);
        std::string nomeArquivoEsperado = "pedido_11144477735.txt";
        
        std::ifstream arquivo(nomeArquivoEsperado);
        REQUIRE(arquivo.is_open() == true);

        std::string linha;
        bool possuiCpfGravado = false;
        bool possuiEnderecoGravado = false;

        while (std::getline(arquivo, linha)) {
            if (linha.find("11144477735") != std::string::npos) {
                possuiCpfGravado = true;
            }
            if (linha.find("Belo Horizonte") != std::string::npos) {
                possuiEnderecoGravado = true;
            }
        }
        arquivo.close();

        CHECK(possuiCpfGravado == true);
        CHECK(possuiEnderecoGravado == true);

        std::remove(nomeArquivoEsperado.c_str());
    }
}
