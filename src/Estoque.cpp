#include "Estoque.hpp"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>


static std::string categoriaParaTexto(
        CategoriaProduto categoria) {

    switch (categoria) {
        case CategoriaProduto::Ficcao:   return "Ficcao";
        case CategoriaProduto::Tecnico:  return "Tecnico";
        case CategoriaProduto::Infantil: return "Infantil";
        case CategoriaProduto::Romance:  return "Romance";
        case CategoriaProduto::Suspense: return "Suspense";
        case CategoriaProduto::Fantasia: return "Fantasia";
    }
    return "Desconhecida";
}

static CategoriaProduto textoParaCategoria(
        const std::string& texto) {

    if (texto == "Ficcao")   return CategoriaProduto::Ficcao;
    if (texto == "Tecnico")  return CategoriaProduto::Tecnico;
    if (texto == "Infantil") return CategoriaProduto::Infantil;
    if (texto == "Romance")  return CategoriaProduto::Romance;
    if (texto == "Suspense") return CategoriaProduto::Suspense;
    if (texto == "Fantasia") return CategoriaProduto::Fantasia;

    throw std::invalid_argument(
        "Categoria invalida no arquivo de estoque: " + texto);
}


void Estoque::carregarEstoque() {

    std::ifstream arquivo(_nomeArquivo);

    if (!arquivo.is_open()) {
        return;
    }

    _inventario.clear();

    std::string linha;

    while (std::getline(arquivo, linha)) {

        if (linha.empty()) {
            continue;
        }

        std::stringstream ss(linha);

        std::string idStr;
        std::string nome;
        std::string descricao;
        std::string precoStr;
        std::string qtdStr;
        std::string catStr;

        if (!std::getline(ss, idStr,     ';') ||
            !std::getline(ss, nome,      ';') ||
            !std::getline(ss, descricao, ';') ||
            !std::getline(ss, precoStr,  ';') ||
            !std::getline(ss, qtdStr,    ';') ||
            !std::getline(ss, catStr)) {

            throw std::runtime_error(
                "Dados corrompidos no arquivo de estoque.");
        }
        if (!catStr.empty() && catStr.back() == '\r') {
            catStr.pop_back();
        }

        try {
            int id        = std::stoi(idStr);
            float preco   = std::stof(precoStr);
            int quantidade = std::stoi(qtdStr);
            CategoriaProduto cat = textoParaCategoria(catStr);

            _inventario.push_back(
                Produto(id, nome, descricao,
                        preco, quantidade, cat));

        } catch (const std::invalid_argument& e) {
            throw std::runtime_error(
                std::string("Dado invalido no arquivo de estoque: ") +
                e.what());
        }
    }
}

void Estoque::salvarEstoque() const {

    std::ofstream arquivo(_nomeArquivo);

    if (!arquivo.is_open()) {
        throw std::runtime_error(
            "Erro ao abrir arquivo de estoque para escrita: " +
            _nomeArquivo);
    }

    for (const Produto& p : _inventario) {

        arquivo << p.getId()               << ";"
                << p.getNome()             << ";"
                << p.getDescricao()        << ";"
                << p.getPreco()            << ";"
                << p.getQuantidadeEstoque() << ";"
                << categoriaParaTexto(p.getCategoria())
                << "\n";

        if (!arquivo.good()) {
            throw std::runtime_error(
                "Erro ao escrever no arquivo de estoque.");
        }
    }
}


Estoque::Estoque(const std::string& nomeArquivo)
    : _nomeArquivo(nomeArquivo) {

    carregarEstoque();

    if (_inventario.empty()) {

        _inventario.push_back(
            Produto(1, "Livro TDD",
                    "Introducao ao TDD em C++",
                    45.90f, 10,
                    CategoriaProduto::Tecnico));

        _inventario.push_back(
            Produto(2, "Clean Code",
                    "Guia de boas praticas de programacao",
                    89.90f, 3,
                    CategoriaProduto::Tecnico));

        _inventario.push_back(
            Produto(3, "Design Patterns",
                    "Padroes de projeto orientado a objetos",
                    120.00f, 0,
                    CategoriaProduto::Tecnico));

        salvarEstoque();
    }
}


std::vector<Produto> Estoque::obterInventario() const {
    return _inventario;
}

std::vector<Produto> Estoque::obterProdutosEmAlerta() const {
    std::vector<Produto> produtosEmAlerta;
    
    for (const Produto& p : _inventario) {
        if (p.getQuantidadeEstoque() < 5) {
            produtosEmAlerta.push_back(p);
        }
    }
    
    return produtosEmAlerta;
}


void Estoque::congelarQuantidades(
        int idProduto,
        int quantidade) const {

    if (quantidade <= 0) {
        throw std::invalid_argument(
            "Quantidade de reserva deve ser positiva.");
    }

    for (const Produto& p : _inventario) {

        if (p.getId() == idProduto) {

            if (p.getQuantidadeEstoque() < quantidade) {
                throw std::runtime_error(
                    "Estoque insuficiente para reserva.");
            }

            return;
        }
    }

    throw std::runtime_error(
        "Produto nao encontrado no estoque.");
}

void Estoque::efetuarSubtracao(
        int idProduto,
        int quantidade) {

    if (quantidade <= 0) {
        throw std::invalid_argument(
            "Quantidade para subtracao deve ser positiva.");
    }

    for (Produto& p : _inventario) {

        if (p.getId() == idProduto) {

            if (!p.debitarEstoque(quantidade)) {
                throw std::runtime_error(
                    "Estoque insuficiente para subtracao.");
            }

            salvarEstoque();

            return;
        }
    }

    throw std::runtime_error(
        "Produto nao encontrado no estoque.");
}

bool Estoque::impedirVendasAcimaMaximo(
        int idProduto,
        int quantidadeDesejada) const {

    for (const Produto& p : _inventario) {

        if (p.getId() == idProduto) {
            return p.getQuantidadeEstoque() >= quantidadeDesejada;
        }
    }

    return false;
}