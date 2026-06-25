#include "doctest.h"
#include "Usuario.hpp"

#include <fstream>
#include <cstdio>
#include <stdexcept>

static void criarArquivo(const std::string& nome,
                         const std::string& conteudo = "") {
    std::ofstream f(nome);
    f << conteudo;
}

static void removerArquivo(const std::string& nome) {
    std::remove(nome.c_str());
}

TEST_CASE("Usuario - construtor e getters") {
    Usuario u("fulana", "fulana@email.com", "senha123",
              "cliente", "escola");

    CHECK(u.getNome() == "fulana");
    CHECK(u.getEmail() == "fulana@email.com");
    CHECK(u.getSenha() == "senha123");
    CHECK(u.getTipo() == "cliente");
    CHECK(u.getRespostaSeguranca() == "escola");
}

TEST_CASE("Usuario - construtor com dados invalidos") {
    CHECK_THROWS_AS(Usuario("", "fulana@email.com", "senha123",
                            "cliente", "escola"), std::invalid_argument);

    CHECK_THROWS_AS(Usuario("fulana", "emailerrado", "senha123",
                            "cliente", "escola"), std::invalid_argument);

    CHECK_THROWS_AS(Usuario("fulana", "fulana@email.com", "123",
                            "cliente", "escola"), std::invalid_argument);

    CHECK_THROWS_AS(Usuario("fulana", "fulana@email.com", "senha123",
                            "tipoerrado", "escola"), std::invalid_argument);

    CHECK_THROWS_AS(Usuario("fulana", "fulana@email.com", "senha123",
                            "cliente", ""), std::invalid_argument);
}

TEST_CASE("Usuario - validarEmail valido") {
    Usuario u("fulana", "fulana@email.com", "senha123",
              "cliente", "escola");

    CHECK(u.validarEmail("fulana@email.com") == true);
    CHECK(u.validarEmail("teste@dominio.net") == true);
    CHECK(u.validarEmail("x@y.com") == true);
}

TEST_CASE("Usuario - validarEmail invalido") {
    Usuario u("fulana", "fulana@email.com", "senha123",
              "cliente", "escola");

    CHECK(u.validarEmail("") == false);
    CHECK(u.validarEmail("semArroba.com") == false);
    CHECK(u.validarEmail("@email.com") == false);
    CHECK(u.validarEmail("fulana@semponto") == false);
    CHECK(u.validarEmail("fulana@email.c") == false);
    CHECK(u.validarEmail("fulana email@email.com") == false);
    CHECK(u.validarEmail("fulana@@email.com") == false);
    CHECK(u.validarEmail("fulana@email;.com") == false);
}

TEST_CASE("Usuario - gerenciarSenha") {
    Usuario u("fulana", "fulana@email.com", "senha123",
              "cliente", "escola");

    CHECK(u.gerenciarSenha("abc123") == true);
    CHECK(u.gerenciarSenha("abcdefg") == true);
    CHECK(u.gerenciarSenha("12345") == false);
    CHECK(u.gerenciarSenha("") == false);
    CHECK(u.gerenciarSenha("abc;123") == false);
}

TEST_CASE("Usuario - armazenarNome") {
    Usuario u("fulana", "fulana@email.com", "senha123",
              "cliente", "escola");

    u.armazenarNome("Joyjoy");
    CHECK(u.getNome() == "Joyjoy");

    CHECK_THROWS_AS(u.armazenarNome(""), std::invalid_argument);
    CHECK_THROWS_AS(u.armazenarNome("Nome;Errado"), std::invalid_argument);
}

