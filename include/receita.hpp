/**
 * @file receita.hpp
 * @brief Declaracao da classe Receita.
 */
#ifndef RECEITA_HPP
#define RECEITA_HPP

#include "lancamentos.hpp"

/**
 * @brief Lancamento que adiciona dinheiro a conta (ex: salario).
 *
 * Uma receita so aumenta o saldo quando a data dela chega; receitas com data
 * futura ficam pendentes.
 */
class Receita : public Lancamentos {
public:
    /**
     * @brief Cria uma receita.
     * @param valor Valor da receita (maior que zero).
     * @param categoria Categoria da receita.
     * @param data Data da receita.
     * @param conta Conta da receita.
     * @param fixo Se a receita e fixa/recorrente.
     * @throws std::invalid_argument se algum parametro for invalido.
     */
    Receita(double valor, Categoria* categoria, std::chrono::year_month_day data,
            Conta* conta, bool fixo);

    /**
     * @brief Aumenta o saldo se a data da receita ja chegou.
     * @param saldo Saldo a ser alterado.
     * @param divida Divida (nao e alterada por receitas).
     * @param hoje Data atual.
     * @return true se a receita foi aplicada; false se a data ainda nao chegou.
     */
    bool aplicarEfeito(double& saldo, double& divida,
                       std::chrono::year_month_day hoje) const override;

    /** @brief Receitas nao contam para os orcamentos. @return false. */
    bool isDespesa() const override;

    /** @brief Nome do tipo. @return "Receita". */
    std::string getTipoTexto() const override;
};

#endif
