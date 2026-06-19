#include "Usuario.hpp"

#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>

Usuario::Usuario(std::string nome,
                 std::string email,
                 std::string senha,
                 std::string tipo,
                 std::string respostaSeguranca)
    : _nome(nome),
      _email(email),
      _senha(senha),
      _tipo(tipo),
      _respostaSeguranca(respostaSeguranca) {

    if (_nome.empty()) {
        throw std::invalid_argument("Nome invalido.");
    }

    if (_nome.find(';') != std::string::npos) {
        throw std::invalid_argument("Nome nao pode conter ponto e virgula.");
    }

    if (!validarEmail(_email)) {
        throw std::invalid_argument("Email invalido.");
    }

    if (!gerenciarSenha(_senha)) {
        throw std::invalid_argument("Senha invalida.");
    }

    if (_tipo != "cliente" && _tipo != "administrador") {
        throw std::invalid_argument("Tipo de usuario invalido.");
    }

    if (_respostaSeguranca.empty()) {
        throw std::invalid_argument("Resposta de seguranca invalida.");
    }

    if (_respostaSeguranca.find(';') != std::string::npos) {
        throw std::invalid_argument("Resposta de seguranca nao pode conter ponto e virgula.");
    }
}

bool Usuario::validarEmail(std::string novoEmail) const {
    if (novoEmail.empty()) {
        return false;
    }

    if (novoEmail.find(' ') != std::string::npos ||
        novoEmail.find(';') != std::string::npos) {
        return false;
    }

    bool temArroba = false;
    bool temPonto = false;
    size_t posArroba = 0;
    size_t posPonto = 0;

    for (size_t i = 0; i < novoEmail.size(); i++) {
        if (novoEmail[i] == '@') {
            if (temArroba) {
                return false;
            }

            temArroba = true;
            posArroba = i;
        }

        if (novoEmail[i] == '.' && temArroba) {
            temPonto = true;
            posPonto = i;
        }
    }

    if (!temArroba || posArroba == 0 || !temPonto) {
        return false;
    }

    if (posArroba == novoEmail.size() - 1) {
        return false;
    }

    if (posPonto == posArroba + 1) {
        return false;
    }

    return (novoEmail.size() - posPonto) > 2;
}

bool Usuario::gerenciarSenha(std::string novaSenha) const {
    if (novaSenha.size() < 6) {
        return false;
    }

    if (novaSenha.find(';') != std::string::npos) {
        return false;
    }

    return true;
}

void Usuario::armazenarNome(std::string novoNome) {
    if (novoNome.empty()) {
        throw std::invalid_argument("Nome invalido.");
    }

    if (novoNome.find(';') != std::string::npos) {
        throw std::invalid_argument("Nome nao pode conter ponto e virgula.");
    }

    _nome = novoNome;
}

void Usuario::alterarNome(std::string novoNome,
                          const std::string& nomeArquivo) {
    if (novoNome.empty()) {
        throw std::invalid_argument("Nome invalido.");
    }

    if (novoNome.find(';') != std::string::npos) {
        throw std::invalid_argument("Nome nao pode conter ponto e virgula.");
    }

    std::ifstream entrada(nomeArquivo);

    if (!entrada.is_open()) {
        throw std::runtime_error("Erro ao abrir usuarios.txt para leitura.");
    }

    std::vector<std::string> linhas;
    std::string linha;
    bool encontrou = false;

    while (std::getline(entrada, linha)) {
        if (linha.empty()) {
            continue;
        }

        std::stringstream ss(linha);

        std::string tipo;
        std::string nomeArquivoUsuario;
        std::string emailArquivo;
        std::string senhaArquivo;
        std::string cpfArquivo;
        std::string respostaArquivo;

        if (!std::getline(ss, tipo, ';') ||
            !std::getline(ss, nomeArquivoUsuario, ';') ||
            !std::getline(ss, emailArquivo, ';') ||
            !std::getline(ss, senhaArquivo, ';') ||
            !std::getline(ss, cpfArquivo, ';') ||
            !std::getline(ss, respostaArquivo, ';')) {

            throw std::runtime_error("Dados invalidos no arquivo usuarios.txt.");
        }

        if (emailArquivo == _email) {
            nomeArquivoUsuario = novoNome;
            encontrou = true;
        }

        linhas.push_back(
            tipo + ";" +
            nomeArquivoUsuario + ";" +
            emailArquivo + ";" +
            senhaArquivo + ";" +
            cpfArquivo + ";" +
            respostaArquivo
        );
    }

    if (!encontrou) {
        throw std::runtime_error("Usuario nao encontrado no arquivo.");
    }

    std::ofstream saida(nomeArquivo);

    if (!saida.is_open()) {
        throw std::runtime_error("Erro ao abrir usuarios.txt para escrita.");
    }

    for (const std::string& l : linhas) {
        saida << l << "\n";

        if (!saida.good()) {
            throw std::runtime_error("Erro ao escrever dados no arquivo usuarios.txt.");
        }
    }

    _nome = novoNome;
}

