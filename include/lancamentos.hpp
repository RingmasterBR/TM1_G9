#ifndef LANCAMENTOS_HPP
#define LANCAMENTOS_HPP

#include <string>
#include <chrono>


#include "categoria.hpp"
#include "conta.hpp"


//Classe pai de despesa e receita. Guarda o histotico de lancamento de uma conta. 
class Lancamentos {
public:
    //Atributos:
    double valor;
    Categoria* categoria;
    std::chrono::year_month_day data;
    Conta* conta;
    enum tipoLancamento {TipoReceita, TipoDespesa};
    tipoLancamento tipo;
    bool LancamentoFixo;

private:
    void realizarTransacao();

};


#endif