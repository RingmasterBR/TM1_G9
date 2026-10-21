#ifndef TRANSACAO_HPP
#define TRANSACAO_HPP

// Inclusões próprias do C++
#include <iostream>
#include <string>

// Forward declarations para evitar erros de compilação
class Conta;

class Transacao {
public:

    Transacao(Conta* contaTransacao, double valorTransacao);
    virtual ~Transacao();
    Conta* getConta() const;
    double getSaldoFinal() const;
    double getDividaFinal() const;
    double getSaldoAnterior() const;
    double getDividaAnterior() const;
    int ValidarDados();

 //Adiciona a transacao atual na lista de transacao da classe conta toda vez que um objeto transacao eh criado.    
    void updateListaTransacao();

protected:
    Conta* conta;            /**< Conta associada. */
    double valor;            /**< Valor da transacao. */
    double saldoFinal;       /**< Armazena o saldo atualizado pos-transacao. */
    double dividaFinal;      /**< Armazena o valor da divida atualizado pos-transacao. */
    double saldoAnterior;    /**< Armazena o saldo historico pre-transacao. */
    double dividaAnterior;   /**< Armazena a divida historica pre-transacao. */

    //Percorre vetor de lançamento de conta e recalcula, atualiza saldo e divida Final da propria transacao. 
    void updateSaldoEDivida();    
};

#endif