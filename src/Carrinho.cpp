#include "Carrinho.hpp"

Carrinho::Carrinho(Cliente& cliente) : _cliente(cliente) {}

int Carrinho::buscarIdProduto(int idProduto) const {
    for (int i = 0; i < _produtos.size(); i++) {
        if (_produtos[i].getId() == idProduto) {
            return i;
        }
    }
    return -1;
}

bool Carrinho::validarEstoque(const Produto& produto, int quantidade) {
    return produto.getQuantidadeEstoque() >= quantidade;
}

void Carrinho::adicionarProduto(const Produto& produto, int quantidade) {
    if (quantidade <= 0) return;
    if (!validarEstoque(produto, quantidade)) return;

    int indice = buscarIdProduto(produto.getId());

    if (indice != -1) {
        _quantidades[indice] += quantidade;
    } else {
        _produtos.push_back(produto);
        _quantidades.push_back(quantidade);
    }
}

void Carrinho::removerProduto(int idProduto) {
    int indice = buscarIdProduto(idProduto);
    if (indice == -1) return;

    _produtos.erase(_produtos.begin() + indice);
    _quantidades.erase(_quantidades.begin() + indice);
}

void Carrinho::atualizarQuantidade(int idProduto, int novaQuantidade) {
    if (novaQuantidade < 0) return;

    int indice = buscarIdProduto(idProduto);
    if (indice == -1) return;

    const Produto& produto = _produtos[indice];
    if (!validarEstoque(produto, novaQuantidade)) return;

    _quantidades[indice] = novaQuantidade;
}

void Carrinho::limparCarrinho() {
    _produtos.clear();
    _quantidades.clear();
}

double Carrinho::calcularSubtotal() const {
    double subtotal = 0.0;

    for (int i = 0; i < _produtos.size(); i++) {
        subtotal += _produtos[i].getPreco() * _quantidades[i];
    }

    return subtotal;
}

double Carrinho::calcularValorFrete() const {
    double subtotal = calcularSubtotal();

    if (subtotal == 0.0 || subtotal >= 300.0)
        return 0.0;
    else if (subtotal >= 100.0)
        return 15.0;
    else
        return 20.0;
}

double Carrinho::calcularTotal() const {
    return calcularSubtotal() + calcularValorFrete();
}

bool Carrinho::vazio() const {
    return _produtos.empty();
}

int Carrinho::getQuantidadeItens() const {
    return _produtos.size();
}



























