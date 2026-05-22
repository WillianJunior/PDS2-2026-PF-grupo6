#include "doctest.h"
#include <string>

#include "../include/Administrador.hpp"
#include "../include/Catalogo.hpp"
#include "../include/Estoque.hpp"
#include "../include/Cliente.hpp"
#include "../include/Carrinho.hpp"
#include "../include/Pedido.hpp"

TEST_CASE("Construtor do Administrador") {
    Administrador admin("Root", "admin@loja.com", "123456");

   CHECK(admin.getNome() == "Root");
    CHECK(admin.getEmail() == "admin@loja.com");
    CHECK(admin.getSenha() == "123456");
}

TEST_CASE("Gerenciar catalogo nao deve lançar excecao") {
    Administrador admin("Root", "admin@loja.com", "123456");
    Catalogo c;

    CHECK_NOTHROW(admin.gerenciarCatalogo(c));
}

TEST_CASE("Gerenciar estoque nao deve lançar excecao") {
    Administrador admin("Root", "admin@loja.com", "123456");
    Estoque e;

    CHECK_NOTHROW(admin.gerenciarEstoque(e));
}

TEST_CASE("Gerenciar contas nao deve lançar excecao") {
    Administrador admin("Root", "admin@loja.com", "123456");
    Cliente cli("Ana", "ana@email.com", "senha123", "52998224725");

    CHECK_NOTHROW(admin.gerenciarContas(cli));
}

TEST_CASE("Atualizar vendas nao deve lançar excecao") {
    Administrador admin("Root", "admin@loja.com", "123456");
    Cliente cli("Ana", "ana@email.com", "senha123", "52998224725");
    Carrinho car(cli);
    Pedido p(car, cli);

    CHECK_NOTHROW(admin.atualizarVendas(p));
}
