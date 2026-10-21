#ifndef RECEITA_HPP
#define RECEITA_HPP

#include <string>
#include <chrono>

#include "transacao.hpp"
#include "categoria.hpp"
#include "lancamentos.hpp"
#include "conta.hpp"


class Receita : public Lancamentos {
private:    
public:    
    //Construtor para despesas fixas
    Receita(const double valorDaReceita, Categoria* categoriaDaReceita, std::chrono::year_month_day dataDaReceita, Conta* contaDaReceita, bool ehfixo);

    
    //Construtor para despesas nao fixas    
    ~Receita() = default;

    //Indica se a despesa atual eh fixa ou nao
    bool isFixa() const;

    //Instancia novo objeto de lancamento de  
    void addLancamentosFuturos();
};

#endif