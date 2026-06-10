#ifndef ESTOQUE_HPP
#define ESTOQUE_HPP

#include "Produto.hpp"
#include <string>
#include <vector>

/**
 * @brief Classe gestora do inventário físico da loja.
 * Controla a disponibilidade imediata dos produtos e garante a integridade
 * entre o que é exibido no catálogo e o que realmente existe no armazém.
 */
class Estoque {
private:
    std::vector<Produto> _inventario;

public:
    /**
     * @brief Carrega os dados iniciais do inventário.
     * Prepara a lista em memória antes das operações de venda começarem,
     * permitindo consultas rápidas sem acessar o disco a todo momento.
     */
    Estoque();

    /**
     * @brief Retorna o balanço total de itens no armazém como texto.
     * A exibição fica a cargo da classe de interface.
     */
    std::string exibirQuantidadeDisponiveis() const;

    /**
     * @brief Retorna alertas de produtos com baixo volume de unidades.
     * A exibição fica a cargo da classe de interface.
     */
    std::string alertarEstoqueCritico() const;

    /**
     * @brief Reserva temporariamente itens para um pedido em andamento.
     * Garante que o produto não seja vendido para outro cliente enquanto 
     * o pagamento está sendo processado. 
     * @param idProduto Identificador único do item a ser reservado.
     * @param quantidade Número de unidades que devem ser "congeladas".
     */
    void congelarQuantidades(int idProduto, int quantidade);

    /**
     * @brief Consolida a saída definitiva de um produto após o pagamento.
     * Atualiza o estado interno do objeto para que a nova quantidade 
     * seja gravada posteriormente no arquivo .txt.
     * @param idProduto Identificador do item vendido.
     * @param quantidade Quantidade exata a ser debitada do estoque.
     */
    void efetuarSubtracao(int idProduto, int quantidade);

    /**
     * @brief Bloqueia tentativas de compra que excedam o estoque real.
     * @param idProduto Identificador do produto alvo.
     * @param quantidadeDesejada Volume que o cliente tenta adicionar ao carrinho.
     * @return true se a operação é segura e permitida pelo estoque atual.
     */
    bool impedirVendasAcimaMaximo(int idProduto, int quantidadeDesejada) const;
};

#endif // ESTOQUE_HPP