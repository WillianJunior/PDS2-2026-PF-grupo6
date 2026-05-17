#ifndef CARRINHO_HPP
#define CARRINHO_HPP
#include "Produto.hpp"
#include "Cliente.hpp"
#include <vector>

/** * @class Carrinho 
 * @brief Representa o carrinho ativo de um cliente durante a navegação do e - commerce.
 */

class Carrinho {
    private:
    std::vector<Produto> _produtos; 
    std::vector<int> _quantidades; 
    Cliente& _cliente; 
    double _valorFrete; 
    
    public:
    /** * @brief Cria um carrinho associado a um cliente específico.
     */
    Carrinho(Cliente& cliente);

    /**
     * @brief Busca o índice de um produto no carrinho com base no ID do produto.
     * Esse metodo é utilizado para evitar a duplicação de produtos no carrinho;
     * Todas as operações de modificação dependem dessa busca.
     */
    int buscarIdProduto(int idProduto) const;

    /** * @brief Adiciona um produto ao carrinho ou incrementa a sua quantidade.
     * @param produto produto a ser adicionado.
     * @param quantidade Quantidade do produto a ser adicionada.
     */
    void adicionarProduto(const Produto& produto, int quantidade);

    /** * @brief Remove um produto do carrinho.
     * @param idProduto ID do produto a ser removido.
     */
    void removerProduto(int idProduto);

    /**
     * @brief Atualiza a quantidade de um produto no carrinho.
     * @param idProduto ID do produto a ser atualizado.
     * @param novaQuantidade Nova quantidade do produto.
     */
    void atualizarQuantidade(int idProduto, int novaQuantidade);

    /**
     * @brief Verifica se há disponibilidade de estoque para todos os produtos no carrinho.
     * @param produto O produto a ser verificado.
     * @param quantidade Quantidade do produto a ser verificada.
     * @return Retorna true se todos os produtos estiverem disponíveis, false caso contrário.
     */
    bool validarEstoque(const Produto& produto, int quantidade) const;
    
    /** * @brief Esvazia o carrinho, removendo todos os produtos e resetando o valor total da compra.
     */
    void limparCarrinho();
    
    /** * @brief Calcula o subtotal dos produtos do carrinho.
     * @return Retorna o valor do subtotal dos produtos no carrinho.
     */
    double calcularSubtotal() const;

    /** * @brief Calcula o valor total da compra, incluindo o subtotal dos produtos e o valor do frete.
     * @return Retorna o valor total da compra.
     */
    double calcularTotal() const;

    /** * @brief Calcula o valor do frete com base na localização do cliente.
     * @return Retorna o valor do frete para a compra.
     */
    double calcularValorFrete() const;

    /** * @brief Obtém o valor do frete para a compra.
     */
    double getValorFrete() const;
      
    /** * @brief Fornece acesso, somente para leitura, à lista de produtos no carrinho.
    */
    const std::vector<Produto>& getProdutos() const;

    /** * @brief Fornece acesso, somente para leitura, à lista de quantidades dos produtos no carrinho.
    */
    const std::vector<int>& getQuantidades() const;

};
 
#endif