#include "Administrador.hpp"

Administrador::Administrador(
        std::string nome,
        std::string email,
        std::string senha,
        std::string respostaSeguranca)

    : Usuario(nome,
              email,
              senha,
              "admin",
              respostaSeguranca) {
}

void Administrador::gerenciarCatalogo(
        Catalogo&) {
}

void Administrador::gerenciarEstoque(
        Estoque&) {
}

void Administrador::gerenciarContas(
        Cliente&) {
}

void Administrador::atualizarVendas(
        Pedido&) {
}

bool Administrador::cadastrarAdministrador(
        const std::string& nomeArquivo) const {

    if (!validarEmail(_email)) {
        return false;
    }

    if (!gerenciarSenha(_senha)) {
        return false;
    }

    if (_respostaSeguranca.empty()) {
        return false;
    }

    return Usuario::salvarUsuario(
        "admin",
        _nome,
        _email,
        _senha,
        "",
        _respostaSeguranca,
        nomeArquivo
    );
}