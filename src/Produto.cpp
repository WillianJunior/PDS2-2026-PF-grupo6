#include "Produto.hpp"
#include <stdexcept> 

Produto::Produto(int id, const std::string& nome, const std::string& descricao, 
                 float preco, int quantidadeEstoque, CategoriaProduto categoria) {

    if (preco <= 0) {
        throw std::invalid_argument("Erro: O preço do produto deve ser maior que zero.");
    }
    if (quantidadeEstoque < 0) {
        throw std::invalid_argument("Erro: A quantidade inicial de estoque não pode ser negativa.");
    }

    _id = id;
    _nome = nome;
    _descricao = descricao;
    _preco = preco;
    _quantidadeEstoque = quantidadeEstoque;
    _categoria = categoria;
}

int Produto::getId() const { return _id; }
const std::string& Produto::getNome() const { return _nome; }
const std::string& Produto::getDescricao() const { return _descricao; }
float Produto::getPreco() const { return _preco; }
int Produto::getQuantidadeEstoque() const { return _quantidadeEstoque; }
CategoriaProduto Produto::getCategoria() const { return _categoria; }

void Produto::setPreco(float novoPreco) {
    if (novoPreco <= 0) {
        throw std::invalid_argument("Erro: O novo preço deve ser maior que zero.");
    }
    _preco = novoPreco;
}

void Produto::debitarEstoque(int quantidadeVendida) {
    if (quantidadeVendida <= 0) {
        throw std::invalid_argument("Erro: A quantidade a ser debitada deve ser maior que zero.");
    }
    if (quantidadeVendida > _quantidadeEstoque) {
        throw std::out_of_range("Erro: Estoque insuficiente para realizar o débito.");
    }
    _quantidadeEstoque -= quantidadeVendida;
}

void Produto::adicionarEstoque(int quantidadeRecebida) {
    if (quantidadeRecebida <= 0) {
        throw std::invalid_argument("Erro: A quantidade a ser adicionada deve ser maior que zero.");
    }
    _quantidadeEstoque += quantidadeRecebida;
}