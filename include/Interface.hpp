#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "Catalogo.hpp"
#include "Carrinho.hpp"
#include "Estoque.hpp"
#include "Pedido.hpp"
#include "Cliente.hpp"
#include "Administrador.hpp"

#include <string>

/**
 * @class Interface
 * @brief Centraliza toda a interação com o terminal.
 * Toda saída ao usuário (cout) e leitura de entrada (cin)
 * deve passar por esta classe, conforme separação de responsabilidades.
 */
class Interface {
public:
    void exibirMenuPrincipal();

    void exibirMenuCliente(Carrinho& carrinho,
                           Catalogo& catalogo,
                           Cliente& cliente);

    void exibirMenuAdministrador(Catalogo& catalogo,
                                 Estoque& estoque);

    void telaCadastroCliente(const std::string& nomeArquivo);
    void telaRecuperacaoSenha(const std::string& nomeArquivo);

    void telaCatalogo(Catalogo& catalogo);
    void telaBusca(Catalogo& catalogo);
    void telaOrdenarPreco(Catalogo& catalogo);

    /**
     * @brief Exibe o carrinho atualizado do cliente.
     * 
     * Mostra todos os produtos presentes no carrinho, suas quantidades,
     * o subtotal da compra, o valor do frete e o valor total.
     * Essa função é chamada dentro do menu do carrinho para que,
     * após cada alteração, o cliente visualize o estado atual do carrinho.
     * 
     * @param carrinho Referência constante para o carrinho do cliente.
     */
    void exibirCarrinhoAtualizado(const Carrinho& carrinho);

    /**
     * @brief Exibe o menu de gerenciamento do carrinho.
     * 
     * Permite que o cliente adicione produtos ao carrinho, altere a quantidade
     * de um produto já adicionado, remova um produto específico ou limpe todo
     * o carrinho. O catálogo é recebido para que a interface consiga listar
     * os produtos disponíveis e buscar o produto escolhido pelo ID.
     * 
     * @param carrinho Referência para o carrinho do cliente.
     * @param catalogo Referência para o catálogo de produtos disponíveis.
     */
    void telaCarrinho(Carrinho& carrinho,
                      Catalogo& catalogo);

    void telaCheckout(Carrinho& carrinho,
                      Cliente& cliente);

    void telaEstoque(Estoque& estoque);

    void imprimirSeparador() const;
    void imprimirTitulo(const std::string& titulo) const;
    void exibirErro(const std::string& mensagem) const;
    void exibirSucesso(const std::string& mensagem) const;
    int lerOpcao(const std::string& prompt) const;
    std::string lerTexto(const std::string& prompt) const;
};

#endif