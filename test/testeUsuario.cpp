#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Usuario.hpp"

TEST_CASE("Teste: Construtor e Getters do Usuario") {
    Usuario user("Fulano Ciclano", "fulano@provedor.com", "SenhaValida123");
    
    CHECK(user.getNome() == "Fulano Ciclano");
    CHECK(user.getEmail() == "fulano@provedor.com");
    CHECK(user.getSenha() == "SenhaValida123");
}

TEST_CASE("Teste: Alteração de Nome") {
    Usuario user("Fulano Ciclano", "fulano@provedor.com", "SenhaValida123");
    user.armazenarNome("Ciclano Alterado");
    CHECK(user.getNome() == "Ciclano Alterado");
}

TEST_CASE("Teste: Validação de E-mail") {
    Usuario user("Fulano", "valido@email.com", "12345678");
    
    CHECK(user.validarEmail("suporte@loja.com") == true);
    CHECK(user.validarEmail("emailSemArroba.com") == false);
}

TEST_CASE("Teste: Política de Senha") {
    Usuario user("Fulano", "valido@email.com", "12345678");
    
    CHECK(user.gerenciarSenha("12345678") == true);
    CHECK(user.gerenciarSenha("123") == false);
}

TEST_CASE("Teste: Métodos de Cobertura") {
    Usuario user("Fulano", "valido@email.com", "12345678");
    user.atualizarDadosPerfil();
    user.gerenciarRecuperacaoAcesso();
    CHECK(user.permitirAlteracaoDados() == false);
}