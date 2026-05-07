#ifndef CATALOGO_HPP
#define CATALOGO_HPP

#include "Produto.hpp"
#include <vector>
#include <string>

class Catalogo {

private:
    std::vector<Produto> produtos_;

public:

    /** 
     * @brief O catálogo exibe os produtos que são vendidos pelo e-commerce.
     */
    Catalogo();

    /** 
     * @brief Lista produtos de acordo com a categoria selecionada.
     * @param tipo Define o tipo do produto a ser procurado.
     */
    void listarProdutosCategoria(char tipo) const;

    /** 
     * @brief Busca produtos com base em uma palavra-chave.
     * @param palavraChave Palavra utilizada na busca do produto.
     */
    void buscarItem(const std::string& palavraChave) const;

    /** 
     * @brief Ordena o catálogo pelo preço.
     * @param crescente Define se a ordem será crescente ou não.
     */
    void ordenarPreco(bool crescente);

    /** 
     * @brief Exibe a descrição de um produto selecionado.
     * @param idProduto Identificação do produto.
     */
    void exibirDescricao(int idProduto) const;
};

#endif