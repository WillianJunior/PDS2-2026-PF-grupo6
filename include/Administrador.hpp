#ifndef ADMINISTRADOR_HPP
#define ADMINISTRADOR_HPP

#include "Usuario.hpp"
#include <string>

class Cliente;
class Pedido;

/**
 * @brief Usuário com permissões administrativas.
 */
class Administrador : public Usuario {
public:
    Administrador(const std::string& nome,
                  const std::string& email,
                  const std::string& senha,
                  const std::string& respostaSeguranca);

     ~Administrador() override = default;

    /**
     * @brief Implementação do polimorfismo exigido.
     * Sobrescreve o método da classe base para exibir o perfil administrativo.
     */
     void exibirPerfil() const override;

    /**
     * @brief Gera o relatório textual com os dados cadastrais do cliente.
     */
    std::string gerenciarContas(const Cliente& cliente) const;

    /**
     * @brief Gera o relatório detalhado das informações financeiras da venda.
     */
    std::string atualizarVendas(const Pedido& pedido) const;

    /**
     * @brief Cadastra o administrador no sistema.
     * @throws std::invalid_argument Se os dados internos estiverem corrompidos.
     * @throws std::runtime_error Se houver falha de escrita física no banco de dados.
     */
    bool cadastrarAdministrador(const std::string& nomeArquivo = "usuarios.txt") const;
};

#endif