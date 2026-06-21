#include "Administrador.hpp"
#include "Catalogo.hpp" 
#include "Estoque.hpp"  
#include "Cliente.hpp" 
#include "Pedido.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

Administrador::Administrador(
        std::string nome,
        std::string email,
        std::string senha,
        std::string respostaSeguranca)
    : Usuario(nome, email, senha, "administrador", respostaSeguranca) {
}

// Métodos obsoletos de menu limpos para evitar inputs/outputs na camada de negócio.
void Administrador::gerenciarCatalogo(Catalogo&) {}
void Administrador::gerenciarEstoque(Estoque&) {}

std::string Administrador::gerenciarContas(Cliente& cliente) {
    std::stringstream ss;
    ss << "\n=== DADOS DO CLIENTE ===\n"
       << "Nome: " << cliente.getNome() << "\n"
       << "Email: " << cliente.getEmail() << "\n"
       << "CPF: " << cliente.getCpf() << "\n"
       << "Endereco: " << cliente.getEndereco() << "\n"
       << "Cartoes cadastrados: " << cliente.getCartoesSalvos().size() << "\n";
    return ss.str();
}

std::string Administrador::atualizarVendas(Pedido& pedido) {
    std::stringstream ss;
    ss << "\n=== INFORMACOES DA VENDA ===\n"
       << "Valor total: R$ " << pedido.getValorTotal() << "\n"
       << "Frete: R$ " << pedido.getValorFrete() << "\n"
       << "Status atual: " << static_cast<int>(pedido.getStatus()) << "\n";
    return ss.str();
}

bool Administrador::cadastrarAdministrador(const std::string& nomeArquivo) const {
    if (!validarEmail(_email) || !gerenciarSenha(_senha) || _respostaSeguranca.empty()) {
        return false;
    }

    if (Usuario::emailJaCadastrado(_email, nomeArquivo)) {
        return false;
    }

    std::ofstream arquivo(nomeArquivo, std::ios::app);
    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro defensivo: Falha ao registrar nova conta administrativa no arquivo de texto.");
    }

    arquivo << "administrador" << ";"
            << _nome << ";"
            << _email << ";"
            << _senha << ";"
            << "" << ";" // Conta administrativa não possui campo de CPF
            << _respostaSeguranca << "\n";

    return true;
}