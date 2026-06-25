#include "Administrador.hpp"
#include "Cliente.hpp" 
#include "Pedido.hpp"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

Administrador::Administrador(
        const std::string& nome,
        const std::string& email,
        const std::string& senha,
        const std::string& respostaSeguranca)
    : Usuario(nome, email, senha, "administrador", respostaSeguranca) {
}

void Administrador::exibirPerfil() const {
    std::cout << "[STATUS: ADMINISTRADOR DO SISTEMA]\n";
    Usuario::exibirPerfil();
}

std::string Administrador::gerenciarContas(const Cliente& cliente) const {
    std::stringstream ss;
    ss << "\n=== DADOS DO CLIENTE ===\n"
       << "Nome: " << cliente.getNome() << "\n"
       << "Email: " << cliente.getEmail() << "\n"
       << "CPF: " << cliente.getCpf() << "\n"
       << "Endereco: " << cliente.getEndereco() << "\n"
       << "Cartoes cadastrados: " << cliente.getCartoesSalvos().size() << "\n";
    return ss.str();
}

std::string Administrador::atualizarVendas(const Pedido& pedido) const {
    std::stringstream ss;

    ss << std::fixed << std::setprecision(2);
    ss << "\n=== INFORMACOES DA VENDA ===\n"
       << "Valor total: R$ " << pedido.getValorTotal() << "\n"
       << "Frete: R$ " << pedido.getValorFrete() << "\n"
       << "Status atual: " << static_cast<int>(pedido.getStatus()) << "\n";
    return ss.str();
}

bool Administrador::cadastrarAdministrador(const std::string& nomeArquivo) const {
    if (!validarEmail(_email) || !gerenciarSenha(_senha) || _respostaSeguranca.empty()) {
        throw std::invalid_argument("Operacao bloqueada: Dados invalidos para administrador.");
    }

    if (Usuario::emailJaCadastrado(_email, nomeArquivo)) {
        return false;
    }

    std::ofstream arquivo(nomeArquivo, std::ios::app);
    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro de I/O: Falha ao registrar administrador no arquivo.");
    }

    arquivo << "administrador" << ";"
            << _nome << ";"
            << _email << ";"
            << _senha << ";"
            << "" << ";" 
            << _respostaSeguranca << "\n";

    return true;
}