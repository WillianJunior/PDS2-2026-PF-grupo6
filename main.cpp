#include "UI.hpp"
#include "Usuario.hpp"
#include "Cliente.hpp"
#include "Catalogo.hpp"
#include "Estoque.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

const std::string ARQUIVO_USUARIOS = "usuarios.txt";

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

        if (linha.empty()) continue;

        std::stringstream ss(linha);

        std::string tipo, n, e, s, c, r;

        if (!std::getline(ss, tipo, ';') ||
            !std::getline(ss, n,    ';') ||
            !std::getline(ss, e,    ';') ||
            !std::getline(ss, s,    ';') ||
            !std::getline(ss, c,    ';') ||
            !std::getline(ss, r,    ';')) {

            continue;
        }

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
    Estoque  estoque;

    int opcao;

    do {
        ui.exibirMenuPrincipal();

        opcao = ui.lerOpcao("Opcao: ");

        if (opcao == 1) {

            std::string email = ui.lerTexto("Email: ");
            std::string senha = ui.lerTexto("Senha: ");

            try {
                std::string tipo = Usuario::fazerLogin(
                    email, senha, ARQUIVO_USUARIOS);

                if (tipo == "invalido") {
                    ui.exibirErro(
                        "Email ou senha incorretos.");
                    continue;
                }

                std::string nome, senhaArq, cpf, resposta;

                if (!carregarDadosUsuario(
                        email, nome, senhaArq, cpf, resposta)) {

                    ui.exibirErro(
                        "Erro ao carregar dados do usuario.");
                    continue;
                }

                if (tipo == "administrador") {

                    ui.exibirSucesso(
                        "Login como Administrador!");

                    ui.exibirMenuAdministrador(
                        catalogo, estoque);

                } else {

                    ui.exibirSucesso("Login como Cliente!");

                    Cliente cliente(
                        nome, email, senha, cpf, resposta);

                    Carrinho carrinho(cliente);

                    ui.exibirMenuCliente(
                        carrinho, catalogo, cliente);
                }

            } catch (const std::exception& e) {
                ui.exibirErro(e.what());
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