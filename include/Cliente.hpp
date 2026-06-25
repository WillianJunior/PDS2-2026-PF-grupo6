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
 */
class Cliente : public Usuario {
private:
    std::string         _cpf;
    std::string         _endereco;
    std::vector<Cartao> _cartoesSalvos;

    // Metodo interno para puxar do cartoes.txt
    void carregarCartoes(const std::string& arquivo = "cartoes.txt");

public:
    Cliente(const std::string& nome,
            const std::string& email,
            const std::string& senha,
            const std::string& cpf,
            const std::string& respostaSeguranca);

    ~Cliente() override = default;
    void exibirPerfil() const override;

    bool validarCpf() const;
    bool validarCartao(const std::string& numeroCartao) const;

    bool salvarCartao(const std::string& novoCartao, TipoCartao tipo, const std::string& arquivo = "cartoes.txt");
    bool removerCartao(const std::string& numeroCartao, const std::string& arquivo = "cartoes.txt");

    void adicionarEndereco(const std::string& novoEndereco);
    void alterarEndereco(std::string novoEndereco, const std::string& nomeArquivo = "usuarios.txt");
    bool cadastrarCliente(const std::string& nomeArquivo) const;

    const std::string&         getCpf()           const;
    const std::string&         getEndereco()      const;
    const std::vector<Cartao>& getCartoesSalvos() const;
};

#endif
