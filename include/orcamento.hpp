#ifndef ORCAMENTO_HPP
#define ORCAMENTO_HPP

#include <string>
#include "categoria.hpp"
#include "transacao.hpp"

/**
* @brief Classe responsável pelo controle de limite de gastos por categoria e período.
*
* Acumula os valores de transações/despesas registradas para verificar se o limite foi atingido.
 */
 class Orcamento {
private:
    double limite_;
    double valorGasto_;
    Categoria* categoria_;
    int mes_;
    int ano_;
    
public:
    /**
    * @brief Construtor de orcamento.
    * @param limite Valor limite de gastos.
    * @param categoria Ponteiro para a categoria.
    * @param mes Mês de referência.
    * @param ano Ano de referência.
    */
    Orcamento(double limite, Categoria* categoria, int mes, int ano);

    /**
    * @brief Destrutor de orcamento.
    */
    ~Orcamento() = default;

    /**
    * @brief Adiciona uma transação no total do orçamento.
    * @param transacao Ponteiro para a transação.
    */
    void adicionarTransacao(Transacao* transacao);
    
    /**
    * @brief Verifica se foi ultrapassado o limite para o orçamento.
    * @return true se valorGasto > limite, falso senão.
    */
    bool estourouLimite() const;
    
    /**
    * @brief Calcula o saldo disponível conforme o orçamento.
    * @return Valor restante de saldo.
    */
    double getSaldoRestante() const;
    
    /**
    * @brief Atualiza o limite para o orçamento.
    * @param novoLimite Novo teto.
    */
    void setLimite(double novoLimite);

    /**
     * @brief Retorna o limite de gastos definido para o orçamento.
     * @return Valor do limite configurado.
     */
    double getLimite() const;

    /**
     * @brief Retorna o valor total já gasto dentro do orçamento.
     * @return Quantia acumulada em despesas.
     */
    double getValorGasto() const;

    /**
     * @brief Retorna a categoria vinculada ao orçamento.
     * @return Ponteiro para a Categoria monitorada.
     */
    Categoria* getCategoria() const;

    /**
     * @brief Retorna o mês de referência do orçamento.
     * @return Número do mês (1 a 12).
     */
    int getMes() const;

    /**
     * @brief Retorna o ano de referência do orçamento.
     * @return Ano correspondente.
     */
    int getAno() const;
 };
 #endif