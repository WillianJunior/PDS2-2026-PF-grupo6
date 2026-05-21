#ifndef CATALOGO_HPP
#define CATALOGO_HPP

#include "Produto.hpp"
#include <vector>
#include <string>

class Catalogo {

private:
    std::vector<Produto> produtos_;

public:

    /** * @brief O catálogo exibe os produtos que são vendidos pelo e-commerce.
     */
    Catalogo();

    /** * @brief Lista produtos de acordo com a categoria selecionada.
     * @param categoria Define a categoria do produto a ser procurada.
     */
    void listarProdutosCategoria(CategoriaProduto categoria) const;

    /** * @brief Busca produtos com base em uma palavra-chave.
     * @param palavraChave Palavra utilizada na busca do produto.
     */
    void buscarItem(const std::string& palavraChave) const;

    /** * @brief Ordena o catálogo pelo preço.
     * @param crescente Define se a ordem será crescente ou não.
     */
    void ordenarPreco(bool crescente);

    /** * @brief Exibe a descrição de um produto selecionado.
     * @param idProduto Identificação do produto.
     */
    void exibirDescricao(int idProduto) const;
    
    /** * @brief Adiciona um produto ao catálogo.
     * @param produto Produto a ser adicionado.
     */
    void adicionarProduto(const Produto& produto);
    /** * @brief Remove um produto do catálogo.
     * @param idProduto Identificação do produto a ser removido.
     */
    void removerProduto(int idProduto);

    /**
     * @brief Estrutura fictícia representando um pedido realizado.
     */
    struct Pedido {

        int idPedido;
        std::string nomeCliente;
        std::string enderecoEntrega;
        double valorTotal;
        bool pagamentoAprovado;
    };
};

#endif