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
     * @brief Construtor da classe Catalogo.
     */
    Catalogo();

    /**
     * @brief Lista produtos de acordo com a categoria selecionada.
     * @param categoria Define a categoria do produto a ser procurada.
     * @return String contendo os dados dos livros encontrados.
     * @throws std::runtime_error Se ocorrer um erro ao abrir o arquivo.
     */
    std::string listarProdutosCategoria(CategoriaProduto categoria) const;

    /**
     * @brief Busca produtos com base em uma palavra-chave.
     * @param palavraChave Palavra utilizada na busca do produto.
     * @return String contendo os dados dos livros que dão match com a palavra.
     * @throws std::runtime_error Se ocorrer um erro ao abrir o arquivo.
     */
    std::string buscarItem(const std::string& palavraChave) const;

    /**
     * @brief Ordena o catálogo pelo preço.
     * @param crescente Define se a ordem será crescente (true) ou decrescente (false).
     * @return String contendo a listagem ordenada de livros.
     * @throws std::runtime_error Se ocorrer um erro ao abrir o arquivo.
     */
    std::string ordenarPreco(bool crescente);

    /**
     * @brief Obtém a descrição de um produto selecionado.
     * @param idProduto Identificação do produto.
     * @return String com a descrição do produto ou vazia se não encontrado.
     * @throws std::runtime_error Se ocorrer um erro ao abrir o arquivo.
     */
    std::string exibirDescricao(int idProduto) const;

    /**
     * @brief Adiciona um produto ao catálogo.
     * @param produto Produto a ser adicionado.
     * @throws std::runtime_error Se ocorrer um erro ao abrir o arquivo para escrita.
     */
    void adicionarProduto(const Produto& produto);

    /**
     * @brief Remove um produto do catálogo pelo ID.
     * @param idProduto Identificação do produto a ser removido.
     * @throws std::runtime_error Se ocorrer um erro ao abrir o arquivo para alteração.
     */
    void removerProduto(int idProduto);

    /**
     * @brief Estrutura fictícia representando um pedido realizado.
     */
    struct ResumoPedido {
        int idPedido;
        std::string nomeCliente;
        std::string enderecoEntrega;
        double valorTotal;
        bool pagamentoAprovado;
    };
};

#endif