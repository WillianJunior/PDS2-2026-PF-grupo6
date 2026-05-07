#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include "Usuario.hpp" // Obrigatório usar include aqui por causa da herança (extends)
#include <string>
#include <vector>

/**
 * @brief Representa um consumidor na loja.
 * Gerencia dados sensíveis de faturamento, como CPF e múltiplos endereços.
 */
class Cliente : public Usuario {
private:
    std::string _cpf;
    std::vector<std::string> _enderecos;
    std::vector<std::string> _metodosPagamento;

public:
    Cliente(std::string nome, std::string email, std::string senha, std::string cpf);

    /**
     * @brief Valida as condições matemáticas do CPF fornecido.
     * @return true se o CPF for válido para compras.
     */
    bool validarCpf() const;

    void adicionarEndereco(std::string novoEndereco);
    void adicionarMetodoPagamento(std::string novoMetodo);
};

#endif // CLIENTE_HPP
