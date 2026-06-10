#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include "Usuario.hpp"
#include <string>
#include <vector>
/**
 * @enum TipoCartao
 * @brief Define de forma estrita os tipos de cartões de pagamento aceitos.
 */
enum class TipoCartao {
    CREDITO,
    DEBITO
};

/**
 * @brief Estrutura que une as informações de um cartão bancário.
 */
struct Cartao {
    std::string numero;
    TipoCartao tipo;
};

/**
 * @class Cliente
 * @brief Representa um cliente no sistema, herdando características de Usuario.
 */
class Cliente : public Usuario {
private:
    std::string _cpf;
    std::string _endereco;
    std::vector<Cartao> _cartoesSalvos; // Agora armazena a Struct, não apenas string

public:
    Cliente(const std::string& nome, const std::string& email, const std::string& senha,
            const std::string& cpf, const std::string& respostaSeguranca);
    /**
     * @brief Valida se o formato e os dígitos do CPF são verdadeiros.
     * * @note O 'const' no fim garante que esta função apenas lê dados, sem modificar nenhum atributo do objeto Cliente.
     * @return true Se o CPF for válido.
     * @return false Se o CPF for inválido.
     */
    bool validarCpf() const;
    /**
     * @brief Valida o número de um cartão.
     * @note 'const std::string&' evita copiar o texto do número. O 'const' no fim garante que o método não altera o objeto Cliente.
     * @param numeroCartao String com o número do cartão a ser validado.
     * @return true Se o cartão for válido.
     */
    bool validarCartao(const std::string& numeroCartao) const;
    
    /**
     * @brief Adiciona um novo cartão à lista de cartões salvos do cliente.
     * @note 'const std::string&' garante acesso seguro e rápido ao número do cartão sem duplicar a string na memória.
     * @param novoCartao Número do cartão.
     * @param tipo Tipo do cartão (CREDITO ou DEBITO).
     */
    void salvarCartao(const std::string& novoCartao, TipoCartao tipo); 
     /**
     * @brief Atualiza ou adiciona o endereço de entrega do cliente.
     * @note 'const std::string&' recebe o endereço por referência para economizar memória, protegendo o texto contra alterações.
     * @param novoEndereco String contendo o novo endereço.
     */
    void adicionarEndereco(const std::string& novoEndereco);
     /**
     * @brief Registra e persiste os dados do cliente em um arquivo de banco de dados.
     * @note 'const std::string&' evita cópia do nome do arquivo. O 'const' final assegura que a gravação não modifica o Cliente atual.
     * @param nomeArquivo Caminho ou nome do arquivo destino.
     * @return true Se o cadastro foi salvo com sucesso.
     */
    bool cadastrarCliente(const std::string& nomeArquivo) const;

    const std::string& getCpf() const;
    const std::string& getEndereco() const;
    const std::vector<Cartao>& getCartoesSalvos() const;

};

#endif