TEST_CASE("Usuario - alterarNome persiste no arquivo") {
    const std::string arquivo = "tuj_alterar_nome.txt";
    criarArquivo(arquivo,
        "cliente;fulana;fulana@email.com;senha123;12345678909;escola;\n");

    Usuario u("fulana", "fulana@email.com", "senha123",
              "cliente", "escola");

    u.alterarNome("Maria", arquivo);

    CHECK(u.getNome() == "Maria");
    CHECK(Usuario::fazerLogin("fulana@email.com", "senha123", arquivo) == "cliente");

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - alterarEmail persiste no arquivo") {
    const std::string arquivo = "tuj_alterar_email.txt";
    criarArquivo(arquivo,
        "cliente;fulana;fulana@email.com;senha123;12345678909;escola;\n");

    Usuario u("fulana", "fulana@email.com", "senha123",
              "cliente", "escola");

    u.alterarEmail("novo@email.com", arquivo);

    CHECK(u.getEmail() == "novo@email.com");
    CHECK(Usuario::fazerLogin("novo@email.com", "senha123", arquivo) == "cliente");
    CHECK(Usuario::fazerLogin("fulana@email.com", "senha123", arquivo) == "invalido");

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - alterarEmail duplicado") {
    const std::string arquivo = "tuj_alterar_email_dup.txt";
    criarArquivo(arquivo,
        "cliente;fulana;fulana@email.com;senha123;12345678909;escola;\n"
        "cliente;outra;outra@email.com;senha456;98765432100;colegio;\n");

    Usuario u("fulana", "fulana@email.com", "senha123",
              "cliente", "escola");

    CHECK_THROWS_AS(u.alterarEmail("outra@email.com", arquivo),
                    std::runtime_error);

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - alterarSenha persiste no arquivo") {
    const std::string arquivo = "tuj_alterar_senha.txt";
    criarArquivo(arquivo,
        "cliente;fulana;fulana@email.com;senha123;12345678909;escola;\n");

    Usuario u("fulana", "fulana@email.com", "senha123",
              "cliente", "escola");

    u.alterarSenha("novaSenha1", arquivo);

    CHECK(u.getSenha() == "novaSenha1");
    CHECK(Usuario::fazerLogin("fulana@email.com", "novaSenha1", arquivo) == "cliente");
    CHECK(Usuario::fazerLogin("fulana@email.com", "senha123", arquivo) == "invalido");

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - alterar dados arquivo inexistente") {
    Usuario u("fulana", "fulana@email.com", "senha123",
              "cliente", "escola");

    CHECK_THROWS_AS(u.alterarNome("Maria", "naoexiste_usuario.txt"),
                    std::runtime_error);

    CHECK_THROWS_AS(u.alterarEmail("novo@email.com", "naoexiste_usuario.txt"),
                    std::runtime_error);

    CHECK_THROWS_AS(u.alterarSenha("novaSenha1", "naoexiste_usuario.txt"),
                    std::runtime_error);
}

TEST_CASE("Usuario - permitirAlteracaoDados") {
    Usuario u("fulana", "fulana@email.com", "senha123",
              "cliente", "escola");

    CHECK(u.permitirAlteracaoDados() == true);
}

TEST_CASE("Usuario - autenticar correto") {
    Usuario u("fulana", "fulana@email.com", "senha123",
              "cliente", "escola");

    CHECK(u.autenticar("fulana@email.com", "senha123") == true);
}

TEST_CASE("Usuario - autenticar incorreto") {
    Usuario u("fulana", "fulana@email.com", "senha123",
              "cliente", "escola");

    CHECK(u.autenticar("outro@email.com", "senha123") == false);
    CHECK(u.autenticar("fulana@email.com", "errada") == false);
    CHECK(u.autenticar("", "") == false);
}

TEST_CASE("Usuario - getPerguntaSeguranca") {
    std::string pergunta = Usuario::getPerguntaSeguranca();
    CHECK(!pergunta.empty());
}

TEST_CASE("Usuario - emailJaCadastrado encontrado") {
    const std::string arquivo = "tuj_email.txt";
    criarArquivo(arquivo,
        "cliente;fulana;fulana@email.com;senha123;12345678909;escola;\n");

    CHECK(Usuario::emailJaCadastrado("fulana@email.com", arquivo) == true);

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - emailJaCadastrado nao encontrado") {
    const std::string arquivo = "tuj_email2.txt";
    criarArquivo(arquivo,
        "cliente;fulana;fulana@email.com;senha123;12345678909;escola;\n");

    CHECK(Usuario::emailJaCadastrado("outro@email.com", arquivo) == false);

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - emailJaCadastrado arquivo inexistente") {
    CHECK(Usuario::emailJaCadastrado(
        "fulana@email.com", "naoexiste_uj.txt") == false);
}

TEST_CASE("Usuario - emailJaCadastrado arquivo invalido") {
    const std::string arquivo = "tuj_email_invalido.txt";
    criarArquivo(arquivo, "linha_invalida\n");

    CHECK_THROWS_AS(Usuario::emailJaCadastrado("fulana@email.com", arquivo),
                    std::runtime_error);

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - fazerLogin correto") {
    const std::string arquivo = "tuj_login.txt";
    criarArquivo(arquivo,
        "cliente;fulana;fulana@email.com;senha123;12345678909;escola;\n"
        "administrador;julia;julia@email.com;admin123;00000000000;escola;\n");

    CHECK(Usuario::fazerLogin(
        "fulana@email.com", "senha123", arquivo) == "cliente");

    CHECK(Usuario::fazerLogin(
        "julia@email.com", "admin123", arquivo) == "administrador");

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - fazerLogin incorreto") {
    const std::string arquivo = "tuj_login2.txt";
    criarArquivo(arquivo,
        "cliente;fulana;fulana@email.com;senha123;12345678909;escola;\n");

    CHECK(Usuario::fazerLogin(
        "fulana@email.com", "errada", arquivo) == "invalido");

    CHECK(Usuario::fazerLogin(
        "nao@existe.com", "senha123", arquivo) == "invalido");

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - fazerLogin arquivo inexistente") {
    CHECK_THROWS_AS(Usuario::fazerLogin(
        "fulana@email.com", "senha123", "naoexiste_login.txt"),
        std::runtime_error);
}

