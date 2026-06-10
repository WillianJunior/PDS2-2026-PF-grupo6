#include "doctest.h"
#include <string>
#include <cstdio> 

#include "../include/Administrador.hpp"
#include "../include/Catalogo.hpp"
#include "../include/Estoque.hpp"
#include "../include/Cliente.hpp"
#include "../include/Carrinho.hpp"
#include "../include/Pedido.hpp"

TEST_CASE("Administrador - Construtor e Herança de Usuario") {
    Administrador admin("Djulia", "djulia@ufmg.br", "senha123", "ECA");

    CHECK(admin.getNome() == "Djulia");
    CHECK(admin.getEmail() == "djulia@ufmg.br");
    CHECK(admin.getSenha() == "senha123");
    CHECK(admin.getTipo() == "admin");
    CHECK(admin.getRespostaSeguranca() == "ECA");
}

TEST_CASE("Administrador - Validação e Cadastro (Coverage C8)") {
    std::string arquivoTeste = "admin_teste_pds2.txt";

    std::remove(arquivoTeste.c_str()); 

    SUBCASE("Cadastro com dados válidos") {
        Administrador admin("Viviane", "viviane@ufmg.br", "senhaSegura", "Engenharia");
        CHECK(admin.cadastrarAdministrador(arquivoTeste) == true);
    }

    SUBCASE("Tentativa de cadastro com email inválido") {

        Administrador admin("Joyce", "joyce_sem_arroba.com", "senha123", "UFMG");
        CHECK(admin.cadastrarAdministrador(arquivoTeste) == false);
    }

    SUBCASE("Tentativa de cadastro com senha muito curta") {

        Administrador admin("Thais", "thais@ufmg.br", "123", "PDS2");
        CHECK(admin.cadastrarAdministrador(arquivoTeste) == false);
    }

    SUBCASE("Tentativa de cadastro com resposta de segurança vazia") {
        Administrador admin("Djulia", "djulia@ufmg.br", "senha123", "");
        CHECK(admin.cadastrarAdministrador(arquivoTeste) == false);
    }

    std::remove(arquivoTeste.c_str()); 
}

TEST_CASE("Administrador - Integracao com outros modulos (Ponteiros/Referencias)") {
    Administrador admin("Thais", "thais@ufmg.br", "senha123", "PDS2");
    
    SUBCASE("Gerenciar Catálogo") {
        Catalogo c;
        CHECK_NOTHROW(admin.gerenciarCatalogo(c));
    }

    SUBCASE("Gerenciar Estoque") {
        Estoque e;
        CHECK_NOTHROW(admin.gerenciarEstoque(e));
    }

    SUBCASE("Gerenciar Contas") {
     
        Cliente cli("Cliente Teste", "cliente@email.com", "senha123", "11144477735", "Resposta");
        CHECK_NOTHROW(admin.gerenciarContas(cli));
    }

    SUBCASE("Atualizar Vendas") {
        Cliente cli("Cliente Teste", "cliente@email.com", "senha123", "11144477735", "Resposta");
        Carrinho car(cli);
        Pedido p(car, cli);
        CHECK_NOTHROW(admin.atualizarVendas(p));
    }
}
