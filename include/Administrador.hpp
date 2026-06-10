#ifndef ADMINISTRADOR_HPP
#define ADMINISTRADOR_HPP

#include "Usuario.hpp"
#include <string>

class Catalogo;
class Estoque;
class Cliente;
class Pedido;

/**
 * @brief Usuário com permissões administrativas.
 */
class Administrador : public Usuario {
public:
    Administrador(std::string nome,
                  std::string email,
                  std::string senha,
                  std::string respostaSeguranca);

    /**
     * @brief Gerencia catálogo de produtos.
     */
    void gerenciarCatalogo(Catalogo& catalogo);

    /**
     * @brief Gerencia estoque.
     */
    void gerenciarEstoque(Estoque& estoque);

    /**
     * @brief Gerencia contas de clientes.
     */
    void gerenciarContas(Cliente& cliente);

    /**
     * @brief Atualiza informações de vendas.
     */
    void atualizarVendas(Pedido& pedido);

    /**
     * @brief Cadastra administrador no usuarios.txt.
     */
    bool cadastrarAdministrador(
        const std::string& nomeArquivo = "usuarios.txt") const;
};

#endif
