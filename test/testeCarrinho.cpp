#include "doctest.h"

#include "Carrinho.hpp"
#include "Produto.hpp"
#include "Cliente.hpp"

#include <cstdio>
#include <fstream>

static void limparArquivoCarrinho() {
    std::remove("Carrinho.txt");
}

TEST_CASE("Carrinho - adicionar produtos validos") {
    limparArquivoCarrinho();

    Cliente cliente("Cliente Teste", "cliente@email.com", "senha123", "52998224725", "escola");
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

TEST_CASE("Carrinho - lanca excecao para quantidade invalida") {
    limparArquivoCarrinho();

    Cliente cliente("Cliente Teste", "cliente2@email.com", "senha123", "39053344705", "escola");
    Carrinho carrinho(cliente);

    Produto livro(1, "Livro Teste", "Descricao", 80.0f, 3, CategoriaProduto::Ficcao);

    CHECK_THROWS_AS(carrinho.adicionarProduto(livro, 0), QuantidadeInvalidaException);
    CHECK_THROWS_AS(carrinho.adicionarProduto(livro, -2), QuantidadeInvalidaException);

    CHECK(carrinho.getProdutos().empty());
    CHECK(carrinho.getQuantidades().empty());
}

TEST_CASE("Carrinho - lanca excecao para estoque insuficiente") {
    limparArquivoCarrinho();

    Cliente cliente("Cliente Teste", "cliente7@email.com", "senha123", "11144477735", "escola");
    Carrinho carrinho(cliente);

    Produto livro(1, "Livro Estoque", "Descricao", 80.0f, 3, CategoriaProduto::Ficcao);

    CHECK_THROWS_AS(carrinho.adicionarProduto(livro, 10), EstoqueInsuficienteException);

    carrinho.adicionarProduto(livro, 2);

    CHECK_THROWS_AS(carrinho.adicionarProduto(livro, 2), EstoqueInsuficienteException);
    CHECK(carrinho.getQuantidades()[0] == 2);
}

TEST_CASE("Carrinho - lanca excecao para produto invalido") {
    limparArquivoCarrinho();

    Cliente cliente("Cliente Teste", "cliente8@email.com", "senha123", "15350946056", "escola");
    Carrinho carrinho(cliente);

    Produto produtoInvalido(0, "Produto Invalido", "Descricao", 50.0f, 10, CategoriaProduto::Ficcao);

    CHECK_THROWS_AS(carrinho.adicionarProduto(produtoInvalido, 1), std::invalid_argument);
}

TEST_CASE("Carrinho - atualizar e remover produto") {
    limparArquivoCarrinho();

    Cliente cliente("Cliente Teste", "cliente3@email.com", "senha123", "93541134780", "escola");
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

TEST_CASE("Carrinho - lanca excecao ao remover produto inexistente") {
    limparArquivoCarrinho();

    Cliente cliente("Cliente Teste", "cliente9@email.com", "senha123", "11144477735", "escola");
    Carrinho carrinho(cliente);

    CHECK_THROWS_AS(carrinho.removerProduto(999), ProdutoNaoEncontradoException);
}

TEST_CASE("Carrinho - lanca excecao ao atualizar produto inexistente ou quantidade invalida") {
    limparArquivoCarrinho();

    Cliente cliente("Cliente Teste", "cliente10@email.com", "senha123", "15350946056", "escola");
    Carrinho carrinho(cliente);

    Produto livro(1, "Livro Atualizar", "Descricao", 40.0f, 5, CategoriaProduto::Ficcao);

    CHECK_THROWS_AS(carrinho.atualizarQuantidade(1, -1), QuantidadeInvalidaException);
    CHECK_THROWS_AS(carrinho.atualizarQuantidade(999, 1), ProdutoNaoEncontradoException);

    carrinho.adicionarProduto(livro, 2);

    CHECK_THROWS_AS(carrinho.atualizarQuantidade(1, 10), EstoqueInsuficienteException);
    CHECK(carrinho.getQuantidades()[0] == 2);
}

TEST_CASE("Carrinho - atualizar quantidade para zero remove produto") {
    limparArquivoCarrinho();

    Cliente cliente("Cliente Teste", "cliente11@email.com", "senha123", "93541134780", "escola");
    Carrinho carrinho(cliente);

    Produto livro(1, "Livro Zero", "Descricao", 60.0f, 5, CategoriaProduto::Ficcao);

    carrinho.adicionarProduto(livro, 2);
    carrinho.atualizarQuantidade(1, 0);

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

    Cliente cliente("Cliente Teste", "cliente5@email.com", "senha123", "52998224725", "escola");
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

    Cliente cliente("Cliente Teste", "cliente6@email.com", "senha123", "11144477735", "escola");

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

TEST_CASE("Carrinho - ignora linhas invalidas ao carregar arquivo") {
    limparArquivoCarrinho();

    Cliente cliente("Cliente Teste", "cliente12@email.com", "senha123", "52998224725", "escola");

    std::ofstream arquivo("Carrinho.txt");

    arquivo << cliente.getCpf() << std::endl;
    arquivo << "linha_invalida" << std::endl;
    arquivo << "abc,Livro Ruim,50,10,1" << std::endl;
    arquivo << "2,Livro Valido,45,10,2" << std::endl;
    arquivo << "3,Livro Estoque Invalido,30,1,5" << std::endl;
    arquivo << "END" << std::endl;

    arquivo.close();

    Carrinho carrinho(cliente);

    REQUIRE(carrinho.getProdutos().size() == 1);
    REQUIRE(carrinho.getQuantidades().size() == 1);

    CHECK(carrinho.getProdutos()[0].getId() == 2);
    CHECK(carrinho.getProdutos()[0].getNome() == "Livro Valido");
    CHECK(carrinho.getQuantidades()[0] == 2);

    limparArquivoCarrinho();
}

TEST_CASE("Carrinho - incrementa quantidade de produto ja existente") {
    limparArquivoCarrinho();

    Cliente cliente("Cliente Teste", "cliente13@email.com", "senha123", "52998224725", "escola");
    Carrinho carrinho(cliente);

    Produto livro(1, "Livro Repetido", "Descricao", 25.0f, 10, CategoriaProduto::Ficcao);

    carrinho.adicionarProduto(livro, 2);
    carrinho.adicionarProduto(livro, 3);

    REQUIRE(carrinho.getProdutos().size() == 1);
    REQUIRE(carrinho.getQuantidades().size() == 1);

    CHECK(carrinho.getQuantidades()[0] == 5);
    CHECK(carrinho.calcularSubtotal() == doctest::Approx(125.0));
}

TEST_CASE("Carrinho - preserva carrinho de outro cliente ao salvar") {
    limparArquivoCarrinho();

    Cliente cliente("Cliente Teste", "cliente14@email.com", "senha123", "52998224725", "escola");

    std::ofstream arquivo("Carrinho.txt");
    arquivo << "15350946056" << std::endl;
    arquivo << "9,Livro Outro Cliente,20,5,1" << std::endl;
    arquivo << "END" << std::endl;
    arquivo.close();

    Carrinho carrinho(cliente);

    Produto livro(1, "Livro Cliente Atual", "Descricao", 30.0f, 5, CategoriaProduto::Ficcao);
    carrinho.adicionarProduto(livro, 1);

    std::ifstream leitura("Carrinho.txt");
    std::string conteudo;
    std::string linha;

    while (std::getline(leitura, linha)) {
        conteudo += linha + "\n";
    }

    CHECK(conteudo.find("15350946056") != std::string::npos);
    CHECK(conteudo.find("Livro Outro Cliente") != std::string::npos);
    CHECK(conteudo.find(cliente.getCpf()) != std::string::npos);
    CHECK(conteudo.find("Livro Cliente Atual") != std::string::npos);

    limparArquivoCarrinho();
}