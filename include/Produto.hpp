#ifndef PRODUTO_HPP
#define PRODUTO_HPP

#include <string>

enum class CategoriaProduto { Ficcao, Tecnico, Infantil, Romance };

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

public:

    Produto(int id, const std::string& nome, const std::string& descricao, float preco, int quantidadeEstoque);

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

};

#endif
