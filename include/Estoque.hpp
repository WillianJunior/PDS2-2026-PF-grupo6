#ifndef ESTOQUE_HPP
#define ESTOQUE_HPP

#include "Produto.hpp"
#include <string>
#include <vector>

/**
 * @brief Classe gestora do inventário físico da loja.
 * Controla disponibilidade dos produtos e persiste o estoque em arquivo.
 */
class Estoque {
private:
    std::vector<Produto> _inventario;
    std::string _nomeArquivo;

    /**
     * @brief Carrega o inventário do arquivo.
     * Se o arquivo não existir, mantém o inventário vazio.
     * @throw std::runtime_error se o arquivo existir mas tiver dados corrompidos.
     */
    void carregarEstoque();

public:
    /**
     * @brief Carrega o inventário do arquivo. Se não existir,
     * inicializa com produtos padrão e salva o arquivo.
     * @param nomeArquivo Caminho do arquivo de estoque.
     */
    explicit Estoque(const std::string& nomeArquivo = "estoque.txt");

    /**
     * @brief Retorna uma cópia do inventário atual com as quantidades.
     * A formatação visual fica a cargo da classe Interface.
     * @return Vetor contendo os produtos em estoque.
     */
    std::vector<Produto> obterInventario() const;

    /**
     * @brief Filtra e retorna apenas os produtos com estoque crítico (menos de 5 unidades).
     * @return Vetor de produtos em estado de alerta.
     */
    std::vector<Produto> obterProdutosEmAlerta() const;

    /**
     * @brief Valida se há estoque suficiente para a reserva.
     * @param idProduto ID do produto a reservar.
     * @param quantidade Unidades a reservar.
     * @throw std::invalid_argument se quantidade <= 0.
     * @throw std::runtime_error se produto não encontrado ou estoque insuficiente.
     */
    void congelarQuantidades(int idProduto, int quantidade) const;

    /**
     * @brief Debita o estoque após pagamento confirmado e salva no arquivo.
     * @param idProduto ID do produto vendido.
     * @param quantidade Unidades a debitar.
     * @throw std::invalid_argument se quantidade <= 0.
     * @throw std::runtime_error se produto não encontrado ou estoque insuficiente.
     */
    void efetuarSubtracao(int idProduto, int quantidade);

    /**
     * @brief Verifica se há estoque suficiente para a compra.
     * @param idProduto ID do produto.
     * @param quantidadeDesejada Unidades desejadas.
     * @return true se o estoque permitir a compra.
     */
    bool impedirVendasAcimaMaximo(int idProduto, int quantidadeDesejada) const;

    /**
     * @brief Salva o inventário atual no arquivo.
     * @throw std::runtime_error se o arquivo não puder ser aberto.
     */
    void salvarEstoque() const;
};

#endif