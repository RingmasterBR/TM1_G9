/**
 * @file transacao.hpp
 * @brief Declaracao da classe Transacao.
 */
#ifndef TRANSACAO_HPP
#define TRANSACAO_HPP

class Conta;

/**
 * @brief Registro de uma alteracao no saldo/divida de uma conta.
 *
 * Ao ser criada, a transacao aplica na conta todos os lancamentos ainda nao
 * processados e guarda o saldo e a divida de antes e de depois.
 */
class Transacao {
private:
    Conta* conta_;            /**< Conta associada. */
    double valor_;            /**< Valor do lancamento que gerou a transacao. */
    double saldoAnterior_;    /**< Saldo antes da transacao. */
    double dividaAnterior_;   /**< Divida antes da transacao. */
    double saldoFinal_;       /**< Saldo depois da transacao. */
    double dividaFinal_;      /**< Divida depois da transacao. */

    /**
     * @brief Aplica os lancamentos pendentes da conta em saldoFinal_ e dividaFinal_.
     */
    void calcularSaldoEDivida();

public:
    /**
     * @brief Cria a transacao e calcula o novo saldo e a nova divida.
     * @param conta Conta associada (nao pode ser nula).
     * @param valor Valor do lancamento que gerou a transacao.
     * @throws std::invalid_argument se a conta for nula.
     */
    Transacao(Conta* conta, double valor);

    /**
     * @brief Destrutor virtual.
     */
    virtual ~Transacao() = default;

    /**
     * @brief Registra a transacao na conta, se ela alterou saldo ou divida.
     * @return true se a transacao foi registrada (a conta passa a ser dona dela).
     */
    bool registrarNaConta();

    /** @brief Retorna a conta. @return Ponteiro para a conta. */
    Conta* getConta() const;
    /** @brief Retorna o valor. @return Valor do lancamento que gerou a transacao. */
    double getValor() const;
    /** @brief Retorna o saldo antes da transacao. @return Saldo anterior. */
    double getSaldoAnterior() const;
    /** @brief Retorna a divida antes da transacao. @return Divida anterior. */
    double getDividaAnterior() const;
    /** @brief Retorna o saldo depois da transacao. @return Saldo final. */
    double getSaldoFinal() const;
    /** @brief Retorna a divida depois da transacao. @return Divida final. */
    double getDividaFinal() const;
};

#endif
