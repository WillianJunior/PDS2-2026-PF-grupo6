#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>

/**
 * @brief Acessar dados cadastrais e informações relacionadas às compras.
 */

class cliente : public usuario {

private:

    std::string cpf;
    std:: vector <std::string> string endereco;
    std:: vector <std::string> string metodosPagamento;

public:

    cliente(std::string nome, std::string email, std::string senha);
    
/**
 * @brief Validar as condições do cpf.
 * @return Retorna verdadeiro se condição do cpf válida, retorna falso se condição do cpf inválido.
 */ 
    bool validarCpf();
    
/**
 * @brief Gerenciar o cadastramento ou remoção de endereços.
 */    
    void gerenciarEndereco();
    
/**
 * @brief Gerenciar o cadastramento ou remoção de métodos de pagamento.
 */    
    void gerenciarMetodoPagamento();
    
/**
 * @brief Gerenciar a inclusão ou remoção de produtos do carrinho.
 */    
    void gerenciarCarrinho();
 
/**
 * @brief Consulta ao histórico pessoal de compras.
 */    
    void visualizarHistorico();

};

#endif