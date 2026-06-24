#include "Interface.hpp"

#include <iostream>
#include <limits>
#include <string>

void Interface::imprimirSeparador() const {
    std::cout << "========================================\n";
}

void Interface::imprimirTitulo(const std::string& titulo) const {
    imprimirSeparador();
    std::cout << "   " << titulo << "\n";
    imprimirSeparador();
}

void Interface::exibirErro(const std::string& mensagem) const {
    std::cout << "[ERRO] " << mensagem << "\n";
}

void Interface::exibirSucesso(const std::string& mensagem) const {
    std::cout << "[OK] " << mensagem << "\n";
}

int Interface::lerOpcao(const std::string& prompt) const {
    int opcao;
    std::cout << prompt;

    while (!(std::cin >> opcao)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Opcao invalida. Tente novamente: ";
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return opcao;
}

std::string Interface::lerTexto(const std::string& prompt) const {
    std::string texto;
    std::cout << prompt;
    std::getline(std::cin, texto);
    return texto;
}

// ── Menu Principal ───────────────────────────────────

void Interface::exibirMenuPrincipal() {
    imprimirTitulo("BEM-VINDO A LIVRARIA ONLINE");
    std::cout << "1 - Login\n";
    std::cout << "2 - Cadastrar\n";
    std::cout << "3 - Recuperar senha\n";
    std::cout << "0 - Sair\n";
}

// ── Autenticacao ─────────────────────────────────────

void Interface::telaCadastroCliente(const std::string& nomeArquivo) {
    imprimirTitulo("CADASTRO DE CLIENTE");

    std::string nome     = lerTexto("Nome: ");
    std::string email    = lerTexto("Email: ");
    std::string senha    = lerTexto("Senha: ");
    std::string cpf      = lerTexto("CPF: ");
    std::string resposta = lerTexto("Qual foi a primeira escola que voce estudou? ");

    Cliente cliente(nome, email, senha, cpf, resposta);

    if (cliente.cadastrarCliente(nomeArquivo)) {
        exibirSucesso("Cadastro realizado com sucesso!");
    } else {
        exibirErro("Dados invalidos ou email ja cadastrado.");
    }
}

void Interface::telaRecuperacaoSenha(const std::string& nomeArquivo) {
    imprimirTitulo("RECUPERAR SENHA");

    std::string email     = lerTexto("Email: ");
    std::string resposta  = lerTexto("Qual foi a primeira escola que voce estudou? ");
    std::string novaSenha = lerTexto("Nova senha: ");

    if (Usuario::recuperarSenha(email, resposta, novaSenha, nomeArquivo)) {
        exibirSucesso("Senha atualizada com sucesso!");
    } else {
        exibirErro("Dados incorretos ou senha muito curta.");
    }
}

// ── Catalogo ─────────────────────────────────────────

void Interface::telaCatalogo(Catalogo& catalogo) {
    int opcao;

    do {
        imprimirTitulo("CATALOGO");
        std::cout << "1 - Buscar por palavra-chave\n";
        std::cout << "2 - Listar por categoria\n";
        std::cout << "3 - Ordenar por preco\n";
        std::cout << "4 - Ver descricao de produto\n";
        std::cout << "0 - Voltar\n";

        opcao = lerOpcao("Opcao: ");

        if (opcao == 1) {
            telaBusca(catalogo);
        } else if (opcao == 2) {
            imprimirTitulo("CATEGORIAS");
            std::cout << "1 - Ficcao\n2 - Tecnico\n3 - Infantil\n4 - Romance\n5 - Suspense\n6 - Fantasia\n";

            int cat = lerOpcao("Categoria: ");
            CategoriaProduto categoria;
            bool categoriaValida = true;

            switch (cat) {
                case 1: categoria = CategoriaProduto::Ficcao; break;
                case 2: categoria = CategoriaProduto::Tecnico; break;
                case 3: categoria = CategoriaProduto::Infantil; break;
                case 4: categoria = CategoriaProduto::Romance; break;
                case 5: categoria = CategoriaProduto::Suspense; break;
                case 6: categoria = CategoriaProduto::Fantasia; break;
                default: 
                    exibirErro("Categoria invalida.");
                    categoriaValida = false;
                    break;
            }

            if (categoriaValida) {
                std::string resultado = catalogo.listarProdutosCategoria(categoria);
                if (resultado.empty()) {
                    exibirErro("Nenhum produto encontrado.");
                } else {
                    std::cout << resultado;
                }
            }
        } else if (opcao == 3) {
            telaOrdenarPreco(catalogo);
        } else if (opcao == 4) {
            int id = lerOpcao("ID do produto: ");
            std::string desc = catalogo.exibirDescricao(id);

            if (desc.empty()) {
                exibirErro("Produto nao encontrado.");
            } else {
                std::cout << desc << "\n";
            }
        }

    } while (opcao != 0);
}

void Interface::telaBusca(Catalogo& catalogo) {
    std::string palavra = lerTexto("Palavra-chave: ");
    std::string resultado = catalogo.buscarItem(palavra);

    if (resultado.empty()) {
        exibirErro("Nenhum produto encontrado.");
    } else {
        std::cout << resultado;
    }
}

void Interface::telaOrdenarPreco(Catalogo& catalogo) {
    int opcao = lerOpcao("1 - Crescente  2 - Decrescente: ");
    std::cout << catalogo.ordenarPreco(opcao == 1);
}

// ── Carrinho ─────────────────────────────────────────

void Interface::telaCarrinho(Carrinho& carrinho) {
    imprimirTitulo("SEU CARRINHO");

    const auto& produtos    = carrinho.getProdutos();
    const auto& quantidades = carrinho.getQuantidades();

    if (produtos.empty()) {
        std::cout << "Carrinho vazio.\n";
        return;
    }

    for (size_t i = 0; i < produtos.size(); i++) {
        std::cout << produtos[i].getNome()
                  << " x" << quantidades[i]
                  << " - R$ "
                  << produtos[i].getPreco() * quantidades[i]
                  << "\n";
    }

    imprimirSeparador();
    std::cout << "Subtotal: R$ " << carrinho.calcularSubtotal() << "\n";
    std::cout << "Frete:    R$ " << carrinho.getValorFrete()    << "\n";
    std::cout << "Total:    R$ " << carrinho.getValorTotal()    << "\n";
}

void Interface::telaCheckout(Carrinho& carrinho, Cliente& cliente) {
    imprimirTitulo("FINALIZAR COMPRA");

    try {
        Pedido pedido(carrinho, cliente);

        std::cout << pedido.gerarResumoFaturamento(cliente, carrinho);
        std::cout << pedido.informarValorFrete(cliente.getEndereco()) << "\n";
        std::cout << pedido.estimarDataEntrega(cliente.getEndereco()) << "\n";

        std::cout << "1 - Pix  2 - Credito  3 - Debito\n";
        int opcao = lerOpcao("Forma de pagamento: ");

        Pedido::MetodoPagamento metodo = Pedido::MetodoPagamento::Pix;
        if (opcao == 2) {
            metodo = Pedido::MetodoPagamento::Credito;
        } else if (opcao == 3) {
            metodo = Pedido::MetodoPagamento::Debito;
        }

        std::cout << pedido.processarPagamentos(metodo) << "\n";

        // BUGS CORRIGIDOS: Passando o carrinho como argumento exigido na assinatura
        pedido.salvarEmArquivo(cliente, carrinho);

        exibirSucesso("Pedido salvo com sucesso!");
        carrinho.limparCarrinho();

    } catch (const std::exception& e) {
        exibirErro(e.what());
    }
}

// ── Estoque (admin) ──────────────────────────────────

void Interface::telaEstoque(Estoque& estoque) {
    imprimirTitulo("GERENCIAR ESTOQUE");

    std::cout << estoque.exibirQuantidadeDisponiveis();
    imprimirSeparador();

    std::string alertas = estoque.alertarEstoqueCritico();
    if (!alertas.empty()) {
        std::cout << alertas;
    }
}

// ── Menus de acesso ──────────────────────────────────

void Interface::exibirMenuCliente(Carrinho& carrinho, Catalogo& catalogo, Cliente& cliente) {
    int opcao;

    do {
        imprimirTitulo("MENU CLIENTE");
        std::cout << "1 - Catalogo\n2 - Meu carrinho\n3 - Finalizar compra\n0 - Sair\n";

        opcao = lerOpcao("Opcao: ");

        if (opcao == 1) {
            telaCatalogo(catalogo);
        } else if (opcao == 2) {
            telaCarrinho(carrinho);
        } else if (opcao == 3) {
            telaCheckout(carrinho, cliente);
        }
    } while (opcao != 0);
}

void Interface::exibirMenuAdministrador(Catalogo& catalogo, Estoque& estoque) {
    int opcao;

    do {
        imprimirTitulo("MENU ADMINISTRADOR");
        std::cout << "1 - Catalogo\n2 - Estoque\n0 - Sair\n";

        opcao = lerOpcao("Opcao: ");

        if (opcao == 1) {
            telaCatalogo(catalogo);
        } else if (opcao == 2) {
            telaEstoque(estoque);
        }
    } while (opcao != 0);
}