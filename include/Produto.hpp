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
    
    /**git helpinclude/Produto.cppgit add test
     * @brief Construtor da classe Produto.
     * @param id Identificador único do produto.
     * @param nome Nome de exibição do produto.
     * @param descricao Breve resumo ou sinopse do livro.
     * @param preco Valor de venda (deve ser maior que zero).
     * @param quantidadeEstoque Unidades disponíveis inicialmente.
     * @param categoria A categoria literária do livro.
     * @throws std::invalid_argument se o preço for menor ou igual a zero, ou o estoque for negativo.
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
     * @throws std::invalid_argument se o novo preço for menor ou igual a zero.
     */
    void setPreco(float novoPreco);

    /**
     * @brief Debita uma quantidade do estoque após uma venda.
     * @param quantidadeVendida Número de unidades que saíram para o carrinho.
     * @throws std::invalid_argument se a quantidade vendida for menor ou igual a zero.
     * @throws std::out_of_range se a quantidade solicitada for maior que o estoque atual.
     */
    void debitarEstoque(int quantidadeVendida);

    /**
     * @brief Adiciona novas unidades ao estoque existente.
     * @param quantidadeRecebida Número de unidades recém-chegadas ao armazém.
     * @throws std::invalid_argument se a quantidade recebida for menor ou igual a zero.
     */
    void adicionarEstoque(int quantidadeRecebida);
};

#endif