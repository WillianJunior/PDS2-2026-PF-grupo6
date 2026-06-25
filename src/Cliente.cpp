#include "Cliente.hpp"

#include <algorithm>
#include <cctype>
#include <iostream> 
#include <stdexcept>

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
        throw std::invalid_argument("CPF matematicamente invalido.");
    }
}

/* // TODO para amanhã: Descomentar este bloco para ativar o Polimorfismo Dinâmico
void Cliente::exibirPerfil() const {
    Usuario::exibirPerfil(); // Chama a impressão da classe mãe (Nome e Email)
    std::cout << "CPF: " << _cpf << " | Endereco: " 
              << (_endereco.empty() ? "Nao cadastrado" : _endereco) << "\n";
}
*/

bool Cliente::validarCpf() const {
    std::string cpfLimpo;

    for (char c : _cpf) {
        if (std::isdigit(c)) {
            cpfLimpo += c;
        }
    }

    if (cpfLimpo.size() != 11) {
        return false;
    }

    bool todosIguais = true;
    for (size_t i = 1; i < 11; ++i) {
        if (cpfLimpo[i] != cpfLimpo[0]) {
            todosIguais = false;
            break;
        }
    }

    if (todosIguais) {
        return false;
    }

    int soma = 0;
    for (int i = 0; i < 9; ++i) {
        soma += (cpfLimpo[i] - '0') * (10 - i);
    }

    int resto = (soma * 10) % 11;
    if (resto == 10 || resto == 11) {
        resto = 0;
    }

    if (resto != (cpfLimpo[9] - '0')) {
        return false;
    }

    soma = 0;
    for (int i = 0; i < 10; ++i) {
        soma += (cpfLimpo[i] - '0') * (11 - i);
    }

    resto = (soma * 10) % 11;
    if (resto == 10 || resto == 11) {
        resto = 0;
    }

    return resto == (cpfLimpo[10] - '0');
}

bool Cliente::validarCartao(const std::string& numeroCartao) const {
    std::string numeroLimpo;

    for (char c : numeroCartao) {
        if (std::isdigit(c)) {
            numeroLimpo += c;
        }
    }

    if (numeroLimpo.size() < 13 || numeroLimpo.size() > 19) {
        return false;
    }

    int soma = 0;
    bool deveMultiplicar = false;

    for (int i = numeroLimpo.size() - 1; i >= 0; --i) {
        int digito = numeroLimpo[i] - '0';

        if (deveMultiplicar) {
            digito *= 2;
            if (digito > 9) {
                digito -= 9;
            }
        }

        soma += digito;
        deveMultiplicar = !deveMultiplicar;
    }

    return (soma % 10 == 0);
}

bool Cliente::salvarCartao(const std::string& novoCartao, TipoCartao tipo) {
    if (novoCartao.empty()) {
        throw std::invalid_argument("Numero de cartao nao pode ser vazio.");
    }

    if (!validarCartao(novoCartao)) {
        return false;
    }

    std::string numeroLimpo;
    for (char c : novoCartao) {
        if (std::isdigit(c)) {
            numeroLimpo += c;
        }
    }

    bool jaExiste = std::any_of(
        _cartoesSalvos.begin(),
        _cartoesSalvos.end(),
        [&numeroLimpo](const Cartao& c) {
            return c.numero == numeroLimpo;
        });

    if (jaExiste) {
        return false;
    }

    Cartao cartaoParaSalvar;
    cartaoParaSalvar.numero = numeroLimpo;
    cartaoParaSalvar.tipo   = tipo;

    _cartoesSalvos.push_back(cartaoParaSalvar);

    return true;
}

void Cliente::adicionarEndereco(const std::string& novoEndereco) {
    if (novoEndereco.empty()) {
        throw std::invalid_argument("Endereco nao pode ser vazio.");
    }

    if (novoEndereco.find(';') != std::string::npos) {
        throw std::invalid_argument("Endereco nao pode conter ponto e virgula.");
    }

    _endereco = novoEndereco;
}

bool Cliente::cadastrarCliente(const std::string& nomeArquivo) const {
    if (!validarCpf()) {
        throw std::invalid_argument("CPF invalido para cadastro.");
    }

    return Usuario::salvarUsuario(
        "cliente",
        _nome,
        _email,
        _senha,
        _cpf,
        _respostaSeguranca,
        nomeArquivo
    );
}

// ── Getters ──────────────────────────────────────────

const std::string& Cliente::getCpf() const {
    return _cpf;
}

const std::string& Cliente::getEndereco() const {
    return _endereco;
}

const std::vector<Cartao>& Cliente::getCartoesSalvos() const {
    return _cartoesSalvos;
}