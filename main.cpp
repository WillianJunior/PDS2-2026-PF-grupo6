#include "UI.hpp"
#include "Usuario.hpp"
#include "Cliente.hpp"
#include "Catalogo.hpp"
#include "Estoque.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

const std::string ARQUIVO_USUARIOS = "usuarios.txt";

/**
 * @brief Lê os dados completos de um usuário a partir do email.
 * Necessário para reconstruir o objeto Cliente após o login.
 */
static bool carregarDadosUsuario(
        const std::string& email,
        std::string& nome,
        std::string& senha,
        std::string& cpf,
        std::string& resposta) {

    std::ifstream arquivo(ARQUIVO_USUARIOS);

    if (!arquivo.is_open()) {
        return false;
    }

    std::string linha;

    while (std::getline(arquivo, linha)) {

        std::stringstream ss(linha);

        std::string tipo;
        std::string n;
        std::string e;
        std::string s;
        std::string c;
        std::string r;

        std::getline(ss, tipo, ';');
        std::getline(ss, n,    ';');
        std::getline(ss, e,    ';');
        std::getline(ss, s,    ';');
        std::getline(ss, c,    ';');
        std::getline(ss, r,    ';');

        if (e == email) {
            nome     = n;
            senha    = s;
            cpf      = c;
            resposta = r;
            return true;
        }
    }

    return false;
}

int main() {

    UI ui;
    Catalogo catalogo;
    Estoque estoque;

    int opcao;

    do {
        ui.exibirMenuPrincipal();

        opcao = ui.lerOpcao("Opcao: ");

        if (opcao == 1) {

            std::string email = ui.lerTexto("Email: ");
            std::string senha = ui.lerTexto("Senha: ");

            std::string tipo = Usuario::fazerLogin(
                email, senha, ARQUIVO_USUARIOS);

            if (tipo == "invalido") {
                ui.exibirErro(
                    "Email ou senha incorretos.");
                continue;
            }

            if (tipo == "admin") {

                ui.exibirSucesso(
                    "Login como Administrador!");

                ui.exibirMenuAdministrador(
                    catalogo, estoque);

            } else {

                std::string nome;
                std::string senhaArq;
                std::string cpf;
                std::string resposta;

                if (!carregarDadosUsuario(
                        email, nome,
                        senhaArq, cpf, resposta)) {

                    ui.exibirErro(
                        "Erro ao carregar dados do usuario.");
                    continue;
                }

                ui.exibirSucesso("Login como Cliente!");

                Cliente cliente(
                    nome, email, senha, cpf, resposta);

                Carrinho carrinho(cliente);

                ui.exibirMenuCliente(
                    carrinho, catalogo, cliente);
            }

        } else if (opcao == 2) {

            ui.telaCadastroCliente(ARQUIVO_USUARIOS);

        } else if (opcao == 3) {

            ui.telaRecuperacaoSenha(ARQUIVO_USUARIOS);
        }

    } while (opcao != 0);

    std::cout << "Ate logo!\n";

    return 0;
}