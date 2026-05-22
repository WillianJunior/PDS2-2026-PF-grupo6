#ifndef CARRINHO_HPP
#define CARRINHO_HPP

#include <vector>
#include "Produto.hpp"
#include "Cliente.hpp"

class Carrinho {
private:
    Cliente& _cliente;
    std::vector<Produto> _produtos;
    std::vector<int> _quantidades;

    int buscarIdProduto(int idProduto) const;
    bool validarEstoque(const Produto& produto, int quantidade);

public:
    Carrinho(Cliente& cliente);

    void adicionarProduto(const Produto& produto, int quantidade);
    void removerProduto(int idProduto);
    void atualizarQuantidade(int idProduto, int novaQuantidade);
    void limparCarrinho();

    double calcularSubtotal() const;
    double calcularValorFrete() const;
    double calcularTotal() const;

    bool vazio() const;
    int getQuantidadeItens() const;
};

#endif