#include "Produto.hpp"

Produto::Produto(int id, const std::string& nome, const std::string& descricao, float preco, int quantidadeEstoque) {
    _id = id;
    _nome = nome;
    _descricao = descricao;
    _preco = preco;
    _quantidadeEstoque = quantidadeEstoque;
}

int Produto::getId() const {
    return _id;
}

const std::string& Produto::getNome() const {
    return _nome;
}

const std::string& Produto::getDescricao() const {
    return _descricao;
}

float Produto::getPreco() const {
    return _preco;
}

int Produto::getQuantidadeEstoque() const {
    return _quantidadeEstoque;
}