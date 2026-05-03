#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

/**
 * @brief Gerenciar dados do perfil.
 */

class usuario {
protected:

    std::string nome;
    std::string email;
    std::string senha;

public:

    usuario(std::string nome, std::string email, std::string senha);
    ~usuario();

/**
 * @brief Valida as condições do email.
 * @return Retorna verdadeiro se condição de email válida, retorna falso se condição de email inválida.
 */
    bool validarEmail(std::string email);
    
/**
 * @brief Valida as condições da senha.
 * @return Retorna verdadeiro se condição da senha válida, retorna falso se condição da senha inválida.
 */    
    bool validarSenha(std::string senha);

    std::string getNome();
    std::string getEmail();

};

#endif