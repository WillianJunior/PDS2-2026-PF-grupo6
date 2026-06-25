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

    void telaPerfil(Cliente& cliente);
    void telaGerenciarCartoes(Cliente& cliente);

    void telaCatalogo(Catalogo& catalogo);
    void telaBusca(Catalogo& catalogo);
    void telaOrdenarPreco(Catalogo& catalogo);

    void exibirCarrinhoAtualizado(const Carrinho& carrinho);
    
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
