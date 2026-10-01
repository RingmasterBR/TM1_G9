#ifndef CATEGORIA_HPP
#define CATEGORIA_HPP

//Inclusoes propria c++
#include <iostream>
#include <string>
#include <list>

//Inclusoes do projeto
#include "usuario.hpp"
#include "conta.hpp"
#include "transacao.hpp"


class Categoria : public Transacao{
//Classe completamente privada, metodos nao podem ser sobrescritos
    
    public :
    //Atributos
        //lista de todas as transacoes
        std::list transacoes;

        //Lista todos os gastos por categoria;
        std::list categorias;
        enum categoriaGasto {Alimentacao, Saude, Moradia, Transporte, Lazer};
        string&

        //Sobrecarga de construtor, construtor sem parametro deve possuir atributos ' ' por padrao.
        Categoria(){}

        //Implementacao deve inserir transacoes na lista.
        std::list InserirTransacoes(const Transacao& transacao);
        
        //Implementacao deve inserir transacoes na lista.
        enum getCategoriaGasto();

        //Implementacao deve retornar a lista com todas as transacoes
        std::list getListaTransacoes(const Transacao& transacao);

        //Implementacao deve retornar a lista da transacoes por categoria
        std::list getListaTransacoesPix(std::list transacoes; Transacao& transacao);
};

#endif