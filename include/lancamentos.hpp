#ifndef LANCAMENTOS_HPP
#define LANCAMENTOS_HPP

#include <string>
#include <chrono>


#include "categoria.hpp"
#include "conta.hpp"

// Forward declaration para evitar dependência circular
class Conta;

//Classe pai de despesa e receita. Guarda o histotico de lancamento de uma conta. 
class Lancamentos {
public:
    //Atributos:
    double valor = 0.0;
    Categoria* categoria = nullptr;
    std::chrono::year_month_day data{};
    Conta* conta = nullptr;
    enum tipoLancamento {TipoReceita, TipoDespesa};
    tipoLancamento tipo = TipoDespesa;
    bool LancamentoFixo = false;
    bool processado = false; // true depois que o lancamento ja afetou saldo/divida

    virtual ~Lancamentos() = default;

    //Adiciona o lancamento na lista de lancamentos da conta
    virtual void addLancamentosFuturos();

    //Cria a transacao que aplica os lancamentos pendentes da conta no saldo/divida
    void realizarTransacao();

};


#endif