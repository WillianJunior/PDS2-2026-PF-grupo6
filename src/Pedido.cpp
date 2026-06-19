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

    _status = StatusPedido::Pendente;
    _frete  = carrinho.getValorFrete();

    double subtotal       = carrinho.calcularSubtotal();
    double totalCalculado = carrinho.calcularTotal();

    if (subtotal < 0.0 || totalCalculado < subtotal) {
        throw std::runtime_error(
            "Erro critico: inconsistencia detectada "
            "nos valores do carrinho.");
    }

    _valorTotal = totalCalculado;
}


std::string Pedido::informarValorFrete(
        const std::string& endereco) {

    return "O valor do frete para '" +
           endereco + "' e: R$ " +
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

    } else {
    
        throw std::invalid_argument(
            "Metodo de pagamento invalido.");
    }

    resultado += exibirMensagemConfirmacao();

    return resultado;
}


std::string Pedido::gerarResumoFaturamento(
        const Cliente& cliente,
        const Carrinho& carrinho) {

    double subtotal = carrinho.calcularSubtotal();

    std::ostringstream oss;
    oss << "Subtotal: R$ " << formatarValor(subtotal)    << "\n"
        << "Frete: R$ "    << formatarValor(_frete)      << "\n"
        << "Total: R$ "    << formatarValor(_valorTotal) << "\n";

    return oss.str();
}

void Pedido::gerenciarStatus(
        StatusPedido novoStatus) {

    _status = novoStatus;
}

std::string Pedido::exibirMensagemConfirmacao() {

    if (_status == StatusPedido::Pago) {
        return "Pagamento confirmado!\n";
    }

    return "Aguardando pagamento.\n";
}


void Pedido::salvarEmArquivo(
        const Cliente& cliente) {

    if (cliente.getCpf().empty() ||
        cliente.getEndereco().empty()) {

        throw std::invalid_argument(
            "Nao e possivel salvar pedido com "
            "dados de cliente incompletos.");
    }

    std::string nomeArquivo =
        "pedido_" + cliente.getCpf() + ".txt";

    std::ofstream arquivo(
        nomeArquivo, std::ios::app);

    if (!arquivo.is_open()) {
        throw std::runtime_error(
            "Nao foi possivel abrir o arquivo: " +
            nomeArquivo);
    }


    arquivo << "=== RESUMO DO PEDIDO ===\n";
    arquivo << "CPF do Cliente: " << cliente.getCpf()      << "\n";
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

    arquivo << estimarDataEntrega(
        cliente.getEndereco()) << "\n";

    arquivo << "========================\n\n";
}