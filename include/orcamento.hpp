/**
 * @file orcamento.hpp
 * @brief Declaracao da classe Orcamento.
 */
#ifndef ORCAMENTO_HPP
#define ORCAMENTO_HPP

class Categoria;
class Lancamentos;

/**
 * @brief Limite de gastos para um tipo de gasto em um mes/ano.
 *
 * Acumula as despesas do mesmo tipo de gasto e do mesmo periodo para saber
 * quanto ja foi gasto e se o limite foi ultrapassado.
 */
class Orcamento {
private:
    double limite_;          /**< Valor maximo de gastos. */
    double valorGasto_;      /**< Total ja gasto no periodo. */
    Categoria* categoria_;   /**< Categoria (tipo de gasto) monitorada. */
    int mes_;                /**< Mes de referencia (1 a 12). */
    int ano_;                /**< Ano de referencia. */

public:
    /**
     * @brief Cria um orcamento.
     * @param limite Valor limite de gastos (maior que zero).
     * @param categoria Categoria monitorada (nao pode ser nula).
     * @param mes Mes de referencia (1 a 12).
     * @param ano Ano de referencia.
     * @throws std::invalid_argument se algum parametro for invalido.
     */
    Orcamento(double limite, Categoria* categoria, int mes, int ano);

    /**
     * @brief Soma um lancamento ao total gasto, se ele pertencer ao orcamento.
     *
     * So entram despesas do mesmo tipo de gasto e do mesmo mes/ano. Receitas,
     * outros tipos de gasto, outros periodos e ponteiros nulos sao ignorados.
     * @param lancamento Lancamento a considerar.
     * @return true se o lancamento foi somado.
     */
    bool adicionarLancamento(const Lancamentos* lancamento);

    /**
     * @brief Verifica se o limite foi ultrapassado.
     * @return true se o valor gasto for maior que o limite.
     */
    bool estourouLimite() const;

    /**
     * @brief Calcula quanto ainda pode ser gasto.
     * @return Limite menos o valor gasto (negativo se estourou).
     */
    double getSaldoRestante() const;

    /**
     * @brief Altera o limite. Nao altera o valor ja gasto.
     * @param novoLimite Novo limite (maior que zero).
     * @throws std::invalid_argument se o limite nao for positivo.
     */
    void setLimite(double novoLimite);

    /** @brief Retorna o limite. @return Valor do limite. */
    double getLimite() const;
    /** @brief Retorna o total gasto. @return Valor ja gasto no periodo. */
    double getValorGasto() const;
    /** @brief Retorna a categoria. @return Ponteiro para a categoria monitorada. */
    Categoria* getCategoria() const;
    /** @brief Retorna o mes. @return Mes de referencia (1 a 12). */
    int getMes() const;
    /** @brief Retorna o ano. @return Ano de referencia. */
    int getAno() const;
};

#endif
