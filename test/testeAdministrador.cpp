#include "doctest.h"
#include <string>

#include "../include/Administrador.hpp"
#include "../include/Catalogo.hpp"
#include "../include/Estoque.hpp"
#include "../include/Cliente.hpp"
#include "../include/Carrinho.hpp"
#include "../include/Pedido.hpp"

TEST_CASE("Administrador - Construtor e Heranca de Usuario") {
    Administrador admin("Djulia", "djulia@ufmg.br", "senha123", "ECA");

    CHECK(admin.getNome() == "Djulia");
    CHECK(admin.getEmail() == "djulia@ufmg.br");
    CHECK(admin.getSenha() == "senha123");
    CHECK(admin.getTipo() == "administrador"); 
    CHECK(admin.getRespostaSeguranca() == "ECA");
}

TEST_CASE("Administrador - Validação e Integracao (Coverage C8)") {
    Administrador admin("Thais", "thais@ufmg.br", "senha123", "PDS2");

    SUBCASE("Barricadas do Construtor Herdado") {
        CHECK_THROWS_AS(Administrador("Joyce", "joyce_sem_arroba.com", "senha123", "UFMG"), std::invalid_argument);
        CHECK_THROWS_AS(Administrador("Thais", "thais@ufmg.br", "123", "PDS2"), std::invalid_argument);
    }

    SUBCASE("Gerar Relatorio de Contas") {
        Cliente cli("Cliente Teste", "cliente@email.com", "senha123", "11144477735", "Resposta");
        cli.adicionarEndereco("Rua UFMG");
        
        std::string relatorio = admin.gerenciarContas(cli);
        CHECK(relatorio.find("Cliente Teste") != std::string::npos);
        CHECK(relatorio.find("11144477735") != std::string::npos);
    }

    SUBCASE("Gerar Relatorio de Vendas") {
        Cliente cli("Cliente Teste", "cliente@email.com", "senha123", "11144477735", "Resposta");
        cli.adicionarEndereco("Rua UFMG");
        Carrinho car(cli);
        Produto livro(1, "Livro", "Descricao", 50.00, 10, CategoriaProduto::Ficcao);
        
        car.adicionarProduto(livro, 1);
        Pedido p(car, cli);
        
        std::string relatorioVenda = admin.atualizarVendas(p);
        CHECK(relatorioVenda.find("Valor total") != std::string::npos);
        CHECK(relatorioVenda.find("50.00") != std::string::npos);
    }

    SUBCASE("Metodos Vazios de Interface Legada") {
        Catalogo c;
        Estoque e;
        CHECK_NOTHROW(admin.gerenciarCatalogo(c));
        CHECK_NOTHROW(admin.gerenciarEstoque(e));
    }
}