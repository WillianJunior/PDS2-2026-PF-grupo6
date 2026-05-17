#ifndef PRODUTO_HPP
#define PRODUTO_HPP

#include <string>

/**
 * @brief Categorias disponíveis na loja.
 * Colocado o enum aqui para que o Produto já nasça com uma categoria definida!
 */
enum CategoriaProduto {
    LIVROS,
    ELETRONICOS,
    ROUPAS,
    ALIMENTOS
};

/**
 * @brief Classe armazena e fornece as informações de um produto do e-commerce.
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

    Produto(int id, const std::string& nome, const std::string& descricao, float preco, int quantidadeEstoque, CategoriaProduto categoria);

    /**
     * @brief Retorna o identificador único do produto.
     * O método é const para garantir que a consulta não altere o ID do produto.
     */
    int getId() const;

    /**
     * @brief Retorna o nome do produto.
     * Retorna por referência constante para não gastar memória fazendo cópia do texto.
     */
    const std::string& getNome() const;

    /**
     * @brief Retorna a descrição do produto.
     * Retorna por referência constante para otimização de memória.
     */
    const std::string& getDescricao() const;

    /**
     * @brief Retorna o preço do produto.
     * Este método é const para garantir que a consulta não altere o valor do produto.
     */
    float getPreco() const;

    /**
     * @brief Retorna a quantidade atual de unidades do produto em estoque.
     * Este método é const para garantir que a consulta não altere a contagem de unidades.
     */
    int getQuantidadeEstoque() const;

    /**
     * @brief Retorna a categoria à qual este produto pertence.
     */
    CategoriaProduto getCategoria() const;
};

#endif