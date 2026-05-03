#ifndef ADMINISTRADOR_HPP
#define ADMINISTRADOR_HPP

#include "usuario.hpp"
#include <string>

class catalogo;
class estoque;
class produto;

/**
 * @brief Possui permissões para gerenciar o funcionamento da loja.
 */

class administrador : public usuario {

public:

    administrador(std::string nome, std::string email, std::string senha);
    
/**
 * @brief Gerenciar o cadastramento ou remoção de itens do catálogo.
 */
    void gerenciarCatalogo();

/**
 * @brief Gerenciar a quantidade de itens do estoque.
 */
    void gerenciarEstoque();

/**
 * @brief Visualizar informações do usuário.
 */    
    void gerenciarContas();

/**
 * @brief Gerenciar o fluxo de vendas e atualizar os dados de envio.
 */
    void atualizarVendas();

};

#endif