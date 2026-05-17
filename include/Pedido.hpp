#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <string>
#include "Cliente.hpp" // Include para poder usar o enum FormadePagamento.

class Carrinho;

/**
 * @brief Categorias fixas para o fluxo do pedido.
 * Substitui a string _status para evitar erros de digitação!
 */
enum StatusPedido {
    PENDENTE,
    PAGO,
    ENVIADO,
    ENTREGUE
};

/**
 * @class Pedido
 * @brief Representa o processamento final de uma compra no sistema.
 */
class Pedido{
private:
    StatusPedido _status; // Atualizado de std::string para o novo Enum
    double _valorFrete;
    double _valorTotal;
  
public:
     /** * @brief Este construtor extrai as informacoes de produtos, quantidades e valores 
     * diretamente do carrinho, associa ao cliente responsavel e define o 
     * status inicial como "Pendente".
     * * @param carrinho Referencia constante para o carrinho contendo os produtos.
     * O uso de const garante que os dados do carrinho nao sejam alterados na criacao do pedido.
     * @param cliente Referencia constante para o cliente que esta realizando o pedido.
     * O uso de const garante a integridade dos dados do cliente durante a inicializacao.
     */
    Pedido(const Carrinho& carrinho, const Cliente& cliente);
   
    /**
     * @brief Calcula e informa o valor de frete para o pedido;
     * @param endereco Endereço de entrega
     */
    // Passando endereco por const & para economizar memória!
    void informarValorFrete(const std::string& endereco);

    /**
     * @brief Estima a data de entrega de acordo com a localizacao do cliente.
     * @param endereco Endereço de entrega
     * @return String com a data ou prazo estimado.
     */

    std::string estimarDataEntrega(const std::string& endereco) const;

    /**
    * @brief Processa pagamento via Pix, cartao de credito ou debito.
    * @param metodo Enum indicando o metodo de pagamento escolhido.
    */
  
    void processarPagamentos(FormaPagamento metodo);

    /**
     * @brief Gera o resumo de faturamento, calcula o valor total.
     * @param cliente Cliente do pedido
     * @param carrinho Carrinho com os produtos para somatoria de valores.
     */
    void gerarResumoFaturamento(const Cliente& cliente, const Carrinho& carrinho);

    /**
     * @brief Gerencia o fluxo de mudança do status do pedido(Pendente, pago, enviado e entregue).
     * @param novoStatus O novo estado do pedido.
     */
    // Trocado de string para o Enum StatusPedido!
    void gerenciarStatus(StatusPedido novoStatus);

    /**
     * @brief Exibe mensagem de confirmacao de pagamento.
     */
    // Adicionado 'const' no final porque exibir na tela não altera as variáveis da classe.
    void exibirMensagemConfirmacao() const;

     /**
     * @brief Retorna o status do pedido. O metodo é const para garantir que a consulta ao status nao modifique nenhum atributo da classe.
     * @return Enum contendo o status.
     */
    StatusPedido getStatus() const { return _status; }

      /**
     * @brief Retorna o valor total do pedido. O uso de const assegura que este metodo funcione apenas como um seletor (getter), sem risco de alterar o valor do pedido.
     * @return Double contendo o valor total (produtos + frete).
     */
    double getValorTotal() const { return _valorTotal; }

};
#endif