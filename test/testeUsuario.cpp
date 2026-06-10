#include "doctest.h"
#include "Usuario.hpp"

#include <fstream>
#include <cstdio>

// ──────────── Auxiliares ────────────

static void criarArquivo(const std::string& nome,
                         const std::string& conteudo = "") {
    std::ofstream f(nome);
    f << conteudo;
}

static void removerArquivo(const std::string& nome) {
    std::remove(nome.c_str());
}

// ──────────── Construtor e Getters ────────────

TEST_CASE("Usuario - construtor e getters") {
    Usuario u("Thaisinha", "thaisinha@email.com", "senha123",
              "cliente", "escola");

    CHECK(u.getNome() == "Thaisinha");
    CHECK(u.getEmail() == "thaisinha@email.com");
    CHECK(u.getSenha() == "senha123");
    CHECK(u.getTipo() == "cliente");
    CHECK(u.getRespostaSeguranca() == "escola");
}

// ──────────── validarEmail ────────────

TEST_CASE("Usuario - validarEmail valido") {
    Usuario u("Thaisinha", "thaisinha@email.com", "senha123",
              "cliente", "escola");

    CHECK(u.validarEmail("thaisinha@email.com") == true);
    CHECK(u.validarEmail("teste@dominio.net") == true);
    CHECK(u.validarEmail("x@y.com") == true);
}

TEST_CASE("Usuario - validarEmail invalido") {
    Usuario u("Thaisinha", "thaisinha@email.com", "senha123",
              "cliente", "escola");

    CHECK(u.validarEmail("") == false);
    CHECK(u.validarEmail("semArroba.com") == false);
    CHECK(u.validarEmail("@email.com") == false);
    CHECK(u.validarEmail("thaisinha@semponto") == false);
    CHECK(u.validarEmail("thaisinha@email.c") == false);
}

// ──────────── gerenciarSenha ────────────

TEST_CASE("Usuario - gerenciarSenha") {
    Usuario u("Thaisinha", "thaisinha@email.com", "senha123",
              "cliente", "escola");

    CHECK(u.gerenciarSenha("abc123") == true);
    CHECK(u.gerenciarSenha("abcdefg") == true);
    CHECK(u.gerenciarSenha("12345") == false);
    CHECK(u.gerenciarSenha("") == false);
}

// ──────────── armazenarNome ────────────

TEST_CASE("Usuario - armazenarNome") {
    Usuario u("Thaisinha", "thaisinha@email.com", "senha123",
              "cliente", "escola");
    u.armazenarNome("Joyjoy");
    CHECK(u.getNome() == "Joyjoy");
}

// ──────────── atualizarDadosPerfil e permitirAlteracaoDados ────────────

TEST_CASE("Usuario - atualizarDadosPerfil") {
    Usuario u("Thaisinha", "thaisinha@email.com", "senha123",
              "cliente", "escola");
    CHECK_NOTHROW(u.atualizarDadosPerfil());
}

TEST_CASE("Usuario - permitirAlteracaoDados") {
    Usuario u("Thaisinha", "thaisinha@email.com", "senha123",
              "cliente", "escola");
    CHECK(u.permitirAlteracaoDados() == true);
}

// ──────────── autenticar ────────────

TEST_CASE("Usuario - autenticar correto") {
    Usuario u("Thaisinha", "thaisinha@email.com", "senha123",
              "cliente", "escola");
    CHECK(u.autenticar("thaisinha@email.com", "senha123") == true);
}

TEST_CASE("Usuario - autenticar incorreto") {
    Usuario u("Thaisinha", "thaisinha@email.com", "senha123",
              "cliente", "escola");
    CHECK(u.autenticar("outro@email.com", "senha123") == false);
    CHECK(u.autenticar("thaisinha@email.com", "errada") == false);
    CHECK(u.autenticar("", "") == false);
}

// ──────────── getPerguntaSeguranca ────────────

TEST_CASE("Usuario - getPerguntaSeguranca") {
    std::string pergunta = Usuario::getPerguntaSeguranca();
    CHECK(!pergunta.empty());
}

// ──────────── emailJaCadastrado ────────────

TEST_CASE("Usuario - emailJaCadastrado encontrado") {
    const std::string arquivo = "tuj_email.txt";
    criarArquivo(arquivo,
        "cliente;Thaisinha;thaisinha@email.com;senha123;12345678909;escola\n");

    CHECK(Usuario::emailJaCadastrado("thaisinha@email.com", arquivo) == true);

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - emailJaCadastrado nao encontrado") {
    const std::string arquivo = "tuj_email2.txt";
    criarArquivo(arquivo,
        "cliente;Thaisinha;thaisinha@email.com;senha123;12345678909;escola\n");

    CHECK(Usuario::emailJaCadastrado("outro@email.com", arquivo) == false);

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - emailJaCadastrado arquivo inexistente") {
    CHECK(Usuario::emailJaCadastrado(
        "thaisinha@email.com", "naoexiste_uj.txt") == false);
}