void Usuario::alterarEmail(std::string novoEmail,
                           const std::string& nomeArquivo) {
    if (!validarEmail(novoEmail)) {
        throw std::invalid_argument("Email invalido.");
    }

    if (novoEmail == _email) {
        return;
    }

    if (emailJaCadastrado(novoEmail, nomeArquivo)) {
        throw std::runtime_error("Email ja cadastrado.");
    }

    std::ifstream entrada(nomeArquivo);

    if (!entrada.is_open()) {
        throw std::runtime_error("Erro ao abrir usuarios.txt para leitura.");
    }

    std::vector<std::string> linhas;
    std::string linha;
    bool encontrou = false;

    while (std::getline(entrada, linha)) {
        if (linha.empty()) {
            continue;
        }

        std::stringstream ss(linha);

        std::string tipo;
        std::string nomeArquivoUsuario;
        std::string emailArquivo;
        std::string senhaArquivo;
        std::string cpfArquivo;
        std::string respostaArquivo;

        if (!std::getline(ss, tipo, ';') ||
            !std::getline(ss, nomeArquivoUsuario, ';') ||
            !std::getline(ss, emailArquivo, ';') ||
            !std::getline(ss, senhaArquivo, ';') ||
            !std::getline(ss, cpfArquivo, ';') ||
            !std::getline(ss, respostaArquivo, ';')) {

            throw std::runtime_error("Dados invalidos no arquivo usuarios.txt.");
        }

        if (emailArquivo == _email) {
            emailArquivo = novoEmail;
            encontrou = true;
        }

        linhas.push_back(
            tipo + ";" +
            nomeArquivoUsuario + ";" +
            emailArquivo + ";" +
            senhaArquivo + ";" +
            cpfArquivo + ";" +
            respostaArquivo
        );
    }

    if (!encontrou) {
        throw std::runtime_error("Usuario nao encontrado no arquivo.");
    }

    std::ofstream saida(nomeArquivo);

    if (!saida.is_open()) {
        throw std::runtime_error("Erro ao abrir usuarios.txt para escrita.");
    }

    for (const std::string& l : linhas) {
        saida << l << "\n";

        if (!saida.good()) {
            throw std::runtime_error("Erro ao escrever dados no arquivo usuarios.txt.");
        }
    }

    _email = novoEmail;
}

void Usuario::alterarSenha(std::string novaSenha,
                           const std::string& nomeArquivo) {
    if (!gerenciarSenha(novaSenha)) {
        throw std::invalid_argument("Senha invalida.");
    }

    std::ifstream entrada(nomeArquivo);

    if (!entrada.is_open()) {
        throw std::runtime_error("Erro ao abrir usuarios.txt para leitura.");
    }

    std::vector<std::string> linhas;
    std::string linha;
    bool encontrou = false;

    while (std::getline(entrada, linha)) {
        if (linha.empty()) {
            continue;
        }

        std::stringstream ss(linha);

        std::string tipo;
        std::string nomeArquivoUsuario;
        std::string emailArquivo;
        std::string senhaArquivo;
        std::string cpfArquivo;
        std::string respostaArquivo;

        if (!std::getline(ss, tipo, ';') ||
            !std::getline(ss, nomeArquivoUsuario, ';') ||
            !std::getline(ss, emailArquivo, ';') ||
            !std::getline(ss, senhaArquivo, ';') ||
            !std::getline(ss, cpfArquivo, ';') ||
            !std::getline(ss, respostaArquivo, ';')) {

            throw std::runtime_error("Dados invalidos no arquivo usuarios.txt.");
        }

        if (emailArquivo == _email) {
            senhaArquivo = novaSenha;
            encontrou = true;
        }

        linhas.push_back(
            tipo + ";" +
            nomeArquivoUsuario + ";" +
            emailArquivo + ";" +
            senhaArquivo + ";" +
            cpfArquivo + ";" +
            respostaArquivo
        );
    }

    if (!encontrou) {
        throw std::runtime_error("Usuario nao encontrado no arquivo.");
    }

    std::ofstream saida(nomeArquivo);

    if (!saida.is_open()) {
        throw std::runtime_error("Erro ao abrir usuarios.txt para escrita.");
    }

    for (const std::string& l : linhas) {
        saida << l << "\n";

        if (!saida.good()) {
            throw std::runtime_error("Erro ao escrever dados no arquivo usuarios.txt.");
        }
    }

    _senha = novaSenha;
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
    return "Qual foi a primeira escola que voce estudou?";
}

