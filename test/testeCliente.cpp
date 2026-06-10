#include "doctest.h"                       
#include "Cliente.hpp"   

TEST_CASE("Teste do Cliente - Inicializacao e Casos Base") {
    Cliente cliente("Carlos Silva", "carlos@email.com", "Senha@123", "11144477735", "Belo Horizonte");
    
    CHECK(cliente.getCpf() == "11144477735");
    CHECK(cliente.getEndereco().empty()); 
    CHECK(cliente.getCartoesSalvos().empty());
}

TEST_CASE("Teste de Validacao de CPF - Casos Validos e Invalidos") {
    SUBCASE("CPF Valido com formatacao") {
        Cliente cliente("Ana", "ana@email.com", "123", "111.444.777-35", "Gato");
        CHECK(cliente.validarCpf() == true);
    }

    SUBCASE("CPF Invalido por tamanho curto") {
        Cliente cliente("Ana", "ana@email.com", "123", "123.456", "Gato");
        CHECK(cliente.validarCpf() == false);
    }

    SUBCASE("CPF Invalido com digitos iguais") {
        Cliente cliente("Ana", "ana@email.com", "123", "11111111111", "Gato");
        CHECK(cliente.validarCpf() == false);
    }

    SUBCASE("CPF Invalido por erro nos digitos verificadores") {
        Cliente cliente("Ana", "ana@email.com", "123", "11144477700", "Gato");
        CHECK(cliente.validarCpf() == false);
    }
}

TEST_CASE("Teste do Gerenciamento de Endereco Unico e Troca") {
    Cliente cliente("Carlos", "carlos@email.com", "123", "11144477735", "BH");
   
    cliente.adicionarEndereco("Rua das Flores, 123, Belo Horizonte, MG");
    CHECK(cliente.getEndereco() == "Rua das Flores, 123, Belo Horizonte, MG");
   
    cliente.adicionarEndereco("Av. Paulista, 1000, Sao Paulo, SP");
    CHECK(cliente.getEndereco() == "Av. Paulista, 1000, Sao Paulo, SP"); 
}

TEST_CASE("Teste de Validacao e Salvamento de Cartao (Algoritmo de Luhn)") {
    Cliente cliente("Carlos", "carlos@email.com", "123", "11144477735", "BH");

    SUBCASE("Tentativa de salvar cartao invalido") {
        cliente.salvarCartao("1234-5678-1234-5678", TipoCartao::CREDITO); 
        CHECK(cliente.getCartoesSalvos().empty());
    }

    SUBCASE("Salvar cartao valido") {
        cliente.salvarCartao("49927398716", TipoCartao::CREDITO); 
        REQUIRE(cliente.getCartoesSalvos().size() == 1);

        CHECK(cliente.getCartoesSalvos()[0].numero == "49927398716");
        CHECK(cliente.getCartoesSalvos()[0].tipo == TipoCartao::CREDITO);
    }
    
    SUBCASE("Evitar salvar cartao duplicado") {
        cliente.salvarCartao("49927398716", TipoCartao::CREDITO);
        cliente.salvarCartao("49927398716", TipoCartao::DEBITO);
        
        CHECK(cliente.getCartoesSalvos().size() == 1);
    }
}

TEST_CASE("Teste do Fluxo de Cadastro Completo") {
    Cliente cliente("Carlos", "carlos@email.com", "123", "11144477735", "BH");
    
    CHECK(cliente.cadastrarCliente("usuarios_teste.txt") == true);
}
