#include "Cliente.hpp"

Cliente::Cliente(std::string nome, std::string email, std::string senha, std::string cpf)
    : Usuario(nome, email, senha), _cpf(cpf) {}

bool Cliente::validarCpf() const {
    std::string cpf = "";
    for (char c : _cpf)
        if (isdigit(c)) cpf += c;

    if (cpf.size() != 11) return false;

    bool todosIguais = true;
    for (int i = 1; i < 11; i++)
        if (cpf[i] != cpf[0]) { todosIguais = false; break; }
    if (todosIguais) return false;

    int soma = 0;
    for (int i = 0; i < 9; i++) soma += (cpf[i] - '0') * (10 - i);
    int resto = (soma * 10) % 11;
    if (resto == 10 || resto == 11) resto = 0;
    if (resto != (cpf[9] - '0')) return false;

    soma = 0;
    for (int i = 0; i < 10; i++) soma += (cpf[i] - '0') * (11 - i);
    resto = (soma * 10) % 11;
    if (resto == 10 || resto == 11) resto = 0;
    return resto == (cpf[10] - '0');
}

void Cliente::adicionarEndereco(std::string novoEndereco) {
    _enderecos.push_back(novoEndereco);
}

void Cliente::adicionarMetodoPagamento(std::string novoMetodo) {
    _metodosPagamento.push_back(novoMetodo);
}