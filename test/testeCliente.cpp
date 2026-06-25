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
    }

    SUBCASE("Salvar cartao valido") {
        bool resultado = cliente.salvarCartao(
            "4532015112830366",
            TipoCartao::CREDITO,
            "cartoes_teste_luhn.txt");
        CHECK(resultado == true);
        REQUIRE(cliente.getCartoesSalvos().size() == 1);
        CHECK(cliente.getCartoesSalvos()[0].numero == "4532015112830366");
        std::remove("cartoes_teste_luhn.txt");
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

TEST_CASE("Cliente - Alterar Endereco direto no arquivo TXT") {
    std::string arquivoTeste = "usuarios_teste_endereco.txt";
    std::remove(arquivoTeste.c_str());

    Cliente cliente("Djulia", "djulia@ufmg.br", "senha123", "11144477735", "escola");
    
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

TEST_CASE("Cliente - Gerenciamento de Cartoes no Arquivo") {
    std::string arqCartoes = "cartoes_teste_faturamento.txt";
    std::remove(arqCartoes.c_str());

    Cliente cliente("Teste", "teste_isolado@gmail.com", "senha123", "11144477735", "escola");

    SUBCASE("Salvar cartao persiste no arquivo") {
        CHECK(cliente.salvarCartao("4532015112830366", TipoCartao::DEBITO, arqCartoes) == true);
        CHECK(cliente.getCartoesSalvos().size() == 1);
        
        // Impede duplicados
        CHECK(cliente.salvarCartao("4532015112830366", TipoCartao::CREDITO, arqCartoes) == false);
    }

    SUBCASE("Remover cartao atualiza o arquivo") {
        cliente.salvarCartao("4532015112830366", TipoCartao::DEBITO, arqCartoes);
        
        CHECK(cliente.removerCartao("4532015112830366", arqCartoes) == true);
        CHECK(cliente.getCartoesSalvos().empty());
        
        // Tentar remover cartao que nao existe
        CHECK(cliente.removerCartao("4532015112830366", arqCartoes) == false);
    }

    std::remove(arqCartoes.c_str());
}
