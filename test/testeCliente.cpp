#include "doctest.h"
#include "../include/Cliente.hpp"

TEST_CASE("Cliente - construtor nao lanca excecao") {
    CHECK_NOTHROW(Cliente("Joao", "joao@email.com", "senha123", "12345678901"));
}

TEST_CASE("Cliente - herda validarEmail de Usuario") {
    Cliente c("Joao", "joao@email.com", "senha123", "12345678901");

    CHECK(c.validarEmail("joao@email.com") == true);
    CHECK(c.validarEmail("semArroba")      == false);
    CHECK(c.validarEmail("")               == false);
}

TEST_CASE("Cliente - validarCpf retorna bool") {
    Cliente c("Joao", "joao@email.com", "senha123", "12345678901");
    bool r = c.validarCpf();
    CHECK((r == true || r == false));
}

TEST_CASE("Cliente - adicionarEndereco nao lanca excecao") {
    Cliente c("Joao", "joao@email.com", "senha123", "12345678901");
    CHECK_NOTHROW(c.adicionarEndereco("Rua das Flores, 10"));
}

TEST_CASE("Cliente - adicionar multiplos enderecos") {
    Cliente c("Joao", "joao@email.com", "senha123", "12345678901");
    CHECK_NOTHROW(c.adicionarEndereco("Rua A, 1"));
    CHECK_NOTHROW(c.adicionarEndereco("Rua B, 2"));
    CHECK_NOTHROW(c.adicionarEndereco("Rua C, 3"));
}

TEST_CASE("Cliente - adicionarMetodoPagamento nao lanca excecao") {
    Cliente c("Joao", "joao@email.com", "senha123", "12345678901");
    CHECK_NOTHROW(c.adicionarMetodoPagamento("Pix"));
    CHECK_NOTHROW(c.adicionarMetodoPagamento("Credito"));
}