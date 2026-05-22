#include "Usuario.hpp"

Usuario::Usuario(std::string nome, std::string email, std::string senha) {
    _nome = nome;
    _email = email;
    _senha = senha;
}

bool Usuario::validarEmail(std::string novoEmail) const {
    size_t arrobaPos = novoEmail.find('@');
    
    if (novoEmail.empty() || 
        arrobaPos == std::string::npos || 
        arrobaPos == 0 || 
        arrobaPos == novoEmail.length() - 1) {
        return false;
    }
    return true; 
}

bool Usuario::gerenciarSenha(std::string novaSenha) const {
    if (novaSenha.length() < 8) {
        return false;
    }
    return true; 
}

std::string Usuario::getNome() const {
    return _nome;
}

std::string Usuario::getEmail() const {
    return _email;
}

std::string Usuario::getSenha() const {
    return _senha;
}

void Usuario::armazenarNome(std::string novoNome) {
    _nome = novoNome;
}

void Usuario::atualizarDadosPerfil() {
}

void Usuario::gerenciarRecuperacaoAcesso() {
}

bool Usuario::permitirAlteracaoDados() const {
    return false;
}