#ifndef PRODUTO_HPP
#define PRODUTO_HPP

#include <string>
class estoque;

/**
 * @brief Armazena e fornece as informações de um livro.
 */

class produto {

private:

    int _id;
    std::string _nome;
    std::string _descricao;
    float _preco;
    int quantidadeEstoque;

public:

    produto(int id, std::string nome, std::string descricao, float preco, int quantidadeEstoque);

/**
* @brief Retorna o identificador único do livro. 
*/
    int getId();

/**
* @brief Retorna o nome do livro.
*/
    std::string getNome();

/**
 * @brief Retorna a descrição do livro.
 */
    std::string getDescricao();

/**
* @brief Retorna o preço do livro.
*/
    float getPreco();

/**
* @brief Retorna a quantidade atual de produtos em estoque.
*/
    int getQuantidadeEstoque();
};

#endif
