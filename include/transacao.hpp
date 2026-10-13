#ifndef TRANSACAO_HPP
#define TRANSACAO_HPP

// Inclusões próprias do C++
#include <iostream>
#include <string>

// Forward declarations para evitar erros de compilação
class Conta;

/**
 * @brief Classe abstrata responsavel pelo gerenciamento e execucao de transacoes financeiras.
 */

class Transacao {
public:
    /**
     * @brief Define as formas de pagamento aceitas na transação.
     */
    enum FormaPagamento { Credito, Debito, Pix, Transferencia };

    /**
     * @brief Construtor para inicialização de transações do tipo Despesa.
     * @param conta Conta na qual a transação será realizada.
     * @param formaDePagamento Forma de pagamento utilizada.
     * @param categoria Nome da categoria da transação.
     * @param valor valor da transacao.
     */
    Transacao(const Conta& conta, FormaPagamento formaDePagamento, std::string categoria, double valor);
    
    /**
     * @brief Construtor para inicialização de transações do tipo Receita.
     * @param conta Conta na qual a transação será realizada.
     * @param formaDePagamento Forma de pagamento utilizada.
     * @param categoria Nome da categoria da transação.
     * @param receita Objeto de receita associado.
     */
    Transacao(const Conta& conta, FormaPagamento formaDePagamento, std::string categoria, const Receita& receita);
    
    virtual ~Transacao();

    /**
     * @brief Obtém o objeto Conta associado à transação.
     * @return Conta Objeto da conta bancária.
     */
    Conta getConta() const;

    /**
     * @brief Obtém o valor do saldo da conta após a execução da transação.
     * @return double Saldo final recalculado.
     */
    double getSaldoFinal() const;

    /**
     * @brief Obtém o valor total da dívida da conta após a execução da transação.
     * @return double Dívida final recalculada.
     */
    double getDividaFinal() const;

    /**
     * @brief Obtém o valor do saldo da conta antes da execução da transação.
     * @return double Saldo anterior.
     */
    double getSaldoAnterior() const;

    /**
     * @brief Obtém o valor total da dívida da conta antes da execução da transação.
     * @return double Dívida anterior.
     */
    double getDividaAnterior() const;

    /**
     * @brief Valida os dados e parametros da transacao antes do processamento.
     * @return int Codigo de status informando se a validacao foi bem-sucedida ou o tipo de erro.
     */
    int ValidarDados();

protected:
    Conta* conta;            /**< Conta associada. */
    FormaPagamento forma;    /**< Forma de pagamento. */
    std::string categoria;   /**< Nome da categoria. */

    double valor;            /**< Valor da transacao. */
    double saldoFinal;       /**< Armazena o saldo atualizado pos-transacao. */
    double dividaFinal;      /**< Armazena o valor da divida atualizado pos-transacao. */
    double saldoAnterior;    /**< Armazena o saldo historico pre-transacao. */
    double dividaAnterior;   /**< Armazena a divida historica pre-transacao. */

    /**
     * @brief Define internamente o valor do saldo final.
     * @param saldoFinal Novo saldo calculado.
     */
    void setSaldoFinal();

    /**
     * @brief Define internamente o valor da dívida final.
     * @param dividaFinal Nova dívida calculada.
     */
    void setDividaFinal();

    /**
    * @brief Calcula e retorna o novo saldo da conta com base nos parametros.
    * @param contaRef Conta que sofrera a alteracao.
    * @return double Valor recalculado do saldo.
    */
    
    double updateSaldo(double valor);

    /**
     * @brief Calcula e retorna o novo valor da divida da conta.
     * @param contaRef Conta consultada.
     * @return double Novo valor da divida.
     */
    double updateDivida(double valor); 
    
};

#endif