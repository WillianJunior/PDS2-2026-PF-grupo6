#include "doctest.h"
#include "Cliente.hpp"

#include <cstdio>
#include <stdexcept>

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