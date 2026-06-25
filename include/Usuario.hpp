#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

/**
 * @class Usuario
 * @brief Classe base responsável pelos dados e operações comuns dos usuários.
 *
 * A classe Usuario armazena nome, email, senha, tipo de usuário e resposta
 * de segurança. Também fornece funcionalidades de autenticação, cadastro,
 * recuperação de senha e alteração de dados persistidos em arquivo.
 */
class Usuario {
protected:
    std::string _nome;
    std::string _email;
    std::string _senha;
    std::string _tipo;
    std::string _respostaSeguranca;

public:

    virtual ~Usuario() = default;
    virtual void exibirPerfil() const;

    /**
     * @brief Construtor da classe Usuario.
     *
     * @param nome Nome do usuário.
     * @param email Email do usuário.
     * @param senha Senha do usuário.
     * @param tipo Tipo do usuário ("cliente" ou "administrador").
     * @param respostaSeguranca Resposta da pergunta de segurança.
     *
     * @throw std::invalid_argument Caso algum dado seja inválido.
     */
    Usuario(std::string nome,
            std::string email,
            std::string senha,
            std::string tipo,
            std::string respostaSeguranca);

    /**
     * @brief Valida o formato de um email.
     *
     * @param novoEmail Email a ser validado.
     * @return true se o email for válido.
     */
    bool validarEmail(std::string novoEmail) const;

    /**
     * @brief Valida uma senha.
     *
     * @param novaSenha Senha a ser validada.
     * @return true se a senha possuir pelo menos 6 caracteres.
     */
    bool gerenciarSenha(std::string novaSenha) const;

    /**
     * @brief Altera apenas o nome armazenado em memória.
     *
     * @param novoNome Novo nome.
     *
     * @throw std::invalid_argument Caso o nome seja inválido.
     */
    void armazenarNome(std::string novoNome);

    /**
     * @brief Altera o nome do usuário e atualiza o arquivo.
     *
     * @param novoNome Novo nome.
     * @param nomeArquivo Arquivo de usuários.
     *
     * @throw std::invalid_argument Caso o nome seja inválido.
     * @throw std::runtime_error Caso ocorra erro no arquivo.
     */
    void alterarNome(
        std::string novoNome,
        const std::string& nomeArquivo = "usuarios.txt");

    /**
     * @brief Altera o email do usuário e atualiza o arquivo.
     *
     * @param novoEmail Novo email.
     * @param nomeArquivo Arquivo de usuários.
     *
     * @throw std::invalid_argument Caso o email seja inválido.
     * @throw std::runtime_error Caso ocorra erro no arquivo.
     */
    void alterarEmail(
        std::string novoEmail,
        const std::string& nomeArquivo = "usuarios.txt");

    /**
     * @brief Altera a senha do usuário logado e atualiza o arquivo.
     *
     * Não utiliza resposta de segurança.
     * A resposta de segurança é usada apenas em recuperarSenha().
     *
     * @param novaSenha Nova senha.
     * @param nomeArquivo Arquivo de usuários.
     *
     * @throw std::invalid_argument Caso a senha seja inválida.
     * @throw std::runtime_error Caso ocorra erro no arquivo.
     */
    void alterarSenha(
        std::string novaSenha,
        const std::string& nomeArquivo = "usuarios.txt");

    /**
     * @brief Verifica se o usuário pode alterar seus dados.
     *
     * @return true se a alteração for permitida.
     */
    bool permitirAlteracaoDados() const;

    /**
     * @brief Retorna o nome do usuário.
     */
    const std::string& getNome() const;

    /**
     * @brief Retorna o email do usuário.
     */
    const std::string& getEmail() const;

    /**
     * @brief Retorna a senha do usuário.
     */
    const std::string& getSenha() const;

    /**
     * @brief Retorna o tipo do usuário.
     */
    const std::string& getTipo() const;

    /**
     * @brief Retorna a resposta de segurança.
     */
    const std::string& getRespostaSeguranca() const;

    /**
     * @brief Autentica um usuário em memória.
     *
     * @param email Email informado.
     * @param senha Senha informada.
     *
     * @return true se email e senha coincidirem.
     */
    bool autenticar(
        std::string email,
        std::string senha) const;

    /**
     * @brief Retorna a pergunta fixa de segurança.
     *
     * @return Pergunta de segurança.
     */
    static std::string getPerguntaSeguranca();

    /**
     * @brief Verifica se um email já está cadastrado.
     *
     * @param email Email procurado.
     * @param nomeArquivo Arquivo de usuários.
     *
     * @return true se o email existir.
     *
     * @throw std::runtime_error Caso existam dados inválidos no arquivo.
     */
    static bool emailJaCadastrado(
        const std::string& email,
        const std::string& nomeArquivo = "usuarios.txt");

    /**
     * @brief Realiza login utilizando os dados do arquivo.
     *
     * @param email Email informado.
     * @param senha Senha informada.
     * @param nomeArquivo Arquivo de usuários.
     *
     * @return Tipo do usuário encontrado ou "invalido".
     *
     * @throw std::runtime_error Caso ocorra erro de leitura.
     */
    static std::string fazerLogin(
        const std::string& email,
        const std::string& senha,
        const std::string& nomeArquivo = "usuarios.txt");

    /**
     * @brief Salva um novo usuário no arquivo.
     *
     * @param tipo Tipo do usuário.
     * @param nome Nome do usuário.
     * @param email Email do usuário.
     * @param senha Senha do usuário.
     * @param cpf CPF do usuário.
     * @param respostaSeguranca Resposta da pergunta de segurança.
     * @param endereco Endereço do cliente (adicionado para a 7a coluna)
     * @param nomeArquivo Arquivo de usuários.
     *
     * @return true se o usuário for salvo.
     * @return false se o email já estiver cadastrado.
     *
     * @throw std::invalid_argument Caso algum dado seja inválido.
     * @throw std::runtime_error Caso ocorra erro de arquivo.
     */
    static bool salvarUsuario(
        const std::string& tipo,
        const std::string& nome,
        const std::string& email,
        const std::string& senha,
        const std::string& cpf,
        const std::string& respostaSeguranca,
        const std::string& endereco = "", // ADICIONADO AQUI
        const std::string& nomeArquivo = "usuarios.txt");

    /**
     * @brief Recupera a senha usando email e resposta de segurança.
     *
     * @param email Email do usuário.
     * @param respostaSeguranca Resposta informada.
     * @param novaSenha Nova senha.
     * @param nomeArquivo Arquivo de usuários.
     *
     * @return true se a senha for alterada.
     * @return false caso email ou resposta não coincidam.
     *
     * @throw std::invalid_argument Caso algum dado seja inválido.
     * @throw std::runtime_error Caso ocorra erro de arquivo.
     */
    static bool recuperarSenha(
        const std::string& email,
        const std::string& respostaSeguranca,
        const std::string& novaSenha,
        const std::string& nomeArquivo = "usuarios.txt");
};

#endif