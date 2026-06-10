#include "doctest.h"

#include "Carrinho.hpp"
#include "Produto.hpp"
#include "Cliente.hpp"

#include <cstdio>

static void limparArquivoCarrinho() {
    std::remove("Carrinho.txt");
}

TEST_CASE("Carrinho - adicionar produtos validos") {
    limparArquivoCarrinho();

    Cliente cliente("Cliente Teste", "cliente@email.com", "senha123", "12345678909", "escola");
    Carrinho carrinho(cliente);

    Produto livro1(1, "Harry Potter", "Fantasia", 100.0f, 10, CategoriaProduto::Fantasia);
    Produto livro2(2, "Morte no Nilo", "Suspense", 150.0f, 5, CategoriaProduto::Suspense);

    carrinho.adicionarProduto(livro1, 2);
    carrinho.adicionarProduto(livro2, 1);

    CHECK(carrinho.getProdutos().size() == 2);
    CHECK(carrinho.getQuantidades().size() == 2);
    CHECK(carrinho.getQuantidades()[0] == 2);
    CHECK(carrinho.getQuantidades()[1] == 1);
    CHECK(carrinho.calcularSubtotal() == doctest::Approx(350.0));
}

TEST_CASE("Carrinho - nao adiciona quantidade invalida ou estoque insuficiente") {
    limparArquivoCarrinho();

    Cliente cliente("Cliente Teste", "cliente2@email.com", "senha123", "98765432100", "escola");
    Carrinho carrinho(cliente);

    Produto livro(1, "Livro Teste", "Descricao", 80.0f, 3, CategoriaProduto::Ficcao);

    carrinho.adicionarProduto(livro, 0);
    CHECK(carrinho.getProdutos().empty());

    carrinho.adicionarProduto(livro, -2);
    CHECK(carrinho.getProdutos().empty());

    carrinho.adicionarProduto(livro, 10);
    CHECK(carrinho.getProdutos().empty());
}

TEST_CASE("Carrinho - atualizar e remover produto") {
    limparArquivoCarrinho();

    Cliente cliente("Cliente Teste", "cliente3@email.com", "senha123", "11144477735", "escola");
    Carrinho carrinho(cliente);

    Produto livro(1, "Dom Casmurro", "Classico", 50.0f, 10, CategoriaProduto::Romance);

    carrinho.adicionarProduto(livro, 2);
    carrinho.atualizarQuantidade(1, 4);

    CHECK(carrinho.getProdutos().size() == 1);
    CHECK(carrinho.getQuantidades()[0] == 4);
    CHECK(carrinho.calcularSubtotal() == doctest::Approx(200.0));

    carrinho.removerProduto(1);

    CHECK(carrinho.getProdutos().empty());
    CHECK(carrinho.getQuantidades().empty());
}

TEST_CASE("Carrinho - regras de frete e total") {
    limparArquivoCarrinho();

    Cliente cliente("Cliente Teste", "cliente4@email.com", "senha123", "52998224725", "escola");
    Carrinho carrinho(cliente);

    Produto livro(1, "Livro A", "Descricao", 50.0f, 20, CategoriaProduto::Ficcao);

    CHECK(carrinho.calcularValorFrete() == doctest::Approx(0.0));

    carrinho.adicionarProduto(livro, 1);
    CHECK(carrinho.calcularSubtotal() == doctest::Approx(50.0));
    CHECK(carrinho.calcularValorFrete() == doctest::Approx(20.0));
    CHECK(carrinho.calcularTotal() == doctest::Approx(70.0));
    CHECK(carrinho.getValorTotal() == doctest::Approx(70.0));

    carrinho.atualizarQuantidade(1, 3);
    CHECK(carrinho.calcularSubtotal() == doctest::Approx(150.0));
    CHECK(carrinho.getValorFrete() == doctest::Approx(15.0));

    carrinho.atualizarQuantidade(1, 6);
    CHECK(carrinho.calcularSubtotal() == doctest::Approx(300.0));
    CHECK(carrinho.calcularValorFrete() == doctest::Approx(0.0));
}

TEST_CASE("Carrinho - limpar carrinho") {
    limparArquivoCarrinho();

    Cliente cliente("Cliente Teste", "cliente5@email.com", "senha123", "39053344705", "escola");
    Carrinho carrinho(cliente);

    Produto livro(1, "Livro Limpar", "Descricao", 30.0f, 10, CategoriaProduto::Ficcao);

    carrinho.adicionarProduto(livro, 3);
    CHECK(carrinho.getProdutos().size() == 1);

    carrinho.limparCarrinho();

    CHECK(carrinho.getProdutos().empty());
    CHECK(carrinho.getQuantidades().empty());
    CHECK(carrinho.calcularSubtotal() == doctest::Approx(0.0));
}

TEST_CASE("Carrinho - salvar e carregar arquivo txt") {
    limparArquivoCarrinho();

    Cliente cliente("Cliente Teste", "cliente6@email.com", "senha123", "15350946056", "escola");

    Produto livro(1, "Livro Arquivo", "Descricao", 75.0f, 8, CategoriaProduto::Ficcao);

    {
        Carrinho carrinho(cliente);
        carrinho.adicionarProduto(livro, 2);

        CHECK(carrinho.getProdutos().size() == 1);
        CHECK(carrinho.getQuantidades()[0] == 2);
    }

    {
        Carrinho carrinhoCarregado(cliente);

        REQUIRE(carrinhoCarregado.getProdutos().size() == 1);
        REQUIRE(carrinhoCarregado.getQuantidades().size() == 1);

        CHECK(carrinhoCarregado.getProdutos()[0].getId() == 1);
        CHECK(carrinhoCarregado.getProdutos()[0].getNome() == "Livro Arquivo");
        CHECK(carrinhoCarregado.getProdutos()[0].getPreco() == doctest::Approx(75.0));
        CHECK(carrinhoCarregado.getProdutos()[0].getQuantidadeEstoque() == 8);
        CHECK(carrinhoCarregado.getQuantidades()[0] == 2);
        CHECK(carrinhoCarregado.calcularSubtotal() == doctest::Approx(150.0));  
    }

    limparArquivoCarrinho();
}
