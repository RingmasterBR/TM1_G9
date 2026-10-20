#include <string>
#include <chrono>
#include <list>

#include "transacao.hpp"
#include "categoria.hpp"
#include "lancamentos.hpp"
#include "conta.hpp"
#include "despesa.hpp"

       
    //Construtor para despesas 
    Despesa:: Despesa(const double valordaDespesa, Categoria* categoriadaDespesa, std::chrono::year_month_day dataDaDespesa, Conta* contaDaDespesa, bool ehfixo){
        valor = valordaDespesa;
        categoria = categoriadaDespesa;
        data = dataDaDespesa;
        conta = contaDaDespesa;
        tipo = TipoDespesa;
        LancamentoFixo = ehfixo;
    }
    

    //Instancia novo objeto de lancamento de  
    void Despesa:: addLancamentosFuturos(){
        if(conta!= nullptr){
            conta->addLancamento(this);
        }
     };