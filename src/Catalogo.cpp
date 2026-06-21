#include "Catalogo.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

Catalogo::Catalogo() {}

void Catalogo::adicionarProduto(const Produto& produto) {
    std::ofstream arquivo("catalogo.txt", std::ios::app);
    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro defensivo: Nao foi possivel abrir o arquivo do catalogo para adicionar produto.");
    }

    arquivo << produto.getId() << ";"
            << produto.getNome() << ";"
            << produto.getDescricao() << ";"
            << produto.getPreco() << ";"
            << "Ficcao\n"; // Categoria padrao utilizada pelo fluxo original do grupo
}

void Catalogo::removerProduto(int idProduto) {
    std::ifstream entrada("catalogo.txt");
    if (!entrada.is_open()) {
        throw std::runtime_error("Erro defensivo: Catalogo nao encontrado para a remocao do item.");
    }

    std::vector<std::string> linhas;
    std::string linha;

    while (std::getline(entrada, linha)) {
        if (linha.empty()) continue;
        std::stringstream ss(linha);
        std::string idTexto;
        std::getline(ss, idTexto, ';');

        if (std::stoi(idTexto) != idProduto) {
            linhas.push_back(linha);
        }
    }
    entrada.close();

    std::ofstream saida("catalogo.txt");
    if (!saida.is_open()) {
        throw std::runtime_error("Erro defensivo: Falha ao reescrever o arquivo apos remocao.");
    }

    for (const auto& l : linhas) {
        saida << l << "\n";
    }
}

std::string Catalogo::buscarItem(const std::string& palavraChave) const {
    std::ifstream arquivo("catalogo.txt");
    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro defensivo: Arquivo de catalogo ausente durante a busca.");
    }

    std::string linha;
    std::string resultado;

    while (std::getline(arquivo, linha)) {
        if (linha.find(palavraChave) != std::string::npos) {
            resultado += linha + "\n";
        }
    }
    return resultado;
}

std::string Catalogo::listarProdutosCategoria(CategoriaProduto categoria) const {
    std::string categoriaTexto;
    switch (categoria) {
        case CategoriaProduto::Ficcao:   categoriaTexto = "Ficcao";   break;
        case CategoriaProduto::Tecnico:  categoriaTexto = "Tecnico";  break;
        case CategoriaProduto::Infantil: categoriaTexto = "Infantil"; break;
        case CategoriaProduto::Romance:  categoriaTexto = "Romance";  break;
        case CategoriaProduto::Suspense: categoriaTexto = "Suspense"; break;
        case CategoriaProduto::Fantasia: categoriaTexto = "Fantasia"; break;
    }

    std::ifstream arquivo("catalogo.txt");
    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro defensivo: Arquivo de catalogo ausente durante a listagem.");
    }

    std::string linha;
    std::string resultado;

    while (std::getline(arquivo, linha)) {
        if (linha.find(categoriaTexto) != std::string::npos) {
            resultado += linha + "\n";
        }
    }
    return resultado;
}

std::string Catalogo::ordenarPreco(bool crescente) {
    struct Livro {
        int id;
        std::string nome;
        std::string descricao;
        float preco;
        std::string categoria;
    };

    std::vector<Livro> livros;
    std::ifstream arquivo("catalogo.txt");
    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro defensivo: Arquivo de catalogo ausente durante a ordenacao.");
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue;
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
    arquivo.close();

    // Algoritmo Bubble Sort original mantido intacto
    for (size_t i = 0; i < livros.size(); i++) {
        for (size_t j = 0; j < livros.size() - 1; j++) {
            bool troca = crescente ? (livros[j].preco > livros[j + 1].preco)
                                   : (livros[j].preco < livros[j + 1].preco);
            if (troca) {
                Livro aux = livros[j];
                livros[j] = livros[j + 1];
                livros[j + 1] = aux;
            }
        }
    }

    std::string resultado;
    for (const auto& livro : livros) {
        resultado += std::to_string(livro.id) + " " + livro.nome + " " + std::to_string(livro.preco) + "\n";
    }
    return resultado;
}

std::string Catalogo::exibirDescricao(int idProduto) const {
    std::ifstream arquivo("catalogo.txt");
    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro defensivo: Arquivo de catalogo ausente na visualizacao de descricao.");
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue;
        std::stringstream ss(linha);
        std::string idTexto;
        std::getline(ss, idTexto, ';');

        if (std::stoi(idTexto) == idProduto) {
            std::string nome;
            std::string descricao;
            std::getline(ss, nome, ';');
            std::getline(ss, descricao, ';');
            return descricao;
        }
    }
    return ""; 
}