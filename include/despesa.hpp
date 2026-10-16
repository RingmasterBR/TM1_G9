#ifndef DESPESA_HPP
#define DESPESA_HPP

#include <string>
#include <chrono>

#include "transacao.hpp"
#include "categoria.hpp"
#include "lancamentos.hpp"



class Despesa : public Lancamentos {
public:    
    //Construtor para despesas fixas
    Despesa(const double valordaDespesa, Categoria& categoriadaDespesa, std::year_month_day dataDaDespesa, Conta& contaDaDespesa, bool ehfixo){}

    
    //Construtor para despesas nao fixas    
    ~Despesa() = default;

    //Instancia novo objeto de lancamento de  
    void addLancamentosFuturos();
};

#endif