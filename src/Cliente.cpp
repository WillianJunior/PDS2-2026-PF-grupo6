#include "Cliente.hpp"

#include <algorithm>
#include <cctype>
#include <iostream> 
#include <stdexcept>
#include <fstream>
#include <sstream>

// ── Construtor ───────────────────────────────────────

Cliente::Cliente(const std::string& nome,
                 const std::string& email,
                 const std::string& senha,
                 const std::string& cpf,
                 const std::string& respostaSeguranca)
    : Usuario(nome, email, senha, "cliente", respostaSeguranca),
      _cpf(cpf),
      _endereco("") {

    if (_cpf.empty()) {
        throw std::invalid_argument("CPF nao pode ser vazio.");
    }

    if (_cpf.find(';') != std::string::npos) {
        throw std::invalid_argument("CPF nao pode conter ponto e virgula.");
    }

    if (!validarCpf()) {
        throw std::invalid_argument("CPF invalido! Verifique se voce digitou exatamente 11 numeros verdadeiros (sem pontos ou tracos).");
    }

    carregarCartoes();
}

void Cliente::exibirPerfil() const {
    Usuario::exibirPerfil(); 
    std::cout << "CPF: " << _cpf << " | Endereco: " 
              << (_endereco.empty() ? "Nao cadastrado" : _endereco) << "\n";
}

bool Cliente::validarCpf() const {
    std::string cpfLimpo;
    for (char c : _cpf) { if (std::isdigit(c)) { cpfLimpo += c; } }
    if (cpfLimpo.size() != 11) { return false; }
    bool todosIguais = true;
    for (size_t i = 1; i < 11; ++i) {
        if (cpfLimpo[i] != cpfLimpo[0]) { todosIguais = false; break; }
    }
    if (todosIguais) { return false; }
    int soma = 0;
    for (int i = 0; i < 9; ++i) { soma += (cpfLimpo[i] - '0') * (10 - i); }
    int resto = (soma * 10) % 11;
    if (resto == 10 || resto == 11) { resto = 0; }
    if (resto != (cpfLimpo[9] - '0')) { return false; }
    soma = 0;
    for (int i = 0; i < 10; ++i) { soma += (cpfLimpo[i] - '0') * (11 - i); }
    resto = (soma * 10) % 11;
    if (resto == 10 || resto == 11) { resto = 0; }
    return resto == (cpfLimpo[10] - '0');
}

bool Cliente::validarCartao(const std::string& numeroCartao) const {
    std::string numeroLimpo;
    for (char c : numeroCartao) { if (std::isdigit(c)) { numeroLimpo += c; } }
    if (numeroLimpo.size() < 13 || numeroLimpo.size() > 19) { return false; }
    int soma = 0;
    bool deveMultiplicar = false;
    for (int i = numeroLimpo.size() - 1; i >= 0; --i) {
        int digito = numeroLimpo[i] - '0';
        if (deveMultiplicar) {
            digito *= 2;
            if (digito > 9) { digito -= 9; }
        }
        soma += digito;
        deveMultiplicar = !deveMultiplicar;
    }
    return (soma % 10 == 0);
}

// ── Lógica de Cartões (Carteira Virtual) ───────────────

void Cliente::carregarCartoes(const std::string& arquivo) {
    _cartoesSalvos.clear();
    std::ifstream in(arquivo);
    if (!in.is_open()) return;

    std::string linha;
    while (std::getline(in, linha)) {
        if (linha.empty()) continue;
        std::stringstream ss(linha);
        std::string emailArq, numArq, tipoStr;
        
        std::getline(ss, emailArq, ';');
        std::getline(ss, numArq, ';');
        std::getline(ss, tipoStr);

        if (emailArq == getEmail()) {
            TipoCartao t = (tipoStr == "0") ? TipoCartao::CREDITO : TipoCartao::DEBITO;
            _cartoesSalvos.push_back({numArq, t});
        }
    }
}

