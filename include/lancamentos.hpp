/**
 * @file lancamentos.hpp
 * @brief Declaracao da classe abstrata Lancamentos.
 */
#ifndef LANCAMENTOS_HPP
#define LANCAMENTOS_HPP

#include <chrono>
#include <string>

class Categoria;
class Conta;

/**
 * @brief Classe abstrata para um lancamento financeiro (Receita ou Despesa).
 *
 * Cada subclasse define, de forma polimorfica, como o lancamento afeta o saldo
 * e a divida da conta (aplicarEfeito) e se conta como gasto (isDespesa).
 */
class Lancamentos {
protected:
    double valor_;                      /**< Valor do lancamento (sempre positivo). */
    Categoria* categoria_;              /**< Categoria do lancamento. */
    std::chrono::year_month_day data_;  /**< Data do lancamento. */
    Conta* conta_;                      /**< Conta a que o lancamento pertence. */
    bool fixo_;                         /**< Indica se e um lancamento fixo/recorrente. */
    bool processado_;                   /**< true depois que ja afetou saldo ou divida. */

public:
    /**
     * @brief Construtor usado pelas subclasses.
     * @param valor Valor do lancamento (deve ser maior que zero).
     * @param categoria Categoria do lancamento (nao pode ser nula).
     * @param data Data do lancamento (deve ser uma data valida).
     * @param conta Conta do lancamento (nao pode ser nula).
     * @param fixo Se o lancamento e fixo/recorrente.
     * @throws std::invalid_argument se algum parametro for invalido.
     */
    Lancamentos(double valor, Categoria* categoria, std::chrono::year_month_day data,
                Conta* conta, bool fixo);

    /**
     * @brief Destrutor virtual, para destruir corretamente as subclasses.
     */
    virtual ~Lancamentos() = default;

    /**
     * @brief Aplica o efeito do lancamento no saldo e na divida.
     * @param saldo Saldo a ser alterado.
     * @param divida Divida a ser alterada.
     * @param hoje Data atual, usada para separar lancamentos passados e futuros.
     * @return true se o lancamento foi aplicado; false se deve esperar a data.
     */
    virtual bool aplicarEfeito(double& saldo, double& divida,
                               std::chrono::year_month_day hoje) const = 0;

    /**
     * @brief Indica se o lancamento e um gasto (conta para os orcamentos).
     * @return true para despesas, false para receitas.
     */
    virtual bool isDespesa() const = 0;

    /**
     * @brief Retorna o nome do tipo do lancamento.
     * @return "Receita" ou "Despesa".
     */
    virtual std::string getTipoTexto() const = 0;

    /**
     * @brief Adiciona este lancamento ao historico da propria conta.
     */
    void adicionarNaConta();

    /**
     * @brief Cria a Transacao que aplica os lancamentos pendentes da conta.
     *
     * Se a transacao alterou saldo ou divida, ela e registrada na conta;
     * caso contrario e descartada.
     */
    void realizarTransacao();

    /**
     * @brief Marca o lancamento como ja aplicado no saldo/divida.
     */
    void marcarProcessado();

    /** @brief Retorna o valor. @return Valor do lancamento. */
    double getValor() const;

    /** @brief Retorna a categoria. @return Ponteiro para a categoria. */
    Categoria* getCategoria() const;

    /** @brief Retorna a data. @return Data do lancamento. */
    std::chrono::year_month_day getData() const;

    /** @brief Retorna a conta. @return Ponteiro para a conta. */
    Conta* getConta() const;

    /** @brief Indica se o lancamento e fixo. @return true se for fixo/recorrente. */
    bool isFixo() const;

    /** @brief Indica se o lancamento ja foi aplicado. @return true se ja foi processado. */
    bool isProcessado() const;
};

#endif
