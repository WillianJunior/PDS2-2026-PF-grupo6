#include "Pedido.hpp"
#include "Cliente.hpp"
#include "Carrinho.hpp"

#include <fstream>
#include <iomanip>
#include <sstream>

static std::string formatarValor(double valor) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << valor;
    return oss.str();
}

Pedido::Pedido(const Carrinho& carrinho,
               const Cliente& cliente) {

    _status = StatusPedido::Pendente;
    _frete = carrinho.getValorFrete();
    _valorTotal = 0.0;

    gerarResumoFaturamento(cliente, carrinho);
}

std::string Pedido::informarValorFrete(
        const std::string& endereco) {

    return "O valor do frete para '" +
           endereco +
           "' e: R$ " +
           formatarValor(_frete);
}

std::string Pedido::estimarDataEntrega(
        const std::string& endereco) {

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
    }

    resultado += exibirMensagemConfirmacao();

    return resultado;
}

std::string Pedido::gerarResumoFaturamento(
        const Cliente& cliente,
        const Carrinho& carrinho) {

    double subtotal = carrinho.calcularSubtotal();

    _valorTotal = carrinho.calcularTotal();

    return "Subtotal: R$ " + formatarValor(subtotal) + "\n" +
           "Frete: R$ "    + formatarValor(_frete)    + "\n" +
           "Total: R$ "    + formatarValor(_valorTotal) + "\n";
}

void Pedido::gerenciarStatus(
        StatusPedido novoStatus) {

    _status = novoStatus;
}

std::string Pedido::exibirMensagemConfirmacao() {

    if (_status == StatusPedido::Pago) {
        return "Pagamento confirmado!";
    }

    return "Aguardando pagamento.";
}

bool Pedido::salvarEmArquivo(
        const Cliente& cliente) {

    std::string nomeArquivo =
        "pedido_" + cliente.getCpf() + ".txt";

    std::ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        return false;
    }

    arquivo << "=== RESUMO DO PEDIDO ===\n";
    arquivo << "CPF do Cliente: " << cliente.getCpf() << "\n";
    arquivo << "Endereco: "       << cliente.getEndereco() << "\n";
    arquivo << "------------------------\n";
    arquivo << "VALORES:\n";
    arquivo << "Frete: R$ "      << formatarValor(_frete)      << "\n";
    arquivo << "Total Pago: R$ " << formatarValor(_valorTotal)  << "\n";
    arquivo << "------------------------\n";
    arquivo << "STATUS E LOGISTICA:\n";

    arquivo << "Status Atual: ";

    switch (_status) {
        case StatusPedido::Pendente:
            arquivo << "Pendente\n"; break;
        case StatusPedido::Pago:
            arquivo << "Pago\n";     break;
        case StatusPedido::Enviado:
            arquivo << "Enviado\n";  break;
        case StatusPedido::Entregue:
            arquivo << "Entregue\n"; break;
    }

    arquivo << estimarDataEntrega(cliente.getEndereco()) << "\n";
    arquivo << "========================\n";

    return true;
}