#ifndef CARRINHO_HPP
#define CARRINHO_HPP
#include <vector>

class Produto; 
class Cliente;

/**  
 * @brief Classe Carrinho representa um carrinho de compras.
 * 
 * Esta classe é responsável por armazenar os itens adicionados ao carrinho, calcular o total da compra e fornecer métodos para manipular os itens.
 */

class Carrinho {
    private:
    std::vector<Produto*> _produtos; 
    std::vector<int> _quantidades; 
    Cliente* _cliente; 
    double _valorFrete; 
    
    public:
    /** @brief Construtor da classe Carrinho.
     * @param cliente Ponteiro para o cliente associado ao carrinho.
     */
    Carrinho(Cliente* cliente);

    /** @brief Adiciona um produto ao carrinho.
     * @param produto Ponteiro para o produto a ser adicionado.
     * @param quantidade Quantidade do produto a ser adicionada.
     */
    void adicionarProduto(Produto* produto, int quantidade);

    /** @brief Remove um produto do carrinho.
     * @param idProduto ID do produto a ser removido.
     */
    void removerProduto(int idProduto);

    /** @brief Atualiza a quantidade de um produto no carrinho.
     * @param idProduto ID do produto a ser atualizado.
     * @param novaQuantidade Nova quantidade do produto.
     */
    void atualizarQuantidade(int idProduto, int novaQuantidade);

    /**@brief Verifica se há disponibilidade de estoque para todos os produtos no carrinho.
     * @param produto Ponteiro para o produto a ser verificado.
     * @param quantidade Quantidade do produto a ser verificada.
     * @return Retorna true se todos os produtos estiverem disponíveis, false caso contrário.
     */
    bool validarDisponibilidade(Produto* produto, int quantidade);
    
    /** @brief Esvazia o carrinho, removendo todos os produtos e resetando o valor total da compra.
     */
    void limparCarrinho();
    
    /** @brief Calcula o subtotal dos produtos do carrinho.
     * @return Retorna o valor do subtotal dos produtos no carrinho.
     */
    double calcularSubtotal() const;

    /** @brief Calcula o valor total da compra, incluindo o subtotal dos produtos e o valor do frete.
     * @return Retorna o valor total da compra.
     */
    double calcularTotal() const;

    /** @brief Obtém o valor do frete para a compra.
     * @return Retorna o valor do frete.
     */
    double getValorFrete() const;

};
 
#endif