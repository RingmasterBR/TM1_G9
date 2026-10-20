#ifndef CONTA_HPP
#define CONTA_HPP
 
#include <iostream>
#include <list>
#include <string>

#include "transacao.hpp"

// Forward declaration para evitar dependência circular com Usuario
class Usuario;
class Lancamentos;

class Conta {
    private :
        Usuario* user; // Ponteiro para o usuário dono da conta
        double saldo; 
        double divida; 
        void setSaldo(); 
        void setDivida(); 
        std::list<Lancamentos*> lancamentosFuturos; 
        std::list<Transacao*> listaTransacao; 

    public :
        std::string NomeDaConta;

        void addLancamento(Lancamentos* lancamento);
        void addTransacao(Transacao* transacao);

        // Construtor atualizado para receber também o ponteiro do usuário e o nome da conta
        Conta(Usuario* usuario, std::string nomeDaContaAtual); 

        double getSaldo();
        double getDivida();   
};
 
#endif