bool Usuario::emailJaCadastrado(
        const std::string& email,
        const std::string& nomeArquivo) {

    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        return false;
    }

    std::string linha;

    while (std::getline(arquivo, linha)) {
        if (linha.empty()) {
            continue;
        }

        std::stringstream ss(linha);

        std::string tipo;
        std::string nome;
        std::string emailArquivo;
        std::string senha;
        std::string cpf;
        std::string resposta;

        if (!std::getline(ss, tipo, ';') ||
            !std::getline(ss, nome, ';') ||
            !std::getline(ss, emailArquivo, ';') ||
            !std::getline(ss, senha, ';') ||
            !std::getline(ss, cpf, ';') ||
            !std::getline(ss, resposta, ';')) {

            throw std::runtime_error("Dados invalidos no arquivo usuarios.txt.");
        }

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

    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro ao abrir usuarios.txt para leitura.");
    }

    std::string linha;

    while (std::getline(arquivo, linha)) {
        if (linha.empty()) {
            continue;
        }

        std::stringstream ss(linha);

        std::string tipo;
        std::string nome;
        std::string emailArquivo;
        std::string senhaArquivo;
        std::string cpf;
        std::string resposta;

        if (!std::getline(ss, tipo, ';') ||
            !std::getline(ss, nome, ';') ||
            !std::getline(ss, emailArquivo, ';') ||
            !std::getline(ss, senhaArquivo, ';') ||
            !std::getline(ss, cpf, ';') ||
            !std::getline(ss, resposta, ';')) {

            throw std::runtime_error("Dados invalidos no arquivo usuarios.txt.");
        }

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

    Usuario usuario(nome, email, senha, tipo, respostaSeguranca);

    if (cpf.empty()) {
        throw std::invalid_argument("CPF invalido.");
    }

    if (cpf.find(';') != std::string::npos) {
        throw std::invalid_argument("CPF nao pode conter ponto e virgula.");
    }

    if (emailJaCadastrado(email, nomeArquivo)) {
        return false;
    }

    std::ofstream arquivo(nomeArquivo, std::ios::app);

    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro ao abrir usuarios.txt para escrita.");
    }

    arquivo << tipo << ";"
            << nome << ";"
            << email << ";"
            << senha << ";"
            << cpf << ";"
            << respostaSeguranca
            << "\n";

    if (!arquivo.good()) {
        throw std::runtime_error("Erro ao escrever dados no arquivo usuarios.txt.");
    }

    return true;
}

bool Usuario::recuperarSenha(
        const std::string& email,
        const std::string& respostaSeguranca,
        const std::string& novaSenha,
        const std::string& nomeArquivo) {

    if (email.empty()) {
        throw std::invalid_argument("Email invalido.");
    }

    if (respostaSeguranca.empty()) {
        throw std::invalid_argument("Resposta de seguranca invalida.");
    }

    if (novaSenha.size() < 6) {
        throw std::invalid_argument("Nova senha invalida.");
    }

    std::ifstream entrada(nomeArquivo);

    if (!entrada.is_open()) {
        throw std::runtime_error("Erro ao abrir usuarios.txt para leitura.");
    }

    std::vector<std::string> linhas;
    std::string linha;

    bool encontrouEmail = false;
    bool respostaCorreta = false;

    while (std::getline(entrada, linha)) {
        if (linha.empty()) {
            continue;
        }

        std::stringstream ss(linha);

        std::string tipo;
        std::string nome;
        std::string emailArquivo;
        std::string senhaArquivo;
        std::string cpf;
        std::string respostaArquivo;

        if (!std::getline(ss, tipo, ';') ||
            !std::getline(ss, nome, ';') ||
            !std::getline(ss, emailArquivo, ';') ||
            !std::getline(ss, senhaArquivo, ';') ||
            !std::getline(ss, cpf, ';') ||
            !std::getline(ss, respostaArquivo, ';')) {

            throw std::runtime_error("Dados invalidos no arquivo usuarios.txt.");
        }

        if (emailArquivo == email) {
            encontrouEmail = true;

            if (respostaArquivo == respostaSeguranca) {
                senhaArquivo = novaSenha;
                respostaCorreta = true;
            }
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

    if (!encontrouEmail) {
        return false;
    }

    if (!respostaCorreta) {
        return false;
    }

    std::ofstream saida(nomeArquivo);

    if (!saida.is_open()) {
        throw std::runtime_error("Erro ao abrir usuarios.txt para escrita.");
    }

    for (const std::string& l : linhas) {
        saida << l << "\n";

        if (!saida.good()) {
            throw std::runtime_error("Erro ao escrever dados no arquivo usuarios.txt.");
        }
    }

    return true;
}