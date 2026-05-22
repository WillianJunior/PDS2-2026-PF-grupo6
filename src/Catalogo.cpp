// Catalogo.cpp

#include "Catalogo.hpp"
#include <iostream>

Catalogo::Catalogo() {}

/**
 * @brief Lista produtos da categoria selecionada.
 */
void Catalogo::listarProdutosCategoria(CategoriaProduto categoria) const {

    std::cout << "Funcionalidade ainda nao implementada."
              << std::endl;
}

/**
 * @brief Busca produtos usando palavra-chave.
 */
void Catalogo::buscarItem(const std::string& palavraChave) const {

    std::cout << "Busca ainda nao implementada."
              << std::endl;
}

/**
 * @brief Ordena produtos pelo preco.
 */
void Catalogo::ordenarPreco(bool crescente) {

    std::cout << "Ordenacao ainda nao implementada."
              << std::endl;
}

/**
 * @brief Exibe descricao de um produto.
 */
void Catalogo::exibirDescricao(int idProduto) const {

    std::cout << "Descricao ainda nao implementada."
              << std::endl;
}

/**
 * @brief Adiciona produto ao catalogo.
 */
void Catalogo::adicionarProduto(const Produto& produto) {

    produtos_.push_back(produto);

    std::cout << "Produto adicionado."
              << std::endl;
}

/**
 * @brief Remove produto do catalogo.
 */
void Catalogo::removerProduto(int idProduto) {

    std::cout << "Remocao ainda nao implementada."
              << std::endl;
}