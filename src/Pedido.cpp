#include "Pedido.hpp"
#include "Cliente.hpp"
#include "Carrinho.hpp"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

static std::string formatarValor(double valor) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << valor;
    return oss.str();
}

Pedido::Pedido(const Carrinho& carrinho,
               const Cliente& cliente) {

  if (!cliente.validarCpf()) {
    throw std::invalid_argument(
        "CPF do cliente invalido.");
}

    _status = StatusPedido::Pendente;
    _frete  = carrinho.getValorFrete();

    if (carrinho.getProdutos().empty()) {
    throw std::runtime_error(
        "Nao e possivel criar pedido sem produtos.");
}

    if (_frete < 0.0) {
        throw std::runtime_error(
            "Valor de frete invalido.");
    }

    double subtotal       = carrinho.calcularSubtotal();
    double totalCalculado = carrinho.calcularTotal();

    if (subtotal < 0.0) {
        throw std::runtime_error(
            "Subtotal invalido.");
    }

    if (totalCalculado < subtotal) {
        throw std::runtime_error(
            "Total inconsistente.");
    }

    _valorTotal = totalCalculado;
}

std::string Pedido::informarValorFrete(
        const std::string& endereco) {

    if (endereco.empty()) {
        throw std::invalid_argument(
            "Endereco nao pode ser vazio.");
    }

    return "O valor do frete para '" +
           endereco + "' e: R$ " +
           formatarValor(_frete);
}

std::string Pedido::estimarDataEntrega(
        const std::string& endereco) {

    if (endereco.empty()) {
        throw std::invalid_argument(
            "Endereco invalido.");
    }

    if (endereco.find("MG") != std::string::npos ||
        endereco.find("Belo Horizonte") != std::string::npos) {

        return "Prazo estimado: 2 a 3 dias uteis, "
               "a partir da confirmacao de pagamento";
    }

    return "Prazo estimado: 7 a 10 dias uteis, "
           "a partir da confirmacao de pagamento.";
}

std::string Pedido::processarPagamentos(
        MetodoPagamento metodo) {

    if (_status != StatusPedido::Pendente) {
    throw std::runtime_error(
        "Pagamento nao permitido para este status.");
}

    if (_valorTotal < 0.0) {
        throw std::runtime_error(
            "Valor total invalido.");
    }

    std::string resultado;

    if (metodo == MetodoPagamento::Pix) {

        resultado = "AGUARDANDO PAGAMENTO PIX\n"
                    "PIX: R$ " +
                    formatarValor(_valorTotal) + "\n";

        gerenciarStatus(StatusPedido::Pago);

    } else if (metodo == MetodoPagamento::Credito ||
               metodo == MetodoPagamento::Debito) {

        resultado = "PROCESSANDO CARTAO\n"
                    "Cobranca de R$ " +
                    formatarValor(_valorTotal) + "\n";

        gerenciarStatus(StatusPedido::Pago);

    } else {

        throw std::invalid_argument(
            "Metodo de pagamento invalido.");
    }

    resultado += exibirMensagemConfirmacao();

    return resultado;
}

std::string Pedido::gerarResumoFaturamento(
        const Cliente&,
        const Carrinho& carrinho) {

    double subtotal = carrinho.calcularSubtotal();

    std::ostringstream oss;

    oss << "Subtotal: R$ "
        << formatarValor(subtotal)
        << "\n";

    oss << "Frete: R$ "
        << formatarValor(_frete)
        << "\n";

    oss << "Total: R$ "
        << formatarValor(_valorTotal)
        << "\n";

    return oss.str();
}

void Pedido::gerenciarStatus(
        StatusPedido novoStatus) {

    switch (novoStatus) {

        case StatusPedido::Pendente:
        case StatusPedido::Pago:
        case StatusPedido::Enviado:
        case StatusPedido::Entregue:
            _status = novoStatus;
            break;

        default:
            throw std::invalid_argument(
                "Status invalido.");
    }
}

