#ifndef ADMINISTRADOR_HPP
#define ADMINISTRADOR_HPP

#include "Usuario.hpp" // Obrigatório por causa da herança
#include <string>

class Catalogo;
class Estoque;
class Cliente;
class Pedido;

/**
 * @brief Possui permissões elevadas para gerenciar o funcionamento da loja.
 * Pode adicionar produtos, conferir estoque e atualizar status de envios.
 */
class Administrador : public Usuario {
public:
    Administrador(std::string nome, std::string email, std::string senha);

    /**
     * @brief Cadastra ou remove itens da vitrine da loja.
     * @param catalogo Referência direta ao catálogo ativo no sistema.
     */
    void gerenciarCatalogo(Catalogo& catalogo);

    /**
     * @brief Modifica quantidades de itens no armazém.
     * @param estoque Referência direta ao controle de inventário.
     */
    void gerenciarEstoque(Estoque& estoque);

    void gerenciarContas(Cliente& cliente);
    void atualizarVendas(Pedido& pedido);
};

#endif // ADMINISTRADOR_HPP