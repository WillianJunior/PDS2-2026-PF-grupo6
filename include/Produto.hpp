#ifndef PRODUTO_HPP
#define PRODUTO_HPP

#include <string>

/**
 * @brief Enumeração para mapear as categorias de livros disponíveis no e-commerce.
 */
enum class CategoriaProduto { Ficcao, Tecnico, Infantil, Romance, Suspense, Fantasia };

/**
 * @brief Classe que armazena e fornece as informações de um produto do e-commerce.
 */
class Produto {

private:
    int _id;
    std::string _nome;
    std::string _descricao;
    float _preco;
    int _quantidadeEstoque;
    CategoriaProduto _categoria;

public:
    
    /**
     * @brief Construtor da classe Produto.
     * @param id Identificador único do produto.
     * @param nome Nome de exibição do produto.
     * @param descricao Breve resumo ou sinopse do livro.
     * @param preco Valor de venda (deve ser maior que zero).
     * @param quantidadeEstoque Unidades disponíveis inicialmente.
     * @param categoria A categoria literária do livro.
     */

    Produto(int id, const std::string& nome, const std::string& descricao, 
            float preco, int quantidadeEstoque, CategoriaProduto categoria);

    
    int getId() const;
    const std::string& getNome() const;
    const std::string& getDescricao() const;
    float getPreco() const;
    int getQuantidadeEstoque() const;
    CategoriaProduto getCategoria() const;
    
    /**
     * @brief Atualiza o preço do produto (apenas se for maior que zero).
     * @param novoPreco O novo valor de venda solicitado.
     * @return true se o preço for maior que zero e a alteração for concluída, false caso contrário.
     */
    bool setPreco(float novoPreco);

    /**
     * @brief Debita uma quantidade do estoque após uma venda.
     * @param quantidadeVendida Número de unidades que saíram para o carrinho.
     * @return true se o débito foi feito com sucesso, false se faltar estoque.
     */
    bool debitarEstoque(int quantidadeVendida);

    /**
     * @brief Adiciona novas unidades ao estoque existente.
     * @param quantidadeRecebida Número de unidades recém-chegadas ao armazém.
     */
    void adicionarEstoque(int quantidadeRecebida);
};

#endif