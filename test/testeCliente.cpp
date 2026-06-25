#include "doctest.h"
#include "Cliente.hpp"

#include <cstdio>
#include <stdexcept>
#include <sstream>
#include <iostream>

TEST_CASE("Teste do Cliente - Inicializacao e Casos Base") {

    Cliente cliente(
        "Djulia Kelikey",
        "djulia@email.com",
        "Senha@123",
        "11144477735",
        "Belo Horizonte");

    CHECK(cliente.getCpf() == "11144477735");
    CHECK(cliente.getEndereco().empty());
    CHECK(cliente.getCartoesSalvos().empty());
}

TEST_CASE("Teste de Validacao de CPF - Casos Validos e Invalidos") {

    SUBCASE("CPF Valido com formatacao") {
        CHECK_NOTHROW(Cliente("Thais", "thais@email.com", "abc123", "111.444.777-35", "Gato"));
    }

    SUBCASE("CPF Invalido por tamanho curto (Estoura no construtor)") {
        CHECK_THROWS_AS(
            Cliente("Thais", "thais@email.com", "abc123", "123.456", "Gato"), 
            std::invalid_argument
        );
    }

    SUBCASE("CPF Invalido com digitos iguais (Estoura no construtor)") {
        CHECK_THROWS_AS(
            Cliente("Thais", "thais@email.com", "abc123", "11111111111", "Gato"), 
            std::invalid_argument
        );
    }

    SUBCASE("CPF Invalido por erro nos digitos verificadores (Estoura no construtor)") {
        CHECK_THROWS_AS(
            Cliente("Thais", "thais@email.com", "abc123", "11144477700", "Gato"), 
            std::invalid_argument
        );
    }
}

TEST_CASE("Teste do Gerenciamento de Endereco Unico e Troca") {

    Cliente cliente(
        "Djulia Kelikey", "djulia@email.com",
        "abc123", "11144477735", "BH");

    cliente.adicionarEndereco(
        "Rua das Flores, 123, Belo Horizonte, MG");

    CHECK(cliente.getEndereco() ==
          "Rua das Flores, 123, Belo Horizonte, MG");

    cliente.adicionarEndereco(
        "Av. Paulista, 1000, Sao Paulo, SP");

    CHECK(cliente.getEndereco() ==
          "Av. Paulista, 1000, Sao Paulo, SP");
}

TEST_CASE("Teste de Endereco Invalido") {

    Cliente cliente(
        "Djulia Kelikey", "djulia@email.com",
        "abc123", "11144477735", "BH");

    CHECK_THROWS_AS(
        cliente.adicionarEndereco(""),
        std::invalid_argument);

    CHECK_THROWS_AS(
        cliente.adicionarEndereco("Rua;Invalida"),
        std::invalid_argument);
}

TEST_CASE("Teste de Validacao e Salvamento de Cartao (Algoritmo de Luhn)") {

    Cliente cliente(
        "Djulia Kelikey", "djulia@email.com",
        "abc123", "11144477735", "BH");

    SUBCASE("Tentativa de salvar cartao invalido") {
        bool resultado = cliente.salvarCartao(
            "1234-5678-1234-5678",
            TipoCartao::CREDITO);
        CHECK(resultado == false);
        CHECK(cliente.getCartoesSalvos().empty());
    }

    SUBCASE("Salvar cartao valido") {
        bool resultado = cliente.salvarCartao(
            "4532015112830366",
            TipoCartao::CREDITO);
        CHECK(resultado == true);
        REQUIRE(cliente.getCartoesSalvos().size() == 1);
        CHECK(cliente.getCartoesSalvos()[0].numero ==
              "4532015112830366");
        CHECK(cliente.getCartoesSalvos()[0].tipo ==
              TipoCartao::CREDITO);
    }

    SUBCASE("Evitar salvar cartao duplicado") {
        cliente.salvarCartao(
            "4532015112830366", TipoCartao::CREDITO);
        bool resultado = cliente.salvarCartao(
            "4532015112830366", TipoCartao::DEBITO);
        CHECK(resultado == false);
        CHECK(cliente.getCartoesSalvos().size() == 1);
    }

    SUBCASE("Numero de cartao vazio lanca excecao") {
        CHECK_THROWS_AS(
            cliente.salvarCartao("", TipoCartao::CREDITO),
            std::invalid_argument);
    }
}

TEST_CASE("Teste do Fluxo de Cadastro Completo") {

    std::remove("usuarios_teste.txt");

    Cliente cliente(
        "Djulia Kelikey",
        "djulia@email.com",
        "Senha123",
        "11144477735",
        "BH");

    CHECK(cliente.cadastrarCliente("usuarios_teste.txt") == true);

    CHECK(cliente.cadastrarCliente("usuarios_teste.txt") == false);

    std::remove("usuarios_teste.txt");
}

TEST_CASE("Teste de Cadastro com CPF Invalido (Agora bloqueado no construtor)") {

    CHECK_THROWS_AS(
        Cliente("Thais", "thais@email.com", "Senha123", "11111111111", "escola"),
        std::invalid_argument);
}

TEST_CASE("Cliente - Alterar Endereco direto no arquivo TXT") {
    std::string arquivoTeste = "usuarios_teste_endereco.txt";
    std::remove(arquivoTeste.c_str());

    Cliente cliente("Djulia", "djulia@ufmg.br", "senha123", "11144477735", "escola");
    
    // Cadastra o cliente para gerar o arquivo fisico
    CHECK(cliente.cadastrarCliente(arquivoTeste) == true);

    SUBCASE("Alteracao de endereco bem-sucedida") {
        CHECK_NOTHROW(cliente.alterarEndereco("Rua da Engenharia, 404", arquivoTeste));
        CHECK(cliente.getEndereco() == "Rua da Engenharia, 404");
    }

    SUBCASE("Disparo de excecao para endereco invalido") {
        CHECK_THROWS_AS(cliente.alterarEndereco("Rua;Hacker", arquivoTeste), std::invalid_argument);
    }

    std::remove(arquivoTeste.c_str());
}

TEST_CASE("Cliente - Polimorfismo (exibirPerfil)") {
    Cliente cliente("Kayke", "kayke@ufmg.br", "senha123", "93541134780", "escola");
    cliente.adicionarEndereco("Campus Pampulha");

    std::ostringstream bufferSaida;
    std::streambuf* coutAntigo = std::cout.rdbuf(bufferSaida.rdbuf());

    cliente.exibirPerfil();

    std::cout.rdbuf(coutAntigo);

    std::string impressao = bufferSaida.str();

    CHECK(impressao.find("Kayke") != std::string::npos);
    CHECK(impressao.find("93541134780") != std::string::npos);
    CHECK(impressao.find("Campus Pampulha") != std::string::npos);
}