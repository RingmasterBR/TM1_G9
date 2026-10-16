#include <string>
#include <chrono>
#include <list>

#include "transacao.hpp"
#include "categoria.hpp"
#include "lancamentos.hpp"
#include "despesa.hpp"

       
    //Construtor para despesas 
    Despesa:: Despesa(const double valordaDespesa, Categoria* categoriadaDespesa, std::year_month_day dataDaDespesa, Conta* contaDaDespesa, bool ehfixo){
        valor = valordaDespesa;
        categoria = categoriadaDespesa;
        data = dataDaDespesa;
        conta = contaDaDespesa;
        tipo = TipoDespesa;
        LancamentoFixo = ehfixo;
    }
    
    //Construtor para despesas nao fixas    
     Despesa::~Despesa() = default;

    //Instancia novo objeto de lancamento de  
    void Despesa:: addLancamentosFuturos(){
        conta->addLancamento(this);
     };