std::string Pedido::exibirMensagemConfirmacao() {

    if (_status == StatusPedido::Pago) {
        return "Pagamento confirmado!\n";
    }

    return "Aguardando pagamento.\n";
}


void Pedido::salvarEmArquivo(const Cliente& cliente, const Carrinho& carrinho) {

    if (cliente.getCpf().empty()) {
        throw std::invalid_argument(
            "CPF do cliente invalido.");
    }

    if (_valorTotal < 0.0) {
        throw std::runtime_error(
            "Pedido invalido.");
    }

    const auto& produtos =
        carrinho.getProdutos();

    const auto& quantidades =
        carrinho.getQuantidades();

    if (produtos.empty()) {
        throw std::runtime_error(
            "Nao e possivel salvar um pedido vazio.");
    }

    if (produtos.size() !=
        quantidades.size()) {

        throw std::runtime_error(
            "Inconsistencia entre produtos e quantidades.");
    }

    std::string nomeArquivo =
        "pedido_" + cliente.getCpf() + ".txt";

    std::ofstream arquivo(
        nomeArquivo,
        std::ios::app);

    if (!arquivo.is_open()) {
        throw std::runtime_error(
            "Nao foi possivel abrir o arquivo: " +
            nomeArquivo);
    }

    arquivo << "====================================\n";
    arquivo << "RESUMO DO PEDIDO\n";
    arquivo << "====================================\n";

    arquivo << "CPF do Cliente: "
            << cliente.getCpf()
            << "\n";

    arquivo << "Endereco: "
            << cliente.getEndereco()
            << "\n\n";

    arquivo << "ITENS DO PEDIDO\n";
    arquivo << "------------------------------------\n";

    double subtotalCalculado = 0.0;

    for (size_t i = 0;
         i < produtos.size();
         i++) {

        if (produtos[i].getId() <= 0) {
            throw std::runtime_error(
                "Produto invalido encontrado no pedido.");
        }

        if (produtos[i].getPreco() < 0.0) {
            throw std::runtime_error(
                "Preco invalido encontrado no pedido.");
        }

        if (quantidades[i] <= 0) {
            throw std::runtime_error(
                "Quantidade invalida encontrada no pedido.");
        }

        double subtotalItem =
            produtos[i].getPreco() *
            quantidades[i];

        subtotalCalculado +=
            subtotalItem;

        arquivo << "Produto: "
                << produtos[i].getNome()
                << "\n";

        arquivo << "ID: "
                << produtos[i].getId()
                << "\n";

        arquivo << "Quantidade: "
                << quantidades[i]
                << "\n";

        arquivo << "Preco Unitario: R$ "
                << formatarValor(
                       produtos[i].getPreco())
                << "\n";

        arquivo << "Subtotal Item: R$ "
                << formatarValor(
                       subtotalItem)
                << "\n";

        arquivo << "------------------------------------\n";
    }

    if (subtotalCalculado < 0.0) {
    throw std::runtime_error(
        "Subtotal calculado invalido.");
}

    arquivo << "\nVALORES\n";

    arquivo << "Subtotal: R$ "
            << formatarValor(
                   subtotalCalculado)
            << "\n";

    arquivo << "Frete: R$ "
            << formatarValor(_frete)
            << "\n";

    arquivo << "Total Pago: R$ "
            << formatarValor(
                   _valorTotal)
            << "\n\n";

    arquivo << "STATUS E LOGISTICA\n";

    arquivo << "Status Atual: ";

    switch (_status) {

        case StatusPedido::Pendente:
            arquivo << "Pendente\n";
            break;

        case StatusPedido::Pago:
            arquivo << "Pago\n";
            break;

        case StatusPedido::Enviado:
            arquivo << "Enviado\n";
            break;

        case StatusPedido::Entregue:
            arquivo << "Entregue\n";
            break;
    }

    if (!cliente.getEndereco().empty()) {

        arquivo << estimarDataEntrega(
                       cliente.getEndereco())
                << "\n";
    }

    arquivo << "====================================\n\n";

    if (!arquivo.good()) {
        throw std::runtime_error(
            "Erro ao escrever dados do pedido.");
    }
}