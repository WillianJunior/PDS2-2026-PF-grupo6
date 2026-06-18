#ifndef UI_HPP
#define UI_HPP

#include "Catalogo.hpp"
#include "Carrinho.hpp"
#include "Estoque.hpp"
#include "Pedido.hpp"
#include "Cliente.hpp"
#include "Administrador.hpp"

#include <string>

/**
 * @class UI
 * @brief Centraliza toda a interação com o terminal.
 * Toda saída ao usuário (cout) e leitura de entrada (cin)
 * deve passar por esta classe, conforme separação de responsabilidades.
 */
class UI {
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


    void telaCarrinho(Carrinho& carrinho);
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