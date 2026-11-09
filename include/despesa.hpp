/**
 * @file despesa.hpp
 * @brief Declaracao da classe Despesa.
 */
#ifndef DESPESA_HPP
#define DESPESA_HPP

#include "lancamentos.hpp"

/**
 * @brief Lancamento que retira dinheiro da conta.
 *
 * Despesas com data ate hoje diminuem o saldo; despesas com data futura
 * aumentam a divida da conta.
 */
class Despesa : public Lancamentos {
public:
    /**
     * @brief Cria uma despesa.
     * @param valor Valor da despesa (maior que zero).
     * @param categoria Categoria da despesa.
     * @param data Data da despesa.
     * @param conta Conta da despesa.
     * @param fixo Se a despesa e fixa/recorrente.
     * @throws std::invalid_argument se algum parametro for invalido.
     */
    Despesa(double valor, Categoria* categoria, std::chrono::year_month_day data,
            Conta* conta, bool fixo);

    /**
     * @brief Diminui o saldo (data ate hoje) ou aumenta a divida (data futura).
     * @param saldo Saldo a ser alterado.
     * @param divida Divida a ser alterada.
     * @param hoje Data atual.
     * @return Sempre true (a despesa e sempre aplicada).
     */
    bool aplicarEfeito(double& saldo, double& divida,
                       std::chrono::year_month_day hoje) const override;

    /** @brief Despesas contam para os orcamentos. @return true. */
    bool isDespesa() const override;

    /** @brief Nome do tipo. @return "Despesa". */
    std::string getTipoTexto() const override;
};

#endif
