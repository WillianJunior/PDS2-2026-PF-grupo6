#include "Administrador.hpp"
#include <iostream>

Administrador::Administrador(std::string nome, std::string email, std::string senha)
    : Usuario(nome, email, senha) {}

void Administrador::gerenciarCatalogo(Catalogo&) {
    std::cout << "Administrador gerenciando catálogo\n";
}

void Administrador::gerenciarEstoque(Estoque&) {
    std::cout << "Administrador gerenciando estoque\n";
}

void Administrador::gerenciarContas(Cliente&) {
    std::cout << "Administrador gerenciando clientes\n";
}

void Administrador::atualizarVendas(Pedido&) {
    std::cout << "Administrador atualizando pedidos\n";
}