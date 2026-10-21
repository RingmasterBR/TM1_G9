#include <string>
#include <chrono>
#include <list>

#include "transacao.hpp"
#include "categoria.hpp"
#include "lancamentos.hpp"
#include "conta.hpp"
#include "receita.hpp"

       
    //Construtor para receitas fixas
    Receita:: Receita(const double valorDaReceita, Categoria* categoriaDaReceita, std:: chrono:: year_month_day dataDaReceita, Conta* contaDaReceita, bool ehfixo){
        valor = valorDaReceita;
        categoria = categoriaDaReceita;
        data = dataDaReceita;
        conta = contaDaReceita;
        tipo = TipoReceita;
        LancamentoFixo = ehfixo;
    }
    
    //Instancia novo objeto de lancamento de  
     void Receita:: addLancamentosFuturos(){
        if(conta!=nullptr){
            conta->addLancamento(this);
        }
     };