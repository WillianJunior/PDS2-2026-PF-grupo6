#include "doctest.h"
#include <string>

#include "Usuario.hpp"
#include "Administrador.hpp"
#include "Catalogo.hpp"
#include "Cliente.hpp"
#include "Pedido.hpp"
#include "Carrinho.hpp"

TEST_CASE("Construtor do Administrador") {
    Administrador admin("Root", "admin@loja.com", "123456");

    CHECK(admin.validarEmail("admin@loja.com") == true);
    CHECK(admin.validarEmail("email_invalido.com") == false);
    CHECK(admin.permitirAlteracaoDados() == true);
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
    Cliente cli;

    CHECK_NOTHROW(admin.gerenciarContas(cli));
}

TEST_CASE("Atualizar vendas nao deve lançar excecao") {
    Administrador admin("Root", "admin@loja.com", "123456");
    Pedido p;

    CHECK_NOTHROW(admin.atualizarVendas(p));
}