#ifndef TRANSACAO_HPP
#define TRANSACAO_HPP

//Inclusoes propria c++
#include <iostream>
#include <string>

//Inclusoes do projeto
#include "usuario.hpp"
#include "conta.hpp"
#include "categoria.hpp"
#include "tipotransacao"


class Transacao {
//Classe completamente privada, metodos nao podem ser sobrescritos
    private :
        double saldoFinal;
        double dividaFinal;
    
    public :
        //Sobrecarga de construtor
        Transacao(){}
        Transacao(const Conta& conta, TipoTransacao tipo, double valor){}

        //Atualiza o saldo da conta: 
        double updateSaldo(double valor, const TipoTransacao tipo, double saldoAtual, const Categoria& categoria);

        //Atualiza a divida da conta:
        double updateDivida(double valor, const TipoTransacao tipo, double dividaAtual,  const Categoria& categoria);

        //Validar dados de transacao:
        int ValidarDados();

        //Atualiza o saldo final.
        double setSaldoFinal();
        double setSaldoFinal();

        //Disponibiliza o saldo final.
        double getSaldoFinal() const;
        double getSaldoFinal() const;

        //Deve retornar a transacao realizada, o tipo, o valor, o saldo final e inicial.
        std::string getTransacao();
};

#endif