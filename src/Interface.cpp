#include "Interface.hpp"

#include <iostream>
#include <limits>
#include <string>
#include <vector>

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

    try {
        Cliente cliente(nome, email, senha, cpf, resposta);

        if (cliente.cadastrarCliente(nomeArquivo)) {
            exibirSucesso("Cadastro realizado com sucesso!");
        } else {
            exibirErro("Dados invalidos ou email ja cadastrado.");
        }
    } catch (const std::exception& e) {
        exibirErro(e.what());
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

        try {
            if (opcao == 1) {
                telaBusca(catalogo);
            } else if (opcao == 2) {
                imprimirTitulo("CATEGORIAS");
                std::cout << "1 - Ficcao\n";
                std::cout << "2 - Tecnico\n";
                std::cout << "3 - Infantil\n";
                std::cout << "4 - Romance\n";
                std::cout << "5 - Suspense\n";
                std::cout << "6 - Fantasia\n";

                int cat = lerOpcao("Categoria: ");
                CategoriaProduto categoria = CategoriaProduto::Ficcao;
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
            } else if (opcao != 0) {
                exibirErro("Opcao invalida.");
            }

        } catch (const std::exception& e) {
            exibirErro(e.what());
        }

    } while (opcao != 0);
}

void Interface::telaBusca(Catalogo& catalogo) {
    try {
        std::string palavra = lerTexto("Palavra-chave: ");
        std::string resultado = catalogo.buscarItem(palavra);

        if (resultado.empty()) {
            exibirErro("Nenhum produto encontrado.");
        } else {
            std::cout << resultado;
        }
    } catch (const std::exception& e) {
        exibirErro(e.what());
    }
}

void Interface::telaOrdenarPreco(Catalogo& catalogo) {
    try {
        int opcao = lerOpcao("1 - Crescente  2 - Decrescente: ");
        std::cout << catalogo.ordenarPreco(opcao == 1);
    } catch (const std::exception& e) {
        exibirErro(e.what());
    }
}

// ── Carrinho ─────────────────────────────────────────

void Interface::exibirCarrinhoAtualizado(const Carrinho& carrinho) {
    imprimirTitulo("SEU CARRINHO");

    const auto& produtos = carrinho.getProdutos();
    const auto& quantidades = carrinho.getQuantidades();

    if (produtos.empty()) {
        std::cout << "Carrinho vazio.\n";
        return;
    }

    for (size_t i = 0; i < produtos.size(); i++) {
        std::cout << "ID: " << produtos[i].getId()
                  << " | " << produtos[i].getNome()
                  << " x" << quantidades[i]
                  << " - R$ " << produtos[i].getPreco() * quantidades[i]
                  << "\n";
    }

    imprimirSeparador();
    std::cout << "Subtotal: R$ " << carrinho.calcularSubtotal() << "\n";
    std::cout << "Frete:    R$ " << carrinho.getValorFrete() << "\n";
    std::cout << "Total:    R$ " << carrinho.getValorTotal() << "\n";
}

void Interface::telaCarrinho(Carrinho& carrinho, Catalogo& catalogo) {
    int opcao;

    do {
        exibirCarrinhoAtualizado(carrinho);

        imprimirSeparador();
        std::cout << "1 - Adicionar produto\n";
        std::cout << "2 - Alterar quantidade\n";
        std::cout << "3 - Remover produto\n";
        std::cout << "4 - Limpar carrinho\n";
        std::cout << "0 - Voltar\n";

        opcao = lerOpcao("Opcao: ");

        try {
            if (opcao == 1) {
                imprimirTitulo("PRODUTOS DISPONIVEIS");

                std::string produtosDisponiveis = catalogo.listarProdutosDisponiveis();

                if (produtosDisponiveis.empty()) {
                    exibirErro("Nenhum produto disponivel no catalogo.");
                    continue;
                }

                std::cout << produtosDisponiveis;

                int id = lerOpcao("Digite o ID do livro desejado: ");
                int quantidade = lerOpcao("Quantidade: ");

                Produto produto = catalogo.buscarProdutoPorId(id);
                carrinho.adicionarProduto(produto, quantidade);
                exibirSucesso("Produto adicionado ao carrinho.");
            }

            else if (opcao == 2) {
                int id = lerOpcao("ID do produto: ");
                int novaQuantidade = lerOpcao("Nova quantidade: ");

                carrinho.atualizarQuantidade(id, novaQuantidade);
                exibirSucesso("Quantidade atualizada.");
            }

            else if (opcao == 3) {
                int id = lerOpcao("ID do produto: ");

                carrinho.removerProduto(id);
                exibirSucesso("Produto removido do carrinho.");
            }

            else if (opcao == 4) {
                carrinho.limparCarrinho();
                exibirSucesso("Carrinho limpo.");
            }

            else if (opcao != 0) {
                exibirErro("Opcao invalida.");
            }

        } catch (const std::exception& e) {
            exibirErro(e.what());
        }

    } while (opcao != 0);
}

// ── Checkout ─────────────────────────────────────────

void Interface::telaCheckout(Carrinho& carrinho, Cliente& cliente) {
    imprimirTitulo("FINALIZAR COMPRA");

    try {
        if (cliente.getEndereco().empty()) {
            std::string endereco = lerTexto("Informe o endereco de entrega: ");
            cliente.adicionarEndereco(endereco);
        }
        
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

        pedido.salvarEmArquivo(cliente, carrinho);

        exibirSucesso("Pedido saved com sucesso!");
        carrinho.limparCarrinho();

    } catch (const std::exception& e) {
        exibirErro(e.what());
    }
}

// ── Estoque (admin) ──────────────────────────────────

void Interface::telaEstoque(Estoque& estoque) {
    imprimirTitulo("GERENCIAR ESTOQUE");

    std::vector<Produto> inventario = estoque.obterInventario();

    for (const auto& p : inventario) {
        std::cout << p.getNome() << ": " << p.getQuantidadeEstoque() << " unidades\n";
    }

    imprimirSeparador();

    std::vector<Produto> alertas = estoque.obterProdutosEmAlerta();

    if (!alertas.empty()) {
        for (const auto& p : alertas) {
            std::cout << "ALERTA: " << p.getNome() << " com estoque critico!\n";
        }
    }
}

// ── Menus de acesso ──────────────────────────────────

/* // TODO para amanhã: Descomentar este bloco para ativar o Cabeçalho Polimórfico útil
void Interface::exibirCabecalhoMenu(const Usuario& usuarioLogado) const {
    imprimirTitulo("SISTEMA DE E-COMMERCE");
    usuarioLogado.exibirPerfil(); //
    imprimirSeparador();
}
*/

void Interface::exibirMenuCliente(Carrinho& carrinho, Catalogo& catalogo, Cliente& cliente) {
    int opcao;

    do {
        // Amanhã eu substituo a linha de baixo por: exibirCabecalhoMenu(cliente);
        imprimirTitulo("MENU CLIENTE");
        std::cout << "1 - Catalogo\n";
        std::cout << "2 - Meu carrinho\n";
        std::cout << "3 - Finalizar compra\n";
        std::cout << "0 - Sair\n";

        opcao = lerOpcao("Opcao: ");

        if (opcao == 1) {
            telaCatalogo(catalogo);
        } else if (opcao == 2) {
            telaCarrinho(carrinho, catalogo);
        } else if (opcao == 3) {
            telaCheckout(carrinho, cliente);
        } else if (opcao != 0) {
            exibirErro("Opcao invalida.");
        }

    } while (opcao != 0);
}

void Interface::exibirMenuAdministrador(Catalogo& catalogo, Estoque& estoque) {
    int opcao;

    do {
        imprimirTitulo("MENU ADMINISTRADOR");
        std::cout << "1 - Catalogo\n";
        std::cout << "2 - Estoque\n";
        std::cout << "0 - Sair\n";

        opcao = lerOpcao("Opcao: ");

        if (opcao == 1) {
            telaCatalogo(catalogo);
        } else if (opcao == 2) {
            telaEstoque(estoque);
        } else if (opcao != 0) {
            exibirErro("Opcao invalida.");
        }

    } while (opcao != 0);
}