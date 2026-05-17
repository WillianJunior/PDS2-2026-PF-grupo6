#ifndef PEDIDO_HPP
#define PEDIDO_HPP
#include <string>
class Cliente;
class Carrinho;

/**
 * @class Pedido
 * @brief Representa o processamento final de uma compra no sistema.
 */
class Pedido{
  public:
  enum class MetodoPagamento {
    Pix,
    Credito,
    Debito
  };
    public:
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
     * @brief Este construtor extrai as informacoes de produtos, quantidades e valores 
     * diretamente do carrinho, associa ao cliente responsavel e define o 
     * status inicial como "Pendente".
     * 
     * @param carrinho Referencia constante para o carrinho contendo os produtos.
     * O uso de const garante que os dados do carrinho nao sejam alterados na criacao do pedido.
     * @param cliente Referencia constante para o cliente que esta realizando o pedido.
     * O uso de const garante a integridade dos dados do cliente durante a inicializacao.
     */
    Pedido(const Carrinho& carrinho, const Cliente& cliente);
   
    /**
     * @brief Calcula e informa o valor de frete para o pedido;
     * @param endereco Endereco de entrega
     */
    void informarValorFrete(std::string endereco);
    /**
     * @brief Estima a data de entrega de acordo com a localizacao do cliente.
     * @param endereco Endereco de entrega
     * @return String com a data ou prazo estimado.
     */
    std::string estimarDataEntrega(std::string endereco);
    /**
    * @brief Processa pagamento via Pix, cartao de credito ou debito.
    * @param metodo metodo enum indicando o metodo de pagamento escolhido (Pix, crédito, débito)
    */
    void processarPagamentos(MetodoPagamento metodo);

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
    void gerenciarStatus(StatusPedido novoStatus);

    /**
     * @brief Exibe mensagem de confirmacao de pagamento.
     */
    void exibirMensagemConfirmacao();

     /**
     * @brief Retorna o status do pedido. O metodo é const para garantir que a consulta ao status nao modifique nenhum atributo da classe.
     * @return String contendo o status.
     */
    StatusPedido getStatus()const {return _status;}

      /**
     * @brief Retorna o valor total do pedido. O uso de const assegura que este metodo funcione apenas como um seletor (getter), sem risco de alterar o valor do pedido.
     * @return Double contendo o valor total (produtos + frete).
     */
    double getvalorTotal() const {return _valorTotal;}


};
#endif


