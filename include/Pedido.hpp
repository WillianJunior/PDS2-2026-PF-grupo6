#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <string>

class Cliente;
class Carrinho;

/**
 * @class Pedido
 * @brief Representa o processamento final de uma compra no sistema.
 */
class Pedido {
public:
    enum class MetodoPagamento {
        Pix,
        Credito,
        Debito
    };

    enum class StatusPedido {
        Pendente,
        Pago,
        Enviado,
        Entregue
    };

private:
    StatusPedido _status;
    double _frete;
    double _valorTotal;

public:
    /**
     * @brief Inicializa o pedido a partir do carrinho e cliente.
     * @throws std::runtime_error se os valores do carrinho forem inconsistentes.
     */
    Pedido(const Carrinho& carrinho,
           const Cliente& cliente);

    /**
     * @brief Retorna o valor do frete formatado.
     * @return String para exibição pela UI.
     */
    std::string informarValorFrete(
        const std::string& endereco);

    /**
     * @brief Estima prazo de entrega pelo endereço.
     * @return String com o prazo estimado.
     */
    std::string estimarDataEntrega(
        const std::string& endereco);

    /**
     * @brief Processa pagamento e retorna resultado para a UI.
     * @throws std::invalid_argument se o método for inválido.
     * @return String com o resultado do pagamento.
     */
    std::string processarPagamentos(
        MetodoPagamento metodo);

    /**
     * @brief Retorna o resumo de faturamento para a UI exibir.
     * @return String com subtotal, frete e total.
     */
    std::string gerarResumoFaturamento(
        const Cliente& cliente,
        const Carrinho& carrinho);

    /**
     * @brief Atualiza o status do pedido.
     */
    void gerenciarStatus(StatusPedido novoStatus);

    /**
     * @brief Retorna mensagem de confirmação para a UI exibir.
     * @return String com a mensagem.
     */
    std::string exibirMensagemConfirmacao();

    /**
     * @brief Salva o resumo do pedido em arquivo histórico.
     * @throws std::invalid_argument se dados do cliente estiverem incompletos.
     * @throws std::runtime_error se o arquivo não puder ser aberto.
     */
    void salvarEmArquivo(const Cliente& cliente, const Carrinho& carrinho);

    StatusPedido getStatus()    const { return _status;     }
    double getValorTotal()      const { return _valorTotal; }
    double getValorFrete()      const { return _frete;      }
};

#endif