// ──────────── fazerLogin ────────────

TEST_CASE("Usuario - fazerLogin correto") {
    const std::string arquivo = "tuj_login.txt";
    criarArquivo(arquivo,
        "cliente;Thaisinha;thaisinha@email.com;senha123;12345678909;escola\n"
        "admin;Djuju;djulia@email.com;admin123;;escola\n");

    CHECK(Usuario::fazerLogin(
        "thaisinha@email.com", "senha123", arquivo) == "cliente");
    CHECK(Usuario::fazerLogin(
        "djulia@email.com", "admin123", arquivo) == "admin");

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - fazerLogin incorreto") {
    const std::string arquivo = "tuj_login2.txt";
    criarArquivo(arquivo,
        "cliente;Thaisinha;thaisinha@email.com;senha123;12345678909;escola\n");

    CHECK(Usuario::fazerLogin(
        "thaisinha@email.com", "errada", arquivo) == "invalido");
    CHECK(Usuario::fazerLogin(
        "nao@existe.com", "senha123", arquivo) == "invalido");

    removerArquivo(arquivo);
}

// ──────────── salvarUsuario ────────────

TEST_CASE("Usuario - salvarUsuario sucesso") {
    const std::string arquivo = "tuj_salvar.txt";
    removerArquivo(arquivo);

    CHECK(Usuario::salvarUsuario(
        "cliente", "Thaisinha", "thaisinha@email.com",
        "senha123", "12345678909", "escola", arquivo) == true);

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - salvarUsuario email duplicado") {
    const std::string arquivo = "tuj_salvar2.txt";
    removerArquivo(arquivo);

    Usuario::salvarUsuario(
        "cliente", "Thaisinha", "thaisinha@email.com",
        "senha123", "12345678909", "escola", arquivo);

    CHECK(Usuario::salvarUsuario(
        "cliente", "Outra", "thaisinha@email.com",
        "outrasenha", "98765432100", "outra", arquivo) == false);

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - salvarUsuario dois usuarios distintos") {
    const std::string arquivo = "tuj_salvar3.txt";
    removerArquivo(arquivo);

    CHECK(Usuario::salvarUsuario(
        "cliente", "Thaisinha", "thaisinha@email.com",
        "senha123", "12345678909", "escola", arquivo) == true);
    CHECK(Usuario::salvarUsuario(
        "admin", "Djuju", "djulia@email.com",
        "admin123", "", "escola", arquivo) == true);

    removerArquivo(arquivo);
}

// ──────────── recuperarSenha ────────────

TEST_CASE("Usuario - recuperarSenha senha curta") {
    const std::string arquivo = "tuj_rec.txt";
    criarArquivo(arquivo,
        "cliente;Thaisinha;thaisinha@email.com;senha123;12345678909;escola\n");

    CHECK(Usuario::recuperarSenha(
        "thaisinha@email.com", "escola", "123", arquivo) == false);

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - recuperarSenha resposta errada") {
    const std::string arquivo = "tuj_rec2.txt";
    criarArquivo(arquivo,
        "cliente;Thaisinha;thaisinha@email.com;senha123;12345678909;escola\n");

    CHECK(Usuario::recuperarSenha(
        "thaisinha@email.com", "errada", "novaSenha1", arquivo) == false);

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - recuperarSenha email nao encontrado") {
    const std::string arquivo = "tuj_rec3.txt";
    criarArquivo(arquivo,
        "cliente;Thaisinha;thaisinha@email.com;senha123;12345678909;escola\n");

    CHECK(Usuario::recuperarSenha(
        "outro@email.com", "escola", "novaSenha1", arquivo) == false);

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - recuperarSenha sucesso") {
    const std::string arquivo = "tuj_rec4.txt";
    criarArquivo(arquivo,
        "cliente;Thaisinha;thaisinha@email.com;senha123;12345678909;escola\n");

    CHECK(Usuario::recuperarSenha(
        "thaisinha@email.com", "escola", "novaSenha1", arquivo) == true);

    CHECK(Usuario::fazerLogin(
        "thaisinha@email.com", "novaSenha1", arquivo) == "cliente");

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - recuperarSenha arquivo inexistente") {
    CHECK(Usuario::recuperarSenha(
        "thaisinha@email.com", "escola",
        "novaSenha1", "naoexiste_uj.txt") == false);
}