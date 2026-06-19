#include "Pedido.hpp"
#include "Cliente.hpp"
#include "Carrinho.hpp"
#include "Produto.hpp"
#include "doctest.h" 
#include <fstream>
#include <string>
#include <cstdio>
#include <stdexcept>

TEST_CASE("Teste de Unidade - Pedido") {
    std::remove("Carrinho.txt");
    
    Cliente cliente("Nome", "email@teste.com", "senha123", "11144477735", "RespostaSeguranca");
    cliente.adicionarEndereco("Belo Horizonte, MG");

    Carrinho carrinho(cliente);
    Produto livro(1, "Livro Ficção A", "Descrição", 100.00, 10, CategoriaProduto::Ficcao);

    SUBCASE("Caminho Feliz: Construtor, Logística e Pagamento") {
        carrinho.adicionarProduto(livro, 1); // Subtotal=100, Frete=15, Total=115
        Pedido pedido(carrinho, cliente);

        CHECK(pedido.getValorTotal() == 115.00);
        CHECK(pedido.getValorFrete() == 15.00);
        CHECK(pedido.getStatus() == Pedido::StatusPedido::Pendente);

        CHECK(pedido.estimarDataEntrega(cliente.getEndereco()).find("2 a 3 dias úteis") != std::string::npos);
        CHECK(pedido.estimarDataEntrega("Outro Estado, SP").find("7 a 10 dias úteis") != std::string::npos);

        pedido.processarPagamentos(Pedido::MetodoPagamento::Pix);
        CHECK(pedido.getStatus() == Pedido::StatusPedido::Pago);
        
        CHECK_THROWS_AS(pedido.processarPagamentos(Pedido::MetodoPagamento::Credito), std::runtime_error);
    }

    SUBCASE("Exceções: Barricadas do Construtor e Métodos Públicos") {
        // Carrinho vazio
        CHECK_THROWS_AS(Pedido(carrinho, cliente), std::invalid_argument);

        carrinho.adicionarProduto(livro, 1);
        Pedido pedidoValido(carrinho, cliente);

        Cliente cSemCpf("Nome", "email@teste.com", "senha123", "", "RespostaSeguranca");
        cSemCpf.adicionarEndereco("Belo Horizonte, MG");

        Cliente cSemEnd("Nome", "email@teste.com", "senha123", "11144477735", "RespostaSeguranca");
     

        CHECK_THROWS_AS(Pedido(carrinho, cSemCpf), std::invalid_argument);
        CHECK_THROWS_AS(Pedido(carrinho, cSemEnd), std::invalid_argument);

        CHECK_THROWS_AS(pedidoValido.estimarDataEntrega(""), std::invalid_argument);
        CHECK_THROWS_AS(pedidoValido.informarValorFrete(""), std::invalid_argument);
        
        auto pagamentoInvalido = static_cast<Pedido::MetodoPagamento>(999);
        CHECK_THROWS_AS(pedidoValido.processarPagamentos(pagamentoInvalido), std::invalid_argument);
    }

    SUBCASE("Persistência: Escrita em Arquivo e Barricada") {
        carrinho.adicionarProduto(livro, 1);
        Pedido pedido(carrinho, cliente);
        
        pedido.salvarEmArquivo(cliente);
        std::string arquivoNome = "pedido_11144477735.txt";
        
        std::ifstream arquivo(arquivoNome);
        REQUIRE(arquivo.is_open() == true);
        arquivo.close();

        Cliente cInvalido("Nome", "email@teste.com", "senha123", "", "RespostaSeguranca"); 
        
        CHECK_THROWS_AS(pedido.salvarEmArquivo(cInvalido), std::invalid_argument);

        std::remove(arquivoNome.c_str());
    }

    std::remove("Carrinho.txt");
}
