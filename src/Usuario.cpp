#include "Usuario.hpp"

#include <fstream>
#include <sstream>
#include <vector>

Usuario::Usuario(std::string nome,
                 std::string email,
                 std::string senha,
                 std::string tipo,
                 std::string respostaSeguranca)
    : _nome(nome),
      _email(email),
      _senha(senha),
      _tipo(tipo),
      _respostaSeguranca(respostaSeguranca) {}

bool Usuario::validarEmail(std::string novoEmail) const {
    if (novoEmail.empty()) {
        return false;
    }

    bool temArroba = false;
    bool temPonto = false;
    size_t posArroba = 0;
    size_t posPonto = 0;

    for (size_t i = 0; i < novoEmail.size(); i++) {
        if (novoEmail[i] == '@') {
            temArroba = true;
            posArroba = i;
        }
        // ponto só conta se vier depois do @
        if (novoEmail[i] == '.' && temArroba) {
            temPonto = true;
            posPonto = i;
        }
    }

    // @ não pode ser o primeiro char, e precisa ter ponto após o @
    if (!temArroba || posArroba == 0 || !temPonto) {
        return false;
    }

    // precisa ter pelo menos 2 chars após o ponto (ex: .com)
    return (novoEmail.size() - posPonto) > 2;
}

bool Usuario::gerenciarSenha(std::string novaSenha) const {
    return novaSenha.size() >= 6;
}

void Usuario::armazenarNome(std::string novoNome) {
    _nome = novoNome;
}

void Usuario::atualizarDadosPerfil() {
}

bool Usuario::permitirAlteracaoDados() const {
    return true;
}

const std::string& Usuario::getNome() const {
    return _nome;
}

const std::string& Usuario::getEmail() const {
    return _email;
}

const std::string& Usuario::getSenha() const {
    return _senha;
}

const std::string& Usuario::getTipo() const {
    return _tipo;
}

const std::string& Usuario::getRespostaSeguranca() const {
    return _respostaSeguranca;
}

bool Usuario::autenticar(std::string email,
                         std::string senha) const {
    return (_email == email &&
            _senha == senha);
}

std::string Usuario::getPerguntaSeguranca() {
    return "Qual foi a primeira escola que você estudou?";
}

bool Usuario::emailJaCadastrado(
        const std::string& email,
        const std::string& nomeArquivo) {

    std::ifstream arquivo(nomeArquivo);

    std::string linha;

    while (std::getline(arquivo, linha)) {

        std::stringstream ss(linha);

        std::string tipo;
        std::string nome;
        std::string emailArquivo;
        std::string senha;
        std::string cpf;
        std::string resposta;

        std::getline(ss, tipo, ';');
        std::getline(ss, nome, ';');
        std::getline(ss, emailArquivo, ';');
        std::getline(ss, senha, ';');
        std::getline(ss, cpf, ';');
        std::getline(ss, resposta, ';');

        if (emailArquivo == email) {
            return true;
        }
    }

    return false;
}

std::string Usuario::fazerLogin(
        const std::string& email,
        const std::string& senha,
        const std::string& nomeArquivo) {

    std::ifstream arquivo(nomeArquivo);

    std::string linha;

    while (std::getline(arquivo, linha)) {

        std::stringstream ss(linha);

        std::string tipo;
        std::string nome;
        std::string emailArquivo;
        std::string senhaArquivo;
        std::string cpf;
        std::string resposta;

        std::getline(ss, tipo, ';');
        std::getline(ss, nome, ';');
        std::getline(ss, emailArquivo, ';');
        std::getline(ss, senhaArquivo, ';');
        std::getline(ss, cpf, ';');
        std::getline(ss, resposta, ';');

        if (emailArquivo == email &&
            senhaArquivo == senha) {

            return tipo;
        }
    }

    return "invalido";
}

bool Usuario::salvarUsuario(
        const std::string& tipo,
        const std::string& nome,
        const std::string& email,
        const std::string& senha,
        const std::string& cpf,
        const std::string& respostaSeguranca,
        const std::string& nomeArquivo) {

    if (emailJaCadastrado(email,
                          nomeArquivo)) {

        return false;
    }

    std::ofstream arquivo(
        nomeArquivo,
        std::ios::app);

    if (!arquivo.is_open()) {
        return false;
    }

    arquivo << tipo << ";"
            << nome << ";"
            << email << ";"
            << senha << ";"
            << cpf << ";"
            << respostaSeguranca
            << "\n";

    return true;
}

bool Usuario::recuperarSenha(
        const std::string& email,
        const std::string& respostaSeguranca,
        const std::string& novaSenha,
        const std::string& nomeArquivo) {

    if (novaSenha.size() < 6) {
        return false;
    }

    std::ifstream entrada(nomeArquivo);

    if (!entrada.is_open()) {
        return false;
    }

    std::vector<std::string> linhas;

    std::string linha;

    bool encontrou = false;

    while (std::getline(entrada, linha)) {

        std::stringstream ss(linha);

        std::string tipo;
        std::string nome;
        std::string emailArquivo;
        std::string senhaArquivo;
        std::string cpf;
        std::string respostaArquivo;

        std::getline(ss, tipo, ';');
        std::getline(ss, nome, ';');
        std::getline(ss, emailArquivo, ';');
        std::getline(ss, senhaArquivo, ';');
        std::getline(ss, cpf, ';');
        std::getline(ss, respostaArquivo, ';');

        if (emailArquivo == email &&
            respostaArquivo == respostaSeguranca) {

            senhaArquivo = novaSenha;
            encontrou = true;
        }

        linhas.push_back(
            tipo + ";" +
            nome + ";" +
            emailArquivo + ";" +
            senhaArquivo + ";" +
            cpf + ";" +
            respostaArquivo
        );
    }

    entrada.close();

    if (!encontrou) {
        return false;
    }

    std::ofstream saida(nomeArquivo);

    if (!saida.is_open()) {
        return false;
    }

    for (const auto& l : linhas) {
        saida << l << "\n";
    }

    return true;
}