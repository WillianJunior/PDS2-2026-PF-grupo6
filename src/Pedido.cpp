#include "Pedido.hpp"
//#include "Cliente.hpp"
//#include "Carrinho.hpp"
#include <iostream>
#include <fstream>

Pedido::Pedido(const Carrinho& carrinho, const Cliente& cliente){
    _status = StatusPedido::Pendente;
    _frete = carrinho.getValorFrete();
    _valorTotal = 0.0;
    gerarResumoFaturamento(cliente, carrinho);
}

void Pedido::informarValorFrete(const std::string& endereco) {
    std::cout << "O valor do frete para '" << endereco << "' é: R$ " << _frete << "\n";
}

std::string Pedido::estimarDataEntrega(const std::string& endereco){
    if (endereco.find("MG") != std::string::npos || endereco.find("Belo Horizonte") != std::string::npos)
        return "Prazo estimado: 2 a 3 dias úteis, a partir da confirmação de pagamento";
    return "Prazo estimado: 7 a 10 dias úteis, a partir da confirmação de pagamento.";
}

void Pedido::processarPagamentos(MetodoPagamento metodo){
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
    }
}

void Pedido::gerarResumoFaturamento(const Cliente& cliente, const Carrinho& carrinho) {
    double subtotal = carrinho.calcularSubtotal();
    _valorTotal = carrinho.calcularTotal();
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
    }
}

void Pedido::exibirMensagemConfirmacao(){
    if (_status == StatusPedido::Pago)
        std::cout << "Pagamento confirmado!\n";
    else
        std::cout << "Aguardando pagamento.\n";
}

void Pedido::salvarEmArquivo(const Cliente& cliente) {
    // Define o nome do arquivo utilizando o CPF do cliente
    // (Garante que o arquivo seja único por cliente: ex: "pedido_12345678900.txt")
    std::string nomeArquivo = "pedido_" + cliente.getCpf() + ".txt";
    std::ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao criar o arquivo de histórico do pedido!\n";
        return;
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
    std::cout << "Pedido salvo com sucesso em: " << nomeArquivo << "\n";
}