TEST_CASE("Usuario - salvarUsuario sucesso") {
    const std::string arquivo = "tuj_salvar.txt";
    removerArquivo(arquivo);

    CHECK(Usuario::salvarUsuario(
        "cliente", "fulana", "fulana@email.com",
        "senha123", "12345678909", "escola", "", arquivo) == true);

    CHECK(Usuario::fazerLogin(
        "fulana@email.com", "senha123", arquivo) == "cliente");

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - salvarUsuario email duplicado") {
    const std::string arquivo = "tuj_salvar2.txt";
    removerArquivo(arquivo);

    Usuario::salvarUsuario(
        "cliente", "fulana", "fulana@email.com",
        "senha123", "12345678909", "escola", "", arquivo);

    CHECK(Usuario::salvarUsuario(
        "cliente", "Outra", "fulana@email.com",
        "outrasenha", "98765432100", "outra", "", arquivo) == false);

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - salvarUsuario dois usuarios distintos") {
    const std::string arquivo = "tuj_salvar3.txt";
    removerArquivo(arquivo);

    CHECK(Usuario::salvarUsuario(
        "cliente", "fulana", "fulana@email.com",
        "senha123", "12345678909", "escola", "", arquivo) == true);

    CHECK(Usuario::salvarUsuario(
        "administrador", "julia", "julia@email.com",
        "admin123", "00000000000", "escola", "", arquivo) == true);

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - salvarUsuario dados invalidos") {
    const std::string arquivo = "tuj_salvar_invalido.txt";
    removerArquivo(arquivo);

    CHECK_THROWS_AS(Usuario::salvarUsuario(
        "cliente", "", "fulana@email.com",
        "senha123", "12345678909", "escola", "", arquivo),
        std::invalid_argument);

    CHECK_THROWS_AS(Usuario::salvarUsuario(
        "cliente", "fulana", "emailerrado",
        "senha123", "12345678909", "escola", "", arquivo),
        std::invalid_argument);

    CHECK_THROWS_AS(Usuario::salvarUsuario(
        "cliente", "fulana", "fulana@email.com",
        "123", "12345678909", "escola", "", arquivo),
        std::invalid_argument);

    CHECK_THROWS_AS(Usuario::salvarUsuario(
        "admin", "julia", "julia@email.com",
        "admin123", "00000000000", "escola", "", arquivo),
        std::invalid_argument);

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - recuperarSenha senha curta") {
    const std::string arquivo = "tuj_rec.txt";
    criarArquivo(arquivo,
        "cliente;fulana;fulana@email.com;senha123;12345678909;escola;\n");

    CHECK_THROWS_AS(Usuario::recuperarSenha(
        "fulana@email.com", "escola", "123", arquivo),
        std::invalid_argument);

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - recuperarSenha resposta errada") {
    const std::string arquivo = "tuj_rec2.txt";
    criarArquivo(arquivo,
        "cliente;fulana;fulana@email.com;senha123;12345678909;escola;\n");

    CHECK(Usuario::recuperarSenha(
        "fulana@email.com", "errada", "novaSenha1", arquivo) == false);

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - recuperarSenha email nao encontrado") {
    const std::string arquivo = "tuj_rec3.txt";
    criarArquivo(arquivo,
        "cliente;fulana;fulana@email.com;senha123;12345678909;escola;\n");

    CHECK(Usuario::recuperarSenha(
        "outro@email.com", "escola", "novaSenha1", arquivo) == false);

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - recuperarSenha sucesso") {
    const std::string arquivo = "tuj_rec4.txt";
    criarArquivo(arquivo,
        "cliente;fulana;fulana@email.com;senha123;12345678909;escola;\n");

    CHECK(Usuario::recuperarSenha(
        "fulana@email.com", "escola", "novaSenha1", arquivo) == true);

    CHECK(Usuario::fazerLogin(
        "fulana@email.com", "novaSenha1", arquivo) == "cliente");

    removerArquivo(arquivo);
}

TEST_CASE("Usuario - recuperarSenha arquivo inexistente") {
    CHECK_THROWS_AS(Usuario::recuperarSenha(
        "fulana@email.com", "escola",
        "novaSenha1", "naoexiste_uj.txt"),
        std::runtime_error);
}