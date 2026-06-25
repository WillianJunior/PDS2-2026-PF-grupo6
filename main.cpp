#include "Interface.hpp"
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
    if (!arquivo.is_open()) return false;

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue;

        std::stringstream ss(linha);
        std::string tipo, n, e, s, c, r;

        if (!std::getline(ss, tipo, ';') || !std::getline(ss, n, ';') ||
            !std::getline(ss, e, ';') || !std::getline(ss, s, ';') ||
            !std::getline(ss, c, ';') || !std::getline(ss, r, ';')) {
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
    Interface interface_app;
    Catalogo catalogo; 
    Estoque  estoque;

    int opcao;

    do {
        interface_app.exibirMenuPrincipal();
        opcao = interface_app.lerOpcao("Opcao: ");

        if (opcao == 1) {
            std::string email = interface_app.lerTexto("Email: ");
            std::string senha = interface_app.lerTexto("Senha: ");

            try {
                std::string tipo = Usuario::fazerLogin(email, senha, ARQUIVO_USUARIOS);

                if (tipo == "invalido") {
                    interface_app.exibirErro("Email ou senha incorretos.");
                    continue;
                }

                std::string nome, senhaArq, cpf, resposta;

                if (!carregarDadosUsuario(email, nome, senhaArq, cpf, resposta)) {
                    interface_app.exibirErro("Erro ao carregar dados do usuario.");
                    continue;
                }

                if (tipo == "administrador") {
                    interface_app.exibirSucesso("Login como Administrador!");
                    interface_app.exibirMenuAdministrador(catalogo, estoque);
                } else {
                    interface_app.exibirSucesso("Login como Cliente!");
                    Cliente cliente(nome, email, senha, cpf, resposta);
                    Carrinho carrinho(cliente);
                    interface_app.exibirMenuCliente(carrinho, catalogo, cliente);
                }

            } catch (const std::exception& e) {
                interface_app.exibirErro(e.what());
            }

        } else if (opcao == 2) {
            interface_app.telaCadastroCliente(ARQUIVO_USUARIOS);
        } else if (opcao == 3) {
            interface_app.telaRecuperacaoSenha(ARQUIVO_USUARIOS);
        }

    } while (opcao != 0);

    std::cout << "Ate logo! Volte sempre :)\n";
    return 0;
}