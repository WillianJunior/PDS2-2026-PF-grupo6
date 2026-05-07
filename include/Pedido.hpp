#ifndef PEDIDO_HPP
#define PEDIDO_HPP
#include <string>
#include "Carrinho.hpp"
#include "Cliente.hpp"
/**
 * @class Pedido
 * @brief Representa o processamento final de uma compra no sistema.
 */
class Pedido
{
private:
std::string status;
double valorFrete;
double valorTotal;
  
public:
     /**
     * @brief Construtor da classe Pedido.
     * @param carrinho Referência ao carrinho contendo os itens.
     * @param cliente Referência ao cliente que realizou o pedido.
     */
   
    Pedido(const Carrinho& carrinho, const Cliente& cliente);
     /**
     * @brief Destrutor do pedido
     */
    ~Pedido(); 
    /**
     * @brief Calcula e informa o valor de frete para o pedido;
     * @param endereco Endereço de entrega
     */
    void informarValorFrete(std::string endereco);
    /**
     * @brief Estima a data de entrega de acordo com a localização do cliente.
     * @param endereco Endereço de entrega
     * @return String com a data ou prazo estimado.
     */
    std::string estimarDataEntrega(std::string endereco);
    /**
    * @brief Processa pagamento via Pix, cartão de crédito ou débito.
    * @param metodo string indicando o método de pagamento escolhido (Pix, crédito, débito
    */
    void processarPagamentos(std::string metodo);

    /**
     * @brief Gera o resumo de faturamento, calcula o valor total.
     * @param cliente Cliente do pedido
     * @param carrinho Carrinho com os produtos para somatória de valores.
     */
    void gerarResumoFaturamento(const Cliente& cliente, const Carrinho& carrinho);

    /**
     * @brief Gerencia o fluxo de mudança do status do pedido(Pendente, pago, enviado e entregue).
     * @param novoStatus O novo estado do pedido.
     */
    void gerenciarStatus(std::string novoStatus);

    /**
     * @brief Exibe mensagem de confirção de pagamento.
     */
    void exibirMensagemConfirmacao();

     /**
     * @brief Retorna o status do pedido
     */
    std::string getStatus()const {return status;}

      /**
     * @brief Retorna o valor total do pedido
     */
    double getvalorTotal() const {return valorTotal;}


};
#endif


