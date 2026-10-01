#ifndef TRANSACAO_HPP
#define TRANSACAO_HPP

// Inclusões próprias do C++
#include <iostream>
#include <string>
#include <list>

// Inclusões do projeto
#include "usuario.hpp"
#include "conta.hpp"
#include "receita.hpp"
#include "despesa.hpp"
#include "categoria.hpp"

// Forward declaration para evitar erros de compilacao
class Categoria;

/**
 * @brief Classe crítica responsável pelo gerenciamento e execução de transações financeiras.
 * 
 * Todas as operações do projeto que envolvam atualização do saldo ou da dívida da conta
 * devem ser realizadas por meio desta classe. Devido à sua criticidade, a classe assinatura da classe possui
 * métodos detalhados para controle e validação de operações.
 */
class Transacao {
public:
    /**
     * @brief Define a direção da movimentação financeira (Entrada ou Saída).
     */
    enum TipoTransacao {Entrada, Saida, Default0};

    /**
     * @brief Define as formas de pagamento aceitas na transação.
     */
    enum FormaPagamento {Credito, Debito, Pix, Transferencia, Default0};

    Receita receita;     /**< Objeto contendo os dados da receita associada. */
    Despesa despesa;     /**< Objeto contendo os dados da despesa associada. */
    Categoria categoria; /**< Objeto contendo a categoria da transação. */
    Conta conta;         /**< Conta bancária associada à transação. */

    /**
     * @brief Construtor padrão da classe Transacao.
     */
    Transacao() {}

    /**
     * @brief Construtor para inicialização de transações gerais.
     * @param conta Conta na qual a transação será realizada.
     * @param tipo Tipo da transação (Entrada ou Saída).
     * @param formaDePagamento Forma de pagamento utilizada.
     * @param categoria Nome da categoria da transação.
     * @param valor Valor da transação.
     */
    Transacao(const Conta& conta, TipoTransacao tipo, FormaPagamento formaDePagamento, std::string categoria, double valor) {}

    /**
     * @brief Define a receita associada à transação atual.
     * @param receita Objeto do tipo Receita contendo os dados do crédito.
     */
    void setReceita(const Receita& receita);

    /**
     * @brief Define a despesa associada à transação atual.
     * @param despesa Objeto do tipo Despesa.
     */
    void setDespesa(const Despesa& despesa);

    /**
     * @brief Define a conta bancária associada à transação.
     * @param conta Objeto da conta a ser atualizada.
     */
    void setConta(const Conta& conta);

    /**
     * @brief Retorna uma representação em texto do tipo de transação.
     * @return std::string Nome do tipo da transação.
     */
    std::string showTipoTransacao() const;

    /**
     * @brief Retorna uma representação em texto da categoria da transação.
     * @return std::string Nome da categoria.
     */
    std::string showCategoria() const;

    /**
     * @brief Retorna um resumo detalhado da transação realizada.
     * @return std::string Texto com o tipo, valor, saldo inicial e saldo final.
     */
    std::string showTransacao() const;

    /**
     * @brief Obtém a lista de despesas utilizadas na transação.
     * @return std::list<Despesa> Lista de despesas atuais.
     */
    std::list<Despesa> getDespesaAtual() const;

    /**
     * @brief Obtém a lista de receitas utilizadas na transação.
     * @return std::list<Receita> Lista de receitas atuais.
     */
    std::list<Receita> getReceitaAtual() const;

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
     * @brief Valida os dados e parâmetros da transação antes do processamento.
     * @return int Código de status informando se a validação foi bem-sucedida ou o tipo de erro.
     */
    int ValidarDados();

private:
    double saldoFinal;     /**< Armazena o saldo atualizado pós-transação. */
    double dividaFinal;    /**< Armazena o valor da dívida atualizado pós-transação. */
    double saldoAnterior;  /**< Armazena o saldo histórico pré-transação. */
    double dividaAnterior; /**< Armazena a dívida histórica pré-transação. */

    /**
     * @brief Define internamente o valor do saldo final.
     * @param saldoFinal Novo saldo calculado.
     */
    void setSaldoFinal(double saldoFinal);

    /**
     * @brief Define internamente o valor da dívida final.
     * @param dividaFinal Nova dívida calculada.
     */
    void setDividaFinal(double dividaFinal);

    /**
     * @brief Define internamente o valor do saldo anterior.
     * @param saldoAnterior Saldo pré-operação.
     */
    void setSaldoAnterior(double saldoAnterior);

    /**
     * @brief Define internamente o valor da dívida anterior.
     * @param dividaAnterior Dívida pré-operação.
     */
    void setDividaAnterior(double dividaAnterior);

    /**
     * @brief Calcula e retorna o novo saldo da conta com base nos parâmetros genéricos.
     * @param conta Conta que sofrerá a alteração.
     * @param tipo Tipo da movimentação (Entrada ou Saída).
     * @param formaDePagamento Método de pagamento escolhido.
     * @param categoria Nome da categoria do lançamento.
     * @param valor Valor monetário a ser aplicado.
     * @return double Valor recalculado do saldo.
     */
    double updateSaldo(const Conta& conta, TipoTransacao tipo, FormaPagamento formaDePagamento, std::string categoria, double valor);

    /**
     * @brief Sobrecarga do método updateSaldo para atualização baseada em objeto de Receita.
     * 
     * Percorre a lista de receitas, verifica agendamentos para a data atual e processa o saldo.
     * @param conta Conta a ser atualizada.
     * @param tipo Tipo de movimentação.
     * @param formaDePagamento Método de pagamento.
     * @param receita Objeto Receita contendo valor e data.
     * @return double Valor recalculado do saldo.
     */
    double updateSaldo(const Conta& conta, TipoTransacao tipo, FormaPagamento formaDePagamento, const Receita& receita);

    /**
     * @brief Sobrecarga do método updateSaldo para atualização baseada em objeto de Despesa.
     * 
     * Percorre a lista de despesas, verifica agendamentos para a data atual e processa o saldo.
     * @param conta Conta a ser atualizada.
     * @param tipo Tipo de movimentação.
     * @param formaDePagamento Método de pagamento.
     * @param despesa Objeto Despesa contendo valor e data.
     * @return double Valor recalculado do saldo.
     */
    double updateSaldo(const Conta& conta, TipoTransacao tipo, FormaPagamento formaDePagamento, const Despesa& despesa);

    /**
     * @brief Calcula e retorna o novo valor da dívida da conta.
     * @param conta Conta consultada.
     * @param tipo Tipo de movimentação.
     * @param formaDePagamento Método de pagamento (ex: Crédito).
     * @param valor Valor da transação.
     * @return double Novo valor da dívida.
     */
    double updateDivida(const Conta& conta, TipoTransacao tipo, FormaPagamento formaDePagamento, double valor);

    /**
     * @brief Aplica e consolida o saldo final diretamente na instância da conta.
     * @param valor Valor do saldo final a ser setado.
     * @param conta Referência da conta a ser alterada.
     */
    void setSaldoFinalemConta(double valor, Conta& conta);

    /**
     * @brief Aplica e consolida a dívida final diretamente na instância da conta.
     * @param valor Valor da dívida a ser setada.
     * @param conta Referência da conta a ser alterada.
     */
    void setDividaFinalemConta(double valor, Conta& conta);
};

#endif