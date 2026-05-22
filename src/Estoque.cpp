#include "Estoque.hpp"
#include <iostream>

Estoque::Estoque() {
    _inventario.push_back(Produto(1, "Livro TDD",       "Descricao", 45.90,  10));
    _inventario.push_back(Produto(2, "Clean Code",      "Descricao", 89.90,   3));
    _inventario.push_back(Produto(3, "Design Patterns", "Descricao", 120.00,  0));
}

void Estoque::exibirQuantidadeDisponiveis() const {
    for (const Produto& p : _inventario)
        std::cout << p.getNome() << ": " << p.getQuantidadeEstoque() << " unidades\n";
}

void Estoque::alertarEstoqueCritico() const {
    for (const Produto& p : _inventario)
        if (p.getQuantidadeEstoque() < 5)
            std::cout << "ALERTA: " << p.getNome() << " com estoque critico!\n";
}

void Estoque::congelarQuantidades(int idProduto, int quantidade) {
    for (Produto& p : _inventario)
        if (p.getId() == idProduto && p.getQuantidadeEstoque() >= quantidade)
            return; // reserva validada — subtração real vem no efetuarSubtracao
}

void Estoque::efetuarSubtracao(int idProduto, int quantidade) {
    for (Produto& p : _inventario)
        if (p.getId() == idProduto && p.getQuantidadeEstoque() >= quantidade)
            return; // subtração será persistida no .txt no C8
}

bool Estoque::impedirVendasAcimaMaximo(int idProduto, int quantidadeDesejada) const {
    for (const Produto& p : _inventario)
        if (p.getId() == idProduto)
            return p.getQuantidadeEstoque() >= quantidadeDesejada;
    return false;
}