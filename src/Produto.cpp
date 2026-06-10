#include "Produto.hpp"

Produto::Produto(int id, const std::string& nome, const std::string& descricao, 
                 float preco, int quantidadeEstoque, CategoriaProduto categoria) {
    _id = id;
    _nome = nome;
    _descricao = descricao;
    _preco = preco > 0 ? preco : 0.0f;
    _quantidadeEstoque = quantidadeEstoque > 0 ? quantidadeEstoque : 0; 
    _categoria = categoria;
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

CategoriaProduto Produto::getCategoria() const {
    return _categoria;
}

bool Produto::setPreco(float novoPreco) {
    if (novoPreco > 0) {
        _preco = novoPreco;
        return true;
    }
    return false;
}

bool Produto::debitarEstoque(int quantidadeVendida) {
    if (quantidadeVendida > 0 && _quantidadeEstoque >= quantidadeVendida) {
        _quantidadeEstoque -= quantidadeVendida;
        return true;
    }
    return false;
}

void Produto::adicionarEstoque(int quantidadeRecebida) {
    if (quantidadeRecebida > 0) {
        _quantidadeEstoque += quantidadeRecebida;
    }
}