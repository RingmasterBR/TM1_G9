#ifndef TRANSACAO_HPP
#define TRANSACAO_HPP

//Inclusoes propria c++
#include <iostream>
#include <string>

//Inclusoes do projeto
#include "usuario.hpp"
#include "conta.hpp"
#include "receita.hpp"
#include "despesa.hpp"
#include "categoria.hpp"

//Todas as operacoes do projeto que envolvam arualizacao do saldo ou da divida da conta devem ser feitas pela classe transacao
class Transacao {
//Classe majoritariamente privada, metodos nao podem ser sobrescritos
    public :
        enum TipoTransacao { Entrada, Saida };
        enum FormaPagamento {Credito, Debito, Pix, Transferencia};
        Categoria& categoria;
        
        //Sobrecarga de construtor
        //Construtor padrao
        Transacao(){}
        //Contrutor para transacoes gerais
        Transacao(const Conta& conta, TipoTransacao tipo, FormaPagamento categoria, Categoria& categoria, double valor){}

        //Validar dados de transacao:
        int ValidarDados();

        //Recebe divida final ou saldo final disponibilizado por metodo da classe de despesa ou de receita e retorna o saldo final apos a transacao registrada.
        double getSaldoFinal(double valor) const;
        double getDividaFinal(double valor) const;

        //Disponibiliza o tipo de transacao e a categoria.
        std::string getTipoTransacao() const;
        std::string getCategoria() const;
        Despesa getDespesa() const;
        Receita getReceita() const;

        //Deve retornar uma string com a transacao realizada, o tipo, o valor, o saldo final e inicial.
        std::string getTransacao() const;
    
    private :
        //Atributos:
        double saldoFinal;
        double dividaFinal;

        //Calcula e retorna o novo valor do saldo da conta: 
        double updateSaldo(const Conta& conta, TipoTransacao tipo, CategoriaTransacao categoria, double valor);

        //Sobrecarga de metodo updateSaldo, serve para atualizar o saldo considerando a data das receitas e das despesas
        //Metodo deve percorrer a lista de receitas e verificar se nao ha nenhuma receita ou despesa para o dia atual e realizar a atualizacao do saldo
        double updateSaldo(const Conta&, conta, TipoTransacao tipo, CategoriaTransacao categoria, Receita receita);
        double updateSaldo(const Conta&, conta, TipoTransacao tipo, CategoriaTransacao categoria, Receita despesa);

        //Calcula e retorna o novo valor da divida da conta:
        double updateDivida(const Conta& conta, TipoTransacao tipo, CategoriaTransacao categoria, double valor);

        //Metodos
        //Atualiza o saldo final e a divida final da conta. 
        double setSaldoFinal(double valor, Conta& conta);
        double setDividaFinal(double valor,Conta& conta);
        
        //Calcula e retorna o novo valor da divida
    };

#endif