bool Cliente::salvarCartao(const std::string& novoCartao, TipoCartao tipo, const std::string& arquivo) {
    if (novoCartao.empty()) { throw std::invalid_argument("Numero de cartao nao pode ser vazio."); }
    if (!validarCartao(novoCartao)) { return false; }

    std::string numeroLimpo;
    for (char c : novoCartao) { if (std::isdigit(c)) { numeroLimpo += c; } }

    bool jaExiste = std::any_of(_cartoesSalvos.begin(), _cartoesSalvos.end(), [&numeroLimpo](const Cartao& c) {
        return c.numero == numeroLimpo;
    });

    if (jaExiste) { return false; }

    _cartoesSalvos.push_back({numeroLimpo, tipo});

    // Salva no cartoes.txt
    std::ofstream out(arquivo, std::ios::app);
    if (out.is_open()) {
        out << getEmail() << ";" << numeroLimpo << ";" << (tipo == TipoCartao::CREDITO ? "0" : "1") << "\n";
    }

    return true;
}

bool Cliente::removerCartao(const std::string& numeroCartao, const std::string& arquivo) {
    auto it = std::remove_if(_cartoesSalvos.begin(), _cartoesSalvos.end(), [&](const Cartao& c) {
        return c.numero == numeroCartao;
    });

    if (it == _cartoesSalvos.end()) { return false; } // Cartao nao encontrado
    _cartoesSalvos.erase(it, _cartoesSalvos.end());

    // Reescreve o txt sem o cartao removido
    std::ifstream in(arquivo);
    std::vector<std::string> linhas;
    if (in.is_open()) {
        std::string linha;
        while (std::getline(in, linha)) {
            if (linha.empty()) continue;
            std::stringstream ss(linha);
            std::string emailArq, numArq;
            std::getline(ss, emailArq, ';');
            std::getline(ss, numArq, ';');
            
            if (emailArq == getEmail() && numArq == numeroCartao) continue;
            
            linhas.push_back(linha);
        }
        in.close();
    }

    std::ofstream out(arquivo);
    if (out.is_open()) {
        for (const auto& l : linhas) { out << l << "\n"; }
    }

    return true;
}

// ── Outros Metodos ───────────────────────────────────

void Cliente::adicionarEndereco(const std::string& novoEndereco) {
    if (novoEndereco.empty() || novoEndereco.find(';') != std::string::npos) {
        throw std::invalid_argument("Endereco invalido ou contem ponto e virgula.");
    }
    _endereco = novoEndereco;
}

void Cliente::alterarEndereco(std::string novoEndereco, const std::string& nomeArquivo) {
    if (novoEndereco.empty() || novoEndereco.find(';') != std::string::npos) {
        throw std::invalid_argument("Endereco invalido ou contem ponto e virgula.");
    }

    std::ifstream entrada(nomeArquivo);
    if (!entrada.is_open()) { throw std::runtime_error("Erro ao abrir usuarios.txt para leitura."); }

    std::vector<std::string> linhas;
    std::string linha;
    bool encontrou = false;

    while (std::getline(entrada, linha)) {
        if (linha.empty()) { continue; }
        std::stringstream ss(linha);
        std::string tipo, nomeArq, emailArq, senhaArq, cpfArq, respArq, endArq;

        if (!std::getline(ss, tipo, ';') || !std::getline(ss, nomeArq, ';') ||
            !std::getline(ss, emailArq, ';') || !std::getline(ss, senhaArq, ';') ||
            !std::getline(ss, cpfArq, ';') || !std::getline(ss, respArq, ';')) {
            throw std::runtime_error("Dados invalidos no arquivo usuarios.txt.");
        }
        std::getline(ss, endArq);

        if (emailArq == getEmail()) {
            endArq = novoEndereco;
            encontrou = true;
        }

        linhas.push_back(tipo + ";" + nomeArq + ";" + emailArq + ";" + senhaArq + ";" + cpfArq + ";" + respArq + ";" + endArq);
    }
    entrada.close();

    if (!encontrou) { throw std::runtime_error("Usuario nao encontrado no arquivo."); }

    std::ofstream saida(nomeArquivo);
    if (!saida.is_open()) { throw std::runtime_error("Erro ao abrir usuarios.txt para escrita."); }
    for (const std::string& l : linhas) { saida << l << "\n"; }
    _endereco = novoEndereco;
}

bool Cliente::cadastrarCliente(const std::string& nomeArquivo) const {
    if (!validarCpf()) { throw std::invalid_argument("CPF invalido para cadastro."); }
    return Usuario::salvarUsuario("cliente", _nome, _email, _senha, _cpf, _respostaSeguranca, _endereco, nomeArquivo);
}

const std::string& Cliente::getCpf() const { return _cpf; }
const std::string& Cliente::getEndereco() const { return _endereco; }
const std::vector<Cartao>& Cliente::getCartoesSalvos() const { return _cartoesSalvos; }
