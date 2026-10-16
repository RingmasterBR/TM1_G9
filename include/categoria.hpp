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
    Categoria(TipoGasto tipo, FormaPagamento forma);
    TipoGasto getTipo();
    FormaPagamento getFormaPagamento();
};
 
#endif


