#include "Carrinho.hpp"

#include <fstream>
#include <sstream>

Carrinho::Carrinho(Cliente& cliente) : _cliente(cliente) {
    carregarCarrinhoDoArquivo();
}

int Carrinho::buscarIdProduto(int idProduto) const {
    for (int i = 0; i < static_cast<int>(_produtos.size()); i++) {
        if (_produtos[i].getId() == idProduto) {
            return i;
        }
    }

    return -1;
}

bool Carrinho::validarEstoque(const Produto& produto, int quantidade) const {
    return produto.getQuantidadeEstoque() >= quantidade;
}

void Carrinho::adicionarProduto(const Produto& produto, int quantidade) {
    if (quantidade <= 0) {
        return;
    }

    int indiceProduto = buscarIdProduto(produto.getId());

    if (indiceProduto != -1) {
        int quantidadeTotal = _quantidades[indiceProduto] + quantidade;

        if (!validarEstoque(produto, quantidadeTotal)) {
            return;
        }

        _quantidades[indiceProduto] = quantidadeTotal;
    } else {
        if (!validarEstoque(produto, quantidade)) {
            return;
        }

        _produtos.push_back(produto);
        _quantidades.push_back(quantidade);
    }

    salvarCarrinhoNoArquivo();
}

void Carrinho::removerProduto(int idProduto) {
    int indiceProduto = buscarIdProduto(idProduto);

    if (indiceProduto == -1) {
        return;
    }

    _produtos.erase(_produtos.begin() + indiceProduto);
    _quantidades.erase(_quantidades.begin() + indiceProduto);

    salvarCarrinhoNoArquivo();
}

void Carrinho::atualizarQuantidade(int idProduto, int novaQuantidade) {
    if (novaQuantidade < 0) {
        return;
    }

    int indiceProduto = buscarIdProduto(idProduto);

    if (indiceProduto == -1) {
        return;
    }

    if (novaQuantidade == 0) {
        removerProduto(idProduto);
        return;
    }

    const Produto& produto = _produtos[indiceProduto];

    if (!validarEstoque(produto, novaQuantidade)) {
        return;
    }

    _quantidades[indiceProduto] = novaQuantidade;

    salvarCarrinhoNoArquivo();
}

void Carrinho::limparCarrinho() {
    _produtos.clear();
    _quantidades.clear();

    salvarCarrinhoNoArquivo();
}

double Carrinho::calcularSubtotal() const {
    double subtotal = 0.0;

    for (int i = 0; i < static_cast<int>(_produtos.size()); i++) {
        subtotal += _produtos[i].getPreco() * _quantidades[i];
    }

    return subtotal;
}

double Carrinho::calcularValorFrete() const {
    double subtotal = calcularSubtotal();

    if (subtotal == 0.0 || subtotal >= 300.0) {
        return 0.0;
    }

    if (subtotal >= 100.0) {
        return 15.0;
    }

    return 20.0;
}

double Carrinho::calcularTotal() const {
    return calcularSubtotal() + calcularValorFrete();
}

double Carrinho::getValorTotal() const {
    return calcularTotal();
}

double Carrinho::getValorFrete() const {
    return calcularValorFrete();
}

const std::vector<Produto>& Carrinho::getProdutos() const {
    return _produtos;
}

const std::vector<int>& Carrinho::getQuantidades() const {
    return _quantidades;
}

void Carrinho::salvarCarrinhoNoArquivo() const {
    std::ifstream arquivoLeitura("Carrinho.txt");
    std::stringstream buffer;
    std::string linha;
    std::string cpfCliente = _cliente.getCpf();

    bool ignorarBlocoCliente = false;

    if (arquivoLeitura.is_open()) {
        while (std::getline(arquivoLeitura, linha)) {
            if (linha == cpfCliente) {
                ignorarBlocoCliente = true;
                continue;
            }

            if (ignorarBlocoCliente && linha == "END") {
                ignorarBlocoCliente = false;
                continue;
            }

            if (!ignorarBlocoCliente) {
                buffer << linha << std::endl;
            }
        }

        arquivoLeitura.close();
    }

    std::ofstream arquivoEscrita("Carrinho.txt");

    arquivoEscrita << buffer.str();

    arquivoEscrita << cpfCliente << std::endl;

    for (int i = 0; i < static_cast<int>(_produtos.size()); i++) {
        arquivoEscrita << _produtos[i].getId() << ","
                       << _produtos[i].getNome() << ","
                       << _produtos[i].getPreco() << ","
                       << _produtos[i].getQuantidadeEstoque() << ","
                       << _quantidades[i] << std::endl;
    }

    arquivoEscrita << "END" << std::endl;

    arquivoEscrita.close();
}

void Carrinho::carregarCarrinhoDoArquivo() {
    std::ifstream arquivo("Carrinho.txt");
    std::string linha;
    std::string cpfCliente = _cliente.getCpf();

    if (!arquivo.is_open()) {
        return;
    }

    bool carregarProdutos = false;

    while (std::getline(arquivo, linha)) {
        if (linha == cpfCliente) {
            carregarProdutos = true;
            continue;
        }

        if (carregarProdutos) {
            if (linha == "END") {
                break;
            }

            std::stringstream ss(linha);
            std::string idStr;
            std::string nome;
            std::string precoStr;
            std::string estoqueStr;
            std::string quantidadeStr;

            std::getline(ss, idStr, ',');
            std::getline(ss, nome, ',');
            std::getline(ss, precoStr, ',');
            std::getline(ss, estoqueStr, ',');
            std::getline(ss, quantidadeStr);

            if (idStr.empty() || nome.empty() || precoStr.empty() ||
                estoqueStr.empty() || quantidadeStr.empty()) {
                continue;
            }

            int id = std::stoi(idStr);
            float preco = std::stof(precoStr);
            int estoque = std::stoi(estoqueStr);
            int quantidade = std::stoi(quantidadeStr);

            Produto produto(id, nome, "", preco, estoque, CategoriaProduto::Ficcao);

            _produtos.push_back(produto);
            _quantidades.push_back(quantidade);
        }
    }

    arquivo.close();
}
