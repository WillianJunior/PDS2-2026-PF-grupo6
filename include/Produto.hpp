#ifndef PRODUTO_HPP
#define PRODUTO_HPP

#include <string>

/**
 * @brief Classe armazena e fornece as informações de um livro.
 */

class Produto {

private:

    int _id;
    std::string _nome;
    std::string _descricao;
    float _preco;
    int _quantidadeEstoque;

public:

    Produto(int id, std::string nome, std::string descricao, float preco, int quantidadeEstoque);

/**
* @brief Retorna o identificador único do livro.
* O método é const para garantir que a consulta não altere o ID do produto.
*/
    int getId() const;

/**
* @brief Retorna o nome do livro.
* Este método é const para garantir que a consulta não altere o nome do produto.
*/
    std::string getNome() const;

/**
 * @brief Retorna a descrição do livro.
 * Este método é const para garantir que a consulta não altere a descrição do produto.
 */
    std::string getDescricao() const;

/**
* @brief Retorna o preço do livro.
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