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
 * O construtor delega validações ao construtor de Usuario.
 */
class Cliente : public Usuario {
private:
    std::string         _cpf;
    std::string         _endereco;
    std::vector<Cartao> _cartoesSalvos;

public:
    /**
     * @brief Constrói um Cliente validando todos os dados via Usuario.
     * @throw std::invalid_argument se algum dado for inválido.
     */
    Cliente(const std::string& nome,
            const std::string& email,
            const std::string& senha,
            const std::string& cpf,
            const std::string& respostaSeguranca);

    /**
     * @brief Valida os dígitos verificadores do CPF.
     * @return true se o CPF for matematicamente válido.
     */
    bool validarCpf() const;

    /**
     * @brief Valida o número do cartão pelo algoritmo de Luhn.
     * @param numeroCartao Número do cartão (pode conter traços/espaços).
     * @return true se passar na validação.
     */
    bool validarCartao(const std::string& numeroCartao) const;

    /**
     * @brief Tenta salvar um cartão na lista do cliente.
     * @param novoCartao Número do cartão.
     * @param tipo Tipo do cartão.
     * @return true se salvo; false se inválido no Luhn ou duplicado.
     * @throw std::invalid_argument se o número for vazio.
     */
    bool salvarCartao(const std::string& novoCartao,
                      TipoCartao tipo);

    /**
     * @brief Atualiza o endereço de entrega.
     * @throw std::invalid_argument se o endereço for vazio
     *        ou contiver ponto e vírgula.
     */
    void adicionarEndereco(const std::string& novoEndereco);

    /**
     * @brief Salva o cliente no arquivo se todos os dados forem válidos.
     * @param nomeArquivo Arquivo destino.
     * @return true se salvo; false se email já cadastrado.
     * @throw std::invalid_argument se CPF ou resposta inválidos.
     * @throw std::runtime_error se ocorrer erro de arquivo.
     */
    bool cadastrarCliente(const std::string& nomeArquivo) const;

    const std::string&         getCpf()           const;
    const std::string&         getEndereco()      const;
    const std::vector<Cartao>& getCartoesSalvos() const;
};

#endif