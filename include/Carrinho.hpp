#ifndef CARRINHO_HPP
#define CARRINHO_HPP

#include <vector>
#include "Produto.hpp"
#include "Cliente.hpp"

/**
 * @class Carrinho
 * @brief Representa o carrinho ativo de um cliente no e-commerce.
 *
 * O carrinho mantém os produtos escolhidos pelo cliente e suas respectivas
 * quantidades. Também é responsável por salvar e recuperar esses dados em
 * arquivo, usando o CPF do cliente como identificador.
 */
class Carrinho {
private:
    std::vector<Produto> _produtos;
    std::vector<int> _quantidades;
    Cliente& _cliente;

    /**
     * @brief Busca a posição de um produto dentro do carrinho.
     * @return Índice do produto no vetor ou -1 caso não esteja no carrinho.
     */
    int buscarIdProduto(int idProduto) const;

    /**
     * @brief Verifica se o estoque do produto permite a quantidade solicitada.
     */
    bool validarEstoque(const Produto& produto, int quantidade) const;

    /**
     * @brief Salva o carrinho atual no arquivo Carrinho.txt.
     *
     * Antes de salvar, remove o bloco antigo do mesmo cliente para evitar
     * duplicação de dados no arquivo.
     */
    void salvarCarrinhoNoArquivo() const;

    /**
     * @brief Carrega do arquivo Carrinho.txt o carrinho associado ao CPF do cliente.
     */
    void carregarCarrinhoDoArquivo();

public:
    /**
     * @brief Cria um carrinho associado a um cliente e tenta carregar dados salvos.
     */
    Carrinho(Cliente& cliente);

    /**
     * @brief Adiciona um produto ao carrinho ou incrementa sua quantidade.
     */
    void adicionarProduto(const Produto& produto, int quantidade);

    /**
     * @brief Remove um produto do carrinho pelo ID.
     */
    void removerProduto(int idProduto);

    /**
     * @brief Atualiza a quantidade de um produto já existente no carrinho.
     */
    void atualizarQuantidade(int idProduto, int novaQuantidade);

    /**
     * @brief Remove todos os produtos do carrinho e atualiza o arquivo.
     */
    void limparCarrinho();

    /**
     * @brief Calcula o subtotal da compra, sem frete.
     */
    double calcularSubtotal() const;

    /**
     * @brief Calcula o frete de acordo com o subtotal.
     */
    double calcularValorFrete() const;

    /**
     * @brief Calcula o total da compra somando subtotal e frete.
     */
    double calcularTotal() const;

    /**
     * @brief Retorna o valor total da compra.
     */
    double getValorTotal() const;

    /**
     * @brief Retorna o valor atual do frete.
     */
    double getValorFrete() const;

    /**
     * @brief Retorna os produtos do carrinho sem permitir alteração direta.
     */
    const std::vector<Produto>& getProdutos() const;

    /**
     * @brief Retorna as quantidades dos produtos sem permitir alteração direta.
     */
    const std::vector<int>& getQuantidades() const;
};

#endif