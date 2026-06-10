#include "Administrador.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

Administrador::Administrador(
        std::string nome,
        std::string email,
        std::string senha,
        std::string respostaSeguranca)

    : Usuario(nome,
              email,
              senha,
              "admin",
              respostaSeguranca) {
}

void Administrador::gerenciarCatalogo(Catalogo&) {

    int opcao;

    do {

        std::cout << "\n=== GERENCIAR CATALOGO ===\n";
        std::cout << "1 - Adicionar livro\n";
        std::cout << "2 - Remover livro\n";
        std::cout << "3 - Listar livros\n";
        std::cout << "0 - Sair\n";
        std::cout << "Opcao: ";
        std::cin >> opcao;

        if (opcao == 1) {

            int id;
            std::string nome;
            std::string descricao;
            std::string categoria;
            float preco;

            std::cin.ignore();

            std::cout << "ID: ";
            std::cin >> id;
            std::cin.ignore();

            std::cout << "Nome: ";
            std::getline(std::cin, nome);

            std::cout << "Descricao: ";
            std::getline(std::cin, descricao);

            std::cout << "Preco: ";
            std::cin >> preco;
            std::cin.ignore();

            std::cout << "Categoria (Ficcao/Tecnico/Infantil/Romance): ";
            std::getline(std::cin, categoria);

            std::ofstream arquivo(
                "catalogo.txt",
                std::ios::app);

            arquivo << id << ";"
                    << nome << ";"
                    << descricao << ";"
                    << preco << ";"
                    << categoria
                    << "\n";
        }

        else if (opcao == 2) {

            int idRemover;

            std::cout << "ID do livro: ";
            std::cin >> idRemover;

            std::ifstream entrada("catalogo.txt");

            std::vector<std::string> linhas;
            std::string linha;

            while (std::getline(entrada, linha)) {

                std::stringstream ss(linha);

                std::string idTexto;

                std::getline(ss, idTexto, ';');

                if (std::stoi(idTexto) != idRemover) {
                    linhas.push_back(linha);
                }
            }

            entrada.close();

            std::ofstream saida("catalogo.txt");

            for (const auto& l : linhas) {
                saida << l << "\n";
            }
        }

        else if (opcao == 3) {

            std::ifstream arquivo("catalogo.txt");

            std::string linha;

            while (std::getline(arquivo, linha)) {
                std::cout << linha << std::endl;
            }
        }

    } while (opcao != 0);
}

void Administrador::gerenciarEstoque(
        Estoque&) {
}

void Administrador::gerenciarContas(
        Cliente&) {
}

void Administrador::atualizarVendas(
        Pedido&) {
}

bool Administrador::cadastrarAdministrador(
        const std::string& nomeArquivo) const {

    if (!validarEmail(_email)) {
        return false;
    }

    if (!gerenciarSenha(_senha)) {
        return false;
    }

    if (_respostaSeguranca.empty()) {
        return false;
    }

    return Usuario::salvarUsuario(
        "admin",
        _nome,
        _email,
        _senha,
        "",
        _respostaSeguranca,
        nomeArquivo
    );
}