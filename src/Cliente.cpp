#include "Cliente.hpp"
#include <iostream>
#include <cctype>
#include <algorithm>

Cliente::Cliente(const std::string& nome,
                 const std::string& email,
                 const std::string& senha,
                 const std::string& cpf,
                 const std::string& respostaSeguranca)
    : Usuario(nome, email, senha, "cliente", respostaSeguranca),
      _cpf(cpf),
      _endereco("") {}

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

    // Cartões de crédito/débito reais têm geralmente entre 13 e 19 dígitos
    if (numeroLimpo.size() < 13 || numeroLimpo.size() > 19) {
        return false;
    }

    // Implementação do Algoritmo de Luhn
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


void Cliente::salvarCartao(const std::string& novoCartao, TipoCartao tipo) {
    if (!validarCartao(novoCartao)) {
        std::cout << "Erro: Numero de cartao invalido!\n";
        return;
    }

   
    std::string numeroLimpo;
    for (char c : novoCartao) {
        if (std::isdigit(c)) numeroLimpo += c;
    }


    bool jaExiste = std::any_of(_cartoesSalvos.begin(), _cartoesSalvos.end(), 
        [&numeroLimpo](const Cartao& c) {
            return c.numero == numeroLimpo;
        });

    if (jaExiste) {
        std::cout << "Erro: Este cartao ja esta cadastrado!\n";
        return;
    }

    Cartao cartaoParaSalvar;
    cartaoParaSalvar.numero = numeroLimpo;
    cartaoParaSalvar.tipo = tipo;

    _cartoesSalvos.push_back(cartaoParaSalvar);
    std::cout << "Cartao validado e salvo com sucesso como " 
              << (tipo == TipoCartao::CREDITO ? "Credito" : "Debito") << "!\n";
}

const std::vector<Cartao>& Cliente::getCartoesSalvos() const {
    return _cartoesSalvos;
}

void Cliente::adicionarEndereco(const std::string& novoEndereco) {
     if (!_endereco.empty()) {
        std::cout << "Alterando endereco antigo para o novo...\n";
    }
    _endereco = novoEndereco;
    std::cout << "Endereco atualizado com sucesso!\n";
}


bool Cliente::cadastrarCliente(const std::string& nomeArquivo) const {
    if (!validarEmail(_email)) {
        return false;
    }

    if (!gerenciarSenha(_senha)) {
        return false;
    }

    if (!validarCpf()) {
        return false;
    }

    if (_respostaSeguranca.empty()) {
        return false;
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

const std::string& Cliente::getCpf() const {
    return _cpf;
}

const std::string& Cliente::getEndereco() const {
    return _endereco;
}
