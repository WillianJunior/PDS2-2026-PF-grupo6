#include "Pedido.hpp"
#include "Cliente.hpp"
#include "Carrinho.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cassert>

Pedido::Pedido(const Carrinho& carrinho, const Cliente& cliente) {
    if (carrinho.calcularSubtotal() <= 0.0) {
        throw std::invalid_argument("Erro: Nao eh possivel gerar um pedido com carrinho vazio ou valor zerado.");
    }
    if (cliente.getCpf().empty() || cliente.getEndereco().empty()) {
        throw std::invalid_argument("Erro: Dados do cliente (CPF ou Endereco) estao incompletos.");
    }

    _status = StatusPedido::Pendente;
    _frete = carrinho.getValorFrete();
    _valorTotal = 0.0;
    
    if (_frete < 0.0) {
        throw std::runtime_error("Erro critico: Valor de frete calculado eh negativo.");
    }

    gerarResumoFaturamento(carrinho);
}

void Pedido::informarValorFrete(const std::string& endereco) {
    if (endereco.empty()) {
        throw std::invalid_argument("Erro: O endereco informado nao pode ser vazio.");
    }
    std::cout << "O valor do frete para '" << endereco << "' é: R$ " << _frete << "\n";
}

std::string Pedido::estimarDataEntrega(const std::string& endereco) {
    if (endereco.empty()) {
        throw std::invalid_argument("Erro: Endereco invalido para estimativa de entrega.");
    }

    if (endereco.find("MG") != std::string::npos || endereco.find("Belo Horizonte") != std::string::npos) {
        return "Prazo estimado: 2 a 3 dias úteis, a partir da confirmação de pagamento";
    }
    return "Prazo estimado: 7 a 10 dias úteis, a partir da confirmação de pagamento.";
}

void Pedido::processarPagamentos(MetodoPagamento metodo) {
    if (_status == StatusPedido::Pago) {
        throw std::runtime_error("Erro: Este pedido ja foi pago e processado.");
    }

     if (_valorTotal <= 0.0) {
        throw std::runtime_error("Erro: Tentativa de pagar um pedido com valor zerado ou nao calculado.");
    }

    if (metodo == MetodoPagamento::Pix) {
        std::cout << "AGUARDANDO PAGAMENTO PIX\n";
        std::cout << "PIX: " << _valorTotal << "\n";
        gerenciarStatus(StatusPedido::Pago);
        exibirMensagemConfirmacao();
    } else if (metodo == MetodoPagamento::Credito || metodo == MetodoPagamento::Debito) {
        std::cout << "PROCESSANDO CARTÃO\n";
        std::cout << "Cobrança de R$ " << _valorTotal << "\n";
        gerenciarStatus(StatusPedido::Pago);
        exibirMensagemConfirmacao();
    } else {
        throw std::invalid_argument("Erro: Metodo de pagamento nao reconhecido.");
    }
}

void Pedido::gerarResumoFaturamento(const Carrinho& carrinho) {
    double subtotal = carrinho.calcularSubtotal();
    _valorTotal = carrinho.calcularTotal();

    assert(subtotal >= 0.0);
    assert(_valorTotal >= subtotal);

    std::cout << "Subtotal: R$ " << subtotal << "\n";
    std::cout << "Frete: R$ " << _frete << "\n";
    std::cout << "Total: R$ " << _valorTotal << "\n";
}

void Pedido::gerenciarStatus(StatusPedido novoStatus) {
    _status = novoStatus;
    switch (_status) {
        case StatusPedido::Pendente: std::cout << "Status: Pendente\n"; break;
        case StatusPedido::Pago:     std::cout << "Status: Pago\n";     break;
        case StatusPedido::Enviado:  std::cout << "Status: Enviado\n";  break;
        case StatusPedido::Entregue: std::cout << "Status: Entregue\n"; break;
        default: 
            throw std::runtime_error("Erro: Status de pedido indefinido detectado.");
    }
}

void Pedido::exibirMensagemConfirmacao() {
    if (_status == StatusPedido::Pago) {
        std::cout << "Pagamento confirmado!\n";
    } else {
        std::cout << "Aguardando pagamento.\n";
    }
}

void Pedido::salvarEmArquivo(const Cliente& cliente) {
    if (cliente.getCpf().empty()) {
        throw std::invalid_argument("Erro: Nao eh possivel salvar o arquivo sem o CPF do cliente.");
    }

    std::string nomeArquivo = "pedido_" + cliente.getCpf() + ".txt";

    std::ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro: Nao foi possivel abrir/criar o arquivo de historico do pedido: " + nomeArquivo);
    }

    arquivo << "=== RESUMO DO PEDIDO ===\n";
    arquivo << "CPF do Cliente: " << cliente.getCpf() << "\n";
    arquivo << "Endereco: " << cliente.getEndereco() << "\n";
    arquivo << "------------------------\n";
    arquivo << "VALORES:\n";
    arquivo << "Frete: R$ " << _frete << "\n";
    arquivo << "Total Pago: R$ " << _valorTotal << "\n";
    arquivo << "------------------------\n";
    arquivo << "STATUS E LOGÍSTICA:\n";
    
    arquivo << "Status Atual: ";
    switch (_status) {
        case StatusPedido::Pendente: arquivo << "Pendente\n"; break;
        case StatusPedido::Pago:     arquivo << "Pago\n";     break;
        case StatusPedido::Enviado:  arquivo << "Enviado\n";  break;
        case StatusPedido::Entregue: arquivo << "Entregue\n"; break;
    }
    
    arquivo << estimarDataEntrega(cliente.getEndereco()) << "\n";
    arquivo << "========================\n";

    arquivo.close(); 
    std::cout << "Pedido salvo com sucesso em: " << nomeArquivo << "\n";    // 
}