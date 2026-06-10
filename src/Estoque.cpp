#include "Estoque.hpp"

Estoque::Estoque() {
    _inventario.push_back(Produto(1, "Livro TDD",       "Descricao", 45.90,  10, CategoriaProduto::Tecnico));
    _inventario.push_back(Produto(2, "Clean Code",      "Descricao", 89.90,   3, CategoriaProduto::Tecnico));
    _inventario.push_back(Produto(3, "Design Patterns", "Descricao", 120.00,  0, CategoriaProduto::Tecnico));
}

std::string Estoque::exibirQuantidadeDisponiveis() const {
    std::string resultado;
    for (const Produto& p : _inventario)
        resultado += p.getNome() + ": " +
                     std::to_string(p.getQuantidadeEstoque()) +
                     " unidades\n";
    return resultado;
}

std::string Estoque::alertarEstoqueCritico() const {
    std::string alertas;
    for (const Produto& p : _inventario)
        if (p.getQuantidadeEstoque() < 5)
            alertas += "ALERTA: " + p.getNome() + " com estoque critico!\n";
    return alertas;
}

void Estoque::congelarQuantidades(int idProduto, int quantidade) {
    for (Produto& p : _inventario)
        if (p.getId() == idProduto && p.getQuantidadeEstoque() >= quantidade)
            return; // reserva validada — subtração real vem no efetuarSubtracao
}

void Estoque::efetuarSubtracao(int idProduto, int quantidade) {
    for (Produto& p : _inventario)
        if (p.getId() == idProduto)
            p.debitarEstoque(quantidade);
}

bool Estoque::impedirVendasAcimaMaximo(int idProduto, int quantidadeDesejada) const {
    for (const Produto& p : _inventario)
        if (p.getId() == idProduto)
            return p.getQuantidadeEstoque() >= quantidadeDesejada;
    return false;
}