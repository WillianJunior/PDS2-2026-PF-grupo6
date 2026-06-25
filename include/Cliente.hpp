#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include "Usuario.hpp"
#include <string>
#include <vector>

/**
 * @enum TipoCartao
 * @brief Define os tipos de cartão de pagamento aceitos.
 */
enum class TipoCartao {
    CREDITO,
    DEBITO
};

/**
 * @brief Agrupa número e tipo de um cartão bancário.
 */
struct Cartao {
    std::string numero;
    TipoCartao  tipo;
};

/**
 * @class Cliente
 * @brief Usuário com permissão de compra no sistema.
 *
 * Herda de Usuario e adiciona CPF, endereço e cartões.
 */
class Cliente : public Usuario {
private:
    std::string         _cpf;
    std::string         _endereco;
    std::vector<Cartao> _cartoesSalvos;

public:
    /**
     * @brief Constrói um Cliente e garante que ele só exista em estado válido.
     */
    Cliente(const std::string& nome,
            const std::string& email,
            const std::string& senha,
            const std::string& cpf,
            const std::string& respostaSeguranca);

    // TODO para amanhã: Descomentar quando a Djulia atualizar a classe Usuario
    // ~Cliente() override = default;

    /**
     * @brief Implementação do polimorfismo exigido pelo professor.
     */
    // TODO para amanhã: Descomentar para ativar o polimorfismo
    // void exibirPerfil() const override;

    /**
     * @brief Valida os dígitos verificadores do CPF.
     */
    bool validarCpf() const;

    /**
     * @brief Valida o número do cartão pelo algoritmo de Luhn.
     */
    bool validarCartao(const std::string& numeroCartao) const;

    /**
     * @brief Tenta salvar um cartão na lista do cliente.
     */
    bool salvarCartao(const std::string& novoCartao, TipoCartao tipo);

    /**
     * @brief Atualiza o endereço de entrega.
     */
    void adicionarEndereco(const std::string& novoEndereco);

    /**
     * @brief Salva o cliente no arquivo.
     */
    bool cadastrarCliente(const std::string& nomeArquivo) const;

    const std::string&         getCpf()           const;
    const std::string&         getEndereco()      const;
    const std::vector<Cartao>& getCartoesSalvos() const;
};

#endif