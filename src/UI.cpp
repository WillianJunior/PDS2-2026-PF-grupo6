#include "UI.hpp"

#include <iostream>
#include <limits>
#include <string>


void UI::imprimirSeparador() const {
    std::cout << "========================================\n";
}

void UI::imprimirTitulo(
        const std::string& titulo) const {

    imprimirSeparador();
    std::cout << "   " << titulo << "\n";
    imprimirSeparador();
}

void UI::exibirErro(
        const std::string& mensagem) const {

    std::cout << "[ERRO] " << mensagem << "\n";
}

void UI::exibirSucesso(
        const std::string& mensagem) const {

    std::cout << "[OK] " << mensagem << "\n";
}

int UI::lerOpcao(
        const std::string& prompt) const {

    int opcao;

    std::cout << prompt;

    while (!(std::cin >> opcao)) {
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');
        std::cout << "Opcao invalida. Tente novamente: ";
    }

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n');

    return opcao;
}

std::string UI::lerTexto(
        const std::string& prompt) const {

    std::string texto;
    std::cout << prompt;
    std::getline(std::cin, texto);
    return texto;
}

// ── Menu Principal ───────────────────────────────────

void UI::exibirMenuPrincipal() {
    imprimirTitulo("BEM-VINDO A LIVRARIA ONLINE");
    std::cout << "1 - Login\n";
    std::cout << "2 - Cadastrar\n";
    std::cout << "3 - Recuperar senha\n";
    std::cout << "0 - Sair\n";
}

// ── Autenticacao ─────────────────────────────────────

void UI::telaCadastroCliente(
        const std::string& nomeArquivo) {

    imprimirTitulo("CADASTRO DE CLIENTE");

    std::string nome     = lerTexto("Nome: ");
    std::string email    = lerTexto("Email: ");
    std::string senha    = lerTexto("Senha: ");
    std::string cpf      = lerTexto("CPF: ");
    std::string resposta = lerTexto(
        "Qual foi a primeira escola que voce estudou? ");

    Cliente cliente(nome, email, senha, cpf, resposta);

    if (cliente.cadastrarCliente(nomeArquivo)) {
        exibirSucesso("Cadastro realizado com sucesso!");
    } else {
        exibirErro(
            "Dados invalidos ou email ja cadastrado.");
    }
}

void UI::telaRecuperacaoSenha(
        const std::string& nomeArquivo) {

    imprimirTitulo("RECUPERAR SENHA");

    std::string email     = lerTexto("Email: ");
    std::string resposta  = lerTexto(
        "Qual foi a primeira escola que voce estudou? ");
    std::string novaSenha = lerTexto("Nova senha: ");

    if (Usuario::recuperarSenha(
            email, resposta, novaSenha, nomeArquivo)) {

        exibirSucesso("Senha atualizada com sucesso!");
    } else {
        exibirErro(
            "Dados incorretos ou senha muito curta.");
    }
}

// ── Catalogo ─────────────────────────────────────────

void UI::telaCatalogo(Catalogo& catalogo) {

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
            std::cout << "1 - Ficcao\n";
            std::cout << "2 - Tecnico\n";
            std::cout << "3 - Infantil\n";
            std::cout << "4 - Romance\n";
            std::cout << "5 - Suspense\n";
            std::cout << "6 - Fantasia\n";

            int cat = lerOpcao("Categoria: ");

            CategoriaProduto categoria =
                CategoriaProduto::Ficcao;

            if (cat == 2) {
                categoria = CategoriaProduto::Tecnico;
            } else if (cat == 3) {
                categoria = CategoriaProduto::Infantil;
            } else if (cat == 4) {
                categoria = CategoriaProduto::Romance;
            } else if (cat == 5) {
                categoria = CategoriaProduto::Suspense;
            } else if (cat == 6) {
                categoria = CategoriaProduto::Fantasia;
            }

            std::string resultado =
                catalogo.listarProdutosCategoria(categoria);

            if (resultado.empty()) {
                exibirErro("Nenhum produto encontrado.");
            } else {
                std::cout << resultado;
            }

        } else if (opcao == 3) {

            telaOrdenarPreco(catalogo);

        } else if (opcao == 4) {

            int id = lerOpcao("ID do produto: ");
            std::string desc =
                catalogo.exibirDescricao(id);

            if (desc.empty()) {
                exibirErro("Produto nao encontrado.");
            } else {
                std::cout << desc << "\n";
            }
        }

    } while (opcao != 0);
}

void UI::telaBusca(Catalogo& catalogo) {

    std::string palavra = lerTexto("Palavra-chave: ");
    std::string resultado = catalogo.buscarItem(palavra);

    if (resultado.empty()) {
        exibirErro("Nenhum produto encontrado.");
    } else {
        std::cout << resultado;
    }
}

void UI::telaOrdenarPreco(Catalogo& catalogo) {

    int opcao = lerOpcao("1 - Crescente  2 - Decrescente: ");
    std::cout << catalogo.ordenarPreco(opcao == 1);
}

// ── Carrinho ─────────────────────────────────────────

void UI::telaCarrinho(Carrinho& carrinho) {

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
                  << produtos[i].getPreco() *
                     quantidades[i]
                  << "\n";
    }

    imprimirSeparador();
    std::cout << "Subtotal: R$ "
              << carrinho.calcularSubtotal() << "\n";
    std::cout << "Frete:    R$ "
              << carrinho.getValorFrete()    << "\n";
    std::cout << "Total:    R$ "
              << carrinho.getValorTotal()    << "\n";
}

void UI::telaCheckout(Carrinho& carrinho,
                      Cliente& cliente) {

    imprimirTitulo("FINALIZAR COMPRA");

    Pedido pedido(carrinho, cliente);

    std::cout << pedido.gerarResumoFaturamento(
        cliente, carrinho);

    std::cout << pedido.informarValorFrete(
        cliente.getEndereco()) << "\n";

    std::cout << pedido.estimarDataEntrega(
        cliente.getEndereco()) << "\n";

    std::cout << "1 - Pix  2 - Credito  3 - Debito\n";

    int opcao = lerOpcao("Forma de pagamento: ");

    Pedido::MetodoPagamento metodo =
        Pedido::MetodoPagamento::Pix;

    if (opcao == 2) {
        metodo = Pedido::MetodoPagamento::Credito;
    } else if (opcao == 3) {
        metodo = Pedido::MetodoPagamento::Debito;
    }

    std::cout << pedido.processarPagamentos(metodo) << "\n";

    if (pedido.salvarEmArquivo(cliente)) {
        exibirSucesso("Pedido salvo com sucesso!");
        carrinho.limparCarrinho();
    } else {
        exibirErro("Falha ao salvar o pedido.");
    }
}

// ── Estoque (admin) ──────────────────────────────────

void UI::telaEstoque(Estoque& estoque) {

    imprimirTitulo("GERENCIAR ESTOQUE");

    std::cout << estoque.exibirQuantidadeDisponiveis();

    imprimirSeparador();

    std::string alertas = estoque.alertarEstoqueCritico();

    if (!alertas.empty()) {
        std::cout << alertas;
    }
}

// ── Menus de acesso ──────────────────────────────────

void UI::exibirMenuCliente(Carrinho& carrinho,
                            Catalogo& catalogo,
                            Cliente& cliente) {
    int opcao;

    do {
        imprimirTitulo("MENU CLIENTE");
        std::cout << "1 - Catalogo\n";
        std::cout << "2 - Meu carrinho\n";
        std::cout << "3 - Finalizar compra\n";
        std::cout << "0 - Sair\n";

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

void UI::exibirMenuAdministrador(Catalogo& catalogo,
                                  Estoque& estoque) {
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
        }

    } while (opcao != 0);
}