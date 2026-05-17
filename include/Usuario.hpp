#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

/**
 * @brief Entidade base do sistema para identificação e controle de acesso.
 * Centraliza as regras de segurança da conta compartilhadas por clientes e administradores.
 */
class Usuario {
protected:
    /**
    * @brief Usamos protected para que Cliente e Administrador consigam herdar e acessar essas variáveis
    */
    std::string _nome;
    std::string _email;
    std::string _senha;

public:
    /**
     * @brief Inicializa as credenciais básicas do usuário na memória.
     */
    Usuario(std::string nome, std::string email, std::string senha);

    /**
     * @brief Verifica a integridade do e-mail (ex: presença de '@').
     * É const pois não altera o usuário, apenas faz uma checagem de leitura.
     */
    bool validarEmail(std::string novoEmail) const;

    /**
     * @brief Avalia se a senha atinge a política de segurança do E-commerce.
     */
    bool gerenciarSenha(std::string novaSenha) const;
    
    void armazenarNome(std::string novoNome);
    void atualizarDadosPerfil();
    void gerenciarRecuperacaoAcesso();
    bool permitirAlteracaoDados() const;
};

#endif // USUARIO_HPP