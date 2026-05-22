#include "Usuario.hpp"

Usuario::Usuario(std::string nome, std::string email, std::string senha)
    : _nome(nome), _email(email), _senha(senha) {}

bool Usuario::validarEmail(std::string novoEmail) const {
    if (novoEmail.empty()) return false;
    for (char c : novoEmail)
        if (c == '@') return true;
    return false;
}

bool Usuario::gerenciarSenha(std::string novaSenha) const {
    return novaSenha.size() >= 6;
}

void Usuario::armazenarNome(std::string novoNome) { _nome = novoNome; }
void Usuario::atualizarDadosPerfil() {}
void Usuario::gerenciarRecuperacaoAcesso() {}
bool Usuario::permitirAlteracaoDados() const { return true; }
const std::string& Usuario::getNome() const { return _nome; }
const std::string& Usuario::getEmail() const { return _email; }
const std::string& Usuario::getSenha() const { return _senha; }
