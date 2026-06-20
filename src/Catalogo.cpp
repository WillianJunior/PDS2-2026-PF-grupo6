#include "Catalogo.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

Catalogo::Catalogo() {}

/**
 * Adiciona um novo produto ao arquivo do catálogo.
 */
void Catalogo::adicionarProduto(
        const Produto& produto) {

    std::ofstream arquivo(
        "catalogo.txt",
        std::ios::app);

    arquivo << produto.getId() << ";"
            << produto.getNome() << ";"
            << produto.getDescricao() << ";"
            << produto.getPreco() << ";"
            << "Ficcao"
            << "\n";
}

/**
 * Remove um produto a partir do ID informado.
 */
void Catalogo::removerProduto(
        int idProduto) {

    std::ifstream entrada("catalogo.txt");

    std::vector<std::string> linhas;

    std::string linha;

    // Copia apenas as linhas que não possuem o ID removido
    while (std::getline(entrada, linha)) {

        std::stringstream ss(linha);

        std::string idTexto;

        std::getline(ss, idTexto, ';');

        if (std::stoi(idTexto) != idProduto) {
            linhas.push_back(linha);
        }
    }

    entrada.close();

    std::ofstream saida("catalogo.txt");

    for (const auto& l : linhas) {
        saida << l << "\n";
    }
}

/**
 * Busca livros contendo a palavra-chave informada.
 */
void Catalogo::buscarItem(
        const std::string& palavraChave) const {

    std::ifstream arquivo("catalogo.txt");

    std::string linha;

    while (std::getline(arquivo, linha)) {

        if (linha.find(palavraChave)
            != std::string::npos) {

            std::cout << linha << std::endl;
        }
    }
}

/**
 * Lista apenas os livros pertencentes à categoria escolhida.
 */
void Catalogo::listarProdutosCategoria(
        CategoriaProduto categoria) const {

    std::string categoriaTexto;

    switch (categoria) {

        case CategoriaProduto::Ficcao:
            categoriaTexto = "Ficcao";
            break;

        case CategoriaProduto::Tecnico:
            categoriaTexto = "Tecnico";
            break;

        case CategoriaProduto::Infantil:
            categoriaTexto = "Infantil";
            break;

        case CategoriaProduto::Romance:
            categoriaTexto = "Romance";
            break;
            
        case CategoriaProduto::Suspense:
            categoriaTexto = "Suspense";
            break;

        case CategoriaProduto::Fantasia:
            categoriaTexto = "Fantasia";
            break;
    }

    std::ifstream arquivo("catalogo.txt");

    std::string linha;

    while (std::getline(arquivo, linha)) {

        if (linha.find(categoriaTexto)
            != std::string::npos) {

            std::cout << linha << std::endl;
        }
    }
}

/**
 * Ordena os livros por preço utilizando Bubble Sort.
 */
void Catalogo::ordenarPreco(
        bool crescente) {

    struct Livro {

        int id;
        std::string nome;
        std::string descricao;
        float preco;
        std::string categoria;
    };

    std::vector<Livro> livros;

    std::ifstream arquivo("catalogo.txt");

    std::string linha;

    // Carrega os livros do arquivo para memória
    while (std::getline(arquivo, linha)) {

        Livro livro;

        std::stringstream ss(linha);

        std::string precoTexto;
        std::string idTexto;

        std::getline(ss, idTexto, ';');
        std::getline(ss, livro.nome, ';');
        std::getline(ss, livro.descricao, ';');
        std::getline(ss, precoTexto, ';');
        std::getline(ss, livro.categoria);

        livro.id = std::stoi(idTexto);
        livro.preco = std::stof(precoTexto);

        livros.push_back(livro);
    }

    // Algoritmo Bubble Sort
    for (size_t i = 0; i < livros.size(); i++) {

        for (size_t j = 0;
             j < livros.size() - 1;
             j++) {

            bool troca;

            if (crescente) {

                troca =
                    livros[j].preco >
                    livros[j + 1].preco;
            }

            else {

                troca =
                    livros[j].preco <
                    livros[j + 1].preco;
            }

            if (troca) {

                Livro aux = livros[j];

                livros[j] =
                    livros[j + 1];

                livros[j + 1] =
                    aux;
            }
        }
    }

    // Exibe os livros ordenados
    for (const auto& livro : livros) {

        std::cout
            << livro.id << " "
            << livro.nome << " "
            << livro.preco
            << std::endl;
    }
}

/**
 * Exibe a descrição de um produto a partir do ID.
 */
void Catalogo::exibirDescricao(
        int idProduto) const {

    std::ifstream arquivo("catalogo.txt");

    std::string linha;

    while (std::getline(arquivo, linha)) {

        std::stringstream ss(linha);

        std::string idTexto;

        std::getline(ss, idTexto, ';');

        if (std::stoi(idTexto)
            == idProduto) {

            std::string nome;
            std::string descricao;

            std::getline(ss, nome, ';');
            std::getline(ss, descricao, ';');

            std::cout
                << descricao
                << std::endl;

            return;
        }
    }
}