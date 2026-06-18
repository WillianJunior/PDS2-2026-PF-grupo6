#ifndef CARRINHO_HPP
#define CARRINHO_HPP

#include <vector>
#include <stdexcept>
#include <string>
#include "Produto.hpp"
#include "Cliente.hpp"

/**
 * @class ProdutoNaoEncontradoException
 * @brief Exceção lançada quando um produto não é encontrado no carrinho.
 */
class ProdutoNaoEncontradoException : public std::runtime_error {
public:
    /**
     * @brief Constrói a exceção com mensagem padrão.
     */
    ProdutoNaoEncontradoException();
};

/**
 * @class EstoqueInsuficienteException
 * @brief Exceção lançada quando o estoque não permite a quantidade solicitada.
 */
class EstoqueInsuficienteException : public std::runtime_error {
public:
    /**
     * @brief Constrói a exceção com mensagem padrão.
     */
    EstoqueInsuficienteException();
};

/**
 * @class QuantidadeInvalidaException
 * @brief Exceção lançada quando uma quantidade inválida é informada.
 */
class QuantidadeInvalidaException : public std::runtime_error {
public:
    /**
     * @brief Constrói a exceção com mensagem padrão.
     */
    QuantidadeInvalidaException();
};

/**
 * @class ErroArquivoCarrinhoException
 * @brief Exceção lançada quando ocorre erro ao salvar ou carregar o carrinho.
 */
class ErroArquivoCarrinhoException : public std::runtime_error {
public:
    /**
     * @brief Constrói a exceção com uma mensagem específica.
     * @param mensagem Mensagem explicando o erro ocorrido.
     */
    ErroArquivoCarrinhoException(const std::string& mensagem);
};

/**
 * @class Carrinho
 * @brief Representa o carrinho ativo de um cliente no e-commerce.
 */
class Carrinho {
private:
    std::vector<Produto> _produtos;
    std::vector<int> _quantidades;
    Cliente& _cliente;

    /**
     * @brief Busca a posição de um produto dentro do carrinho.
     * @param idProduto ID do produto procurado.
     * @return Índice do produto no vetor ou -1 caso não esteja no carrinho.
     */
    int buscarIdProduto(int idProduto) const;

    /**
     * @brief Verifica se o estoque permite a quantidade solicitada.
     * @param produto Produto que será validado.
     * @param quantidade Quantidade desejada.
     * @return true se houver estoque suficiente, false caso contrário.
     */
    bool validarEstoque(const Produto& produto, int quantidade) const;

    /**
     * @brief Salva o carrinho atual no arquivo Carrinho.txt.
     * @throw ErroArquivoCarrinhoException Se não for possível abrir o arquivo.
     */
    void salvarCarrinhoNoArquivo() const;

    /**
     * @brief Carrega do arquivo Carrinho.txt o carrinho associado ao CPF do cliente.
     * @throw ErroArquivoCarrinhoException Se o arquivo estiver com dados inválidos.
     */
    void carregarCarrinhoDoArquivo();

public:
    /**
     * @brief Cria um carrinho associado a um cliente.
     * @param cliente Cliente dono do carrinho.
     */
    Carrinho(Cliente& cliente);

    /**
     * @brief Adiciona um produto ao carrinho ou incrementa sua quantidade.
     * @param produto Produto a ser adicionado.
     * @param quantidade Quantidade desejada.
     * @throw QuantidadeInvalidaException Se quantidade <= 0.
     * @throw EstoqueInsuficienteException Se não houver estoque suficiente.
     */
    void adicionarProduto(const Produto& produto, int quantidade);

    /**
     * @brief Remove um produto do carrinho pelo ID.
     * @param idProduto ID do produto a ser removido.
     * @throw ProdutoNaoEncontradoException Se o produto não existir no carrinho.
     */
    void removerProduto(int idProduto);

    /**
     * @brief Atualiza a quantidade de um produto já existente no carrinho.
     * @param idProduto ID do produto.
     * @param novaQuantidade Nova quantidade desejada.
     * @throw QuantidadeInvalidaException Se a quantidade for negativa.
     * @throw ProdutoNaoEncontradoException Se o produto não existir no carrinho.
     * @throw EstoqueInsuficienteException Se não houver estoque suficiente.
     */
    void atualizarQuantidade(int idProduto, int novaQuantidade);

    /**
     * @brief Remove todos os produtos do carrinho.
     */
    void limparCarrinho();

    /**
     * @brief Calcula o subtotal da compra, sem frete.
     * @return Subtotal da compra.
     */
    double calcularSubtotal() const;

    /**
     * @brief Calcula o valor do frete.
     * @return Valor do frete.
     */
    double calcularValorFrete() const;

    /**
     * @brief Calcula o total da compra somando subtotal e frete.
     * @return Valor total da compra.
     */
    double calcularTotal() const;

    /**
     * @brief Retorna o valor total da compra.
     * @return Valor total.
     */
    double getValorTotal() const;

    /**
     * @brief Retorna o valor atual do frete.
     * @return Valor do frete.
     */
    double getValorFrete() const;

    /**
     * @brief Retorna os produtos do carrinho sem permitir alteração direta.
     * @return Referência constante para o vetor de produtos.
     */
    const std::vector<Produto>& getProdutos() const;

    /**
     * @brief Retorna as quantidades dos produtos sem permitir alteração direta.
     * @return Referência constante para o vetor de quantidades.
     */
    const std::vector<int>& getQuantidades() const;
};

#endif