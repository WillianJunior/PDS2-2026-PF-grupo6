#include "Administrador.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

Administrador::Administrador(
        std::string nome,
        std::string email,
        std::string senha,
        std::string respostaSeguranca)

    : Usuario(nome,
              email,
              senha,
              "administrador",
              respostaSeguranca) {
}

void Administrador::gerenciarCatalogo(
        Catalogo&) {

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
            float preco;
            int quantidadeEstoque;

            std::string nome;
            std::string descricao;
            std::string categoria;

            std::cout << "\nID: ";
            std::cin >> id;
            std::cin.ignore();

            std::cout << "Nome: ";
            std::getline(std::cin, nome);

            std::cout << "Descricao: ";
            std::getline(std::cin, descricao);

            std::cout << "Preco: ";
            std::cin >> preco;

            std::cout << "Quantidade em estoque: ";
            std::cin >> quantidadeEstoque;
            std::cin.ignore();

            std::cout << "Categoria (Ficcao/Tecnico/Infantil/Romance/Suspense/Fantasia): ";
            std::getline(std::cin, categoria);

            std::ofstream arquivo(
                "catalogo.txt",
                std::ios::app
            );

            if (!arquivo.is_open()) {
                std::cout << "Erro ao abrir catalogo.txt.\n";
                return;
            }

            arquivo << id << ";"
                    << nome << ";"
                    << descricao << ";"
                    << preco << ";"
                    << quantidadeEstoque << ";"
                    << categoria
                    << "\n";

            std::cout << "Livro cadastrado com sucesso.\n";
        }

        else if (opcao == 2) {
            int idRemover;

            std::cout << "\nID do livro a remover: ";
            std::cin >> idRemover;

            std::ifstream entrada("catalogo.txt");

            if (!entrada.is_open()) {
                std::cout << "Arquivo catalogo.txt nao encontrado.\n";
                return;
            }

            std::vector<std::string> linhas;
            std::string linha;
            bool removido = false;

            while (std::getline(entrada, linha)) {
                if (linha.empty()) {
                    continue;
                }

                std::stringstream ss(linha);
                std::string idTexto;

                std::getline(ss, idTexto, ';');

                if (std::stoi(idTexto) != idRemover) {
                    linhas.push_back(linha);
                } else {
                    removido = true;
                }
            }

            entrada.close();

            std::ofstream saida("catalogo.txt");

            if (!saida.is_open()) {
                std::cout << "Erro ao reescrever catalogo.txt.\n";
                return;
            }

            for (const auto& l : linhas) {
                saida << l << "\n";
            }

            if (removido) {
                std::cout << "Livro removido com sucesso.\n";
            } else {
                std::cout << "Livro nao encontrado.\n";
            }
        }

        else if (opcao == 3) {
            std::ifstream arquivo("catalogo.txt");

            if (!arquivo.is_open()) {
                std::cout << "Arquivo catalogo.txt ainda nao existe.\n";
                continue;
            }

            std::string linha;

            std::cout << "\n=== LIVROS CADASTRADOS ===\n";

            while (std::getline(arquivo, linha)) {
                std::cout << linha << std::endl;
            }
        }

    } while (opcao != 0);
}

void Administrador::gerenciarEstoque(
        Estoque& estoque) {

    std::cout << "\n=== ESTOQUE ===\n";
    std::cout << estoque.exibirQuantidadeDisponiveis();

    std::string alertas = estoque.alertarEstoqueCritico();

    if (!alertas.empty()) {
        std::cout << "\n" << alertas;
    }
}

void Administrador::gerenciarContas(
        Cliente& cliente) {

    std::cout << "\n=== DADOS DO CLIENTE ===\n";
    std::cout << "Nome: " << cliente.getNome() << "\n";
    std::cout << "Email: " << cliente.getEmail() << "\n";
    std::cout << "CPF: " << cliente.getCpf() << "\n";
    std::cout << "Endereco: " << cliente.getEndereco() << "\n";
    std::cout << "Cartoes cadastrados: "
              << cliente.getCartoesSalvos().size()
              << "\n";
}

void Administrador::atualizarVendas(
        Pedido& pedido) {

    std::cout << "\n=== INFORMACOES DA VENDA ===\n";
    std::cout << "Valor total: R$ "
              << pedido.getValorTotal()
              << "\n";

    std::cout << "Frete: R$ "
              << pedido.getValorFrete()
              << "\n";

    std::cout << "Status atual: "
              << static_cast<int>(pedido.getStatus())
              << "\n";
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

    if (Usuario::emailJaCadastrado(_email, nomeArquivo)) {
        return false;
    }

    std::ofstream arquivo(nomeArquivo, std::ios::app);

    if (!arquivo.is_open()) {
        return false;
    }

    arquivo << "administrador" << ";"
            << _nome << ";"
            << _email << ";"
            << _senha << ";"
            << "" << ";"
            << _respostaSeguranca
            << "\n";

    return true;
}