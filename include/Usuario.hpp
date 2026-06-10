#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

class Usuario {
protected:
    std::string _nome;
    std::string _email;
    std::string _senha;
    std::string _tipo;
    std::string _respostaSeguranca;

public:
    Usuario(std::string nome,
            std::string email,
            std::string senha,
            std::string tipo,
            std::string respostaSeguranca);

    bool validarEmail(std::string novoEmail) const;
    bool gerenciarSenha(std::string novaSenha) const;

    void armazenarNome(std::string novoNome);

    void atualizarDadosPerfil();

    bool permitirAlteracaoDados() const;

    const std::string& getNome() const;
    const std::string& getEmail() const;
    const std::string& getSenha() const;
    const std::string& getTipo() const;
    const std::string& getRespostaSeguranca() const;

    bool autenticar(std::string email,
                    std::string senha) const;

    static std::string getPerguntaSeguranca();

    static bool emailJaCadastrado(
        const std::string& email,
        const std::string& nomeArquivo = "usuarios.txt");

    static std::string fazerLogin(
        const std::string& email,
        const std::string& senha,
        const std::string& nomeArquivo = "usuarios.txt");

    static bool salvarUsuario(
        const std::string& tipo,
        const std::string& nome,
        const std::string& email,
        const std::string& senha,
        const std::string& cpf,
        const std::string& respostaSeguranca,
        const std::string& nomeArquivo = "usuarios.txt");

    static bool recuperarSenha(
        const std::string& email,
        const std::string& respostaSeguranca,
        const std::string& novaSenha,
        const std::string& nomeArquivo = "usuarios.txt");
};

#endif
