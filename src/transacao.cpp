
// Inclusões próprias do C++
#include <iostream>
#include <string>
#include<list>
#include <chrono>

    void Transacao::Transacao(Conta* contaTransacao, double valorTransacao){
        conta = contaTransacao;
        valor = valorTransacao;
        saldoFinal = contaTransacao->getSaldo();        
        dividaFinal = contaTransacao->getDivida();      
        saldoAnterior = contaTransacao->getSaldo();   
        dividaAnterior= contaTransacao->getDivida();     
    };

    Transacao::~Transacao() = default;

    Conta* Transacao::getConta() const{
        return  conta;
    }
    double Transacao:: getSaldoFinal() const{
        return saldoFinal;
    }
    double Transacao:: getDividaFinal() const{
        return dividaFinal;
    }
    double Transacao:: getSaldoAnterior() const{
        return saldoAnterior
    }
    
    double Transacao:: getDividaAnterior() const{
        return dividaAnterior
    }
    
    Transacao::int ValidarDados(){
    }        

    //Percorre vetor de lançamento de conta e recalcula, atualiza saldo e divida Final da propria transacao. 
    void Transacao :: updateSaldoEDivida(){
        int qtdLancamentos = conta-> lancamentosFuturos.size();
        using namespace std::chrono;
        year_month_day hoje = floor<days>(system_clock::now());

        for(auto it = conta->lancamentosFuturos.begin(); it != conta-> lancamentosFuturos.end()){
            Lancamentos* l = *it;
            if (l-> tipo == TipoDespesa && ll-> data > hoje){
                dividaFinal = dividaAtual + l-> valor;
            }else if(l-> tipo = TipoDespesa && l-> data == hoje){
                saldoFinal = saldoAtual - l-> valor;
            }else if (l-> tipo = TipoReceita && l-> data == hoje){
                saldoFinal = saldoAtual + l-> valor;
            }
            if(!l-> ehfixo){
                conta->lancamentosFuturos.erase(it);
                ++it;
            }else{
                ++it;
            }
        }
    } 
    
    //Adiciona a transacao atual na lista de transacao da classe conta toda vez que um objeto transacao eh criado.    
    void Transacao::updateListaTransacao(){
        if(saldoAnterior != sandoAtual || dividaAnterior != dividaAtual){
            conta-> addTransacao(this);
        }
    }   

