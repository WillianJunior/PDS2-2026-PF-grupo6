#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include "Usuario.hpp"
#include <string>
#include <vector>

/**
 * @brief Opções válidas para transações financeiras.
 * O enum evita erros de digitação e substitui o uso de strings.
 */
enum FormaPagamento {
    PIX,
    CARTAO_CREDITO,
    BOLETO
};

/**
 * @brief Representa um consumidor na loja.
 * Gerencia dados sensíveis de faturamento, como CPF e múltiplos endereços.
 */
class Cliente : public Usuario {
private:
    std::string _cpf;
    std::vector<std::string> _enderecos;
    
    std::vector<FormaPagamento> _metodosPagamento;

public:

    Cliente(const std::string& nome, const std::string& email, const std::string& senha, const std::string& cpf);

    /**
     * @brief Valida as condições matemáticas do CPF fornecido.
     * @return true se o CPF for válido para compras.
     */
    bool validarCpf() const;

    void adicionarEndereco(const std::string& novoEndereco);
    
    void adicionarMetodoPagamento(FormaPagamento novoMetodo);
};

#endif // CLIENTE_HPP