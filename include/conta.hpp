ifndef CONTA_HPP
#define CONTA_HPP
 
#include <iostream>
#include <list>

#include "usuario.hpp"
#include "lancamentos.hpp"
#include "transacao.hpp"

 
class Conta {
 
    private :
        Usuario user; //Usuario da conta
        double saldo; //Valor atual do saldo da conta
        double divida; //Valor atual da divida da conta
        void setSaldo(); //Metodo deve setar saldo igual ao saldo final da ultima transacao da lista de transacoes
        void setDivida(); //Metodo deve setar divida igual ao saldo final da ultima transacao da lista de transacoes
        std::list<Lancamentos*>lancamentosFuturos; //Lista de lancamentos da conta 
        std::list<Transacao*>listaTransacao; //Lista de transacoes da conta
 
    public :
        void addLancamento(Lancamento* lancamento);
        void addTransacao(Transacao* transacao);

        //Construtor:
        Conta(std::string nome, int id); //Recebe o nome e o ID do usuario. 

        //Metodos publicos
        double getSaldo();
        double getDivida();         
};
 
#endif
