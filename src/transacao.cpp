
// Inclusões próprias do C++
#include <iostream>
#include <string>
#include<list>
#include <chrono>

#include "transacao.hpp"
#include "conta.hpp"
#include "lancamentos.hpp"

    Transacao::Transacao(Conta* contaTransacao, double valorTransacao){
        conta = contaTransacao;
        valor = valorTransacao;
        saldoFinal = contaTransacao->getSaldo();        
        dividaFinal = contaTransacao->getDivida();      
        saldoAnterior = contaTransacao->getSaldo();   
        dividaAnterior= contaTransacao->getDivida();     
        updateSaldoEDivida();
    };

    Transacao::~Transacao() = default;

    Conta* Transacao::getConta() const{
        return conta;
    }
    double Transacao:: getSaldoFinal() const{
        return saldoFinal;
    }
    double Transacao:: getDividaFinal() const{
        return dividaFinal;
    }
    double Transacao:: getSaldoAnterior() const{
        return saldoAnterior;
    }
    
    double Transacao:: getDividaAnterior() const{
        return dividaAnterior;
    }
    
    int Transacao:: ValidarDados(){
        if (valor <= 0) {
        return 0; // Inválido
        }
        return 1; // Válido
    }        

    //Percorre vetor de lançamento de conta e recalcula, atualiza saldo e divida Final da propria transacao. 
    void Transacao :: updateSaldoEDivida(){
        using namespace std::chrono;
        std::chrono::year_month_day hoje = floor<days>(system_clock::now());

        for(auto it = conta->lancamentosFuturos.begin(); it != conta-> lancamentosFuturos.end();){
            Lancamentos* l = *it;
            if (!l->processado) {
                // Acumula (+=/-=) para considerar todos os lancamentos pendentes
                if (l-> tipo == Lancamentos::TipoDespesa && l-> data > hoje){
                    dividaFinal += l-> valor;
                }else if(l-> tipo == Lancamentos::TipoDespesa){
                    saldoFinal -= l-> valor;
                }else if (l-> tipo == Lancamentos::TipoReceita && l-> data <= hoje){
                    saldoFinal += l-> valor;
                }
                l->processado = true;
            }
            if(!l->LancamentoFixo){
                it = conta->lancamentosFuturos.erase(it); // erase devolve o proximo
            }else{
                ++it;
            }
        }
    } 
    
    //Adiciona a transacao atual na lista de transacao da classe conta toda vez que um objeto transacao eh criado.    
    bool Transacao::updateListaTransacao(){
        if(saldoFinal != saldoAnterior || dividaFinal != dividaAnterior){
            conta-> addTransacao(this);
            return true;
        }
        return false;
    }   

