#ifndef CATEGORIA_HPP
#define CATEGORIA_HPP

#include <iostream>

enum TipoGasto {
    Alimentacao,
    Transporte,
    Lazer,
    Saude,
    Educacao,
    Outros
};

enum FormaPagamento {
    Credito,
    Debito,
    Pix
};

class Categoria {
private:
    TipoGasto tipoGasto;
    FormaPagamento formaPagamento;

public:
    // Construtor alinhado com o src/categoria.cpp
    Categoria(TipoGasto tipo, FormaPagamento forma);
    
    // Métodos leitores (*getters*)
    TipoGasto getTipo();
    FormaPagamento getFormaPagamento();
};

#endif