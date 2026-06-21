#ifndef ADMINISTRADOR_HPP
#define ADMINISTRADOR_HPP

#include "Usuario.hpp"
#include <string>

class Catalogo;
class Estoque;
class Cliente;
class Pedido;

/**
 * @brief Usuário com permissões administrativas.
 */
class Administrador : public Usuario {
public:
    Administrador(std::string nome,
                  std::string email,
                  std::string senha,
                  std::string respostaSeguranca);

    /**
     * @brief Métodos legados mantidos vazios para compatibilidade de herança.
     * O controle de fluxos interativos de telas agora reside unicamente na classe UI.
     */
    void gerenciarCatalogo(Catalogo& catalogo);
    void gerenciarEstoque(Estoque& estoque);

    /**
     * @brief Gera o relatório textual com os dados cadastrais do cliente informado.
     * @return String formatada contendo as informações.
     */
    std::string gerenciarContas(Cliente& cliente);

    /**
     * @brief Gera o relatório detalhado das informações financeiras e logísticas da venda.
     * @return String formatada contendo o faturamento.
     */
    std::string atualizarVendas(Pedido& pedido);

    /**
     * @brief Cadastra o administrador no sistema.
     * @return true se salvo com sucesso, false caso contrário.
     * @throws std::runtime_error Se houver falha de escrita física de arquivos.
     */
    bool cadastrarAdministrador(
        const std::string& nomeArquivo = "usuarios.txt") const;
};

#endif