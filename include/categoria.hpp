#ifndef CATEGORIA_HPP
#define CATEGORIA_HPP

#include <iostream>
#include <string>

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
    std::string nome;
    TipoGasto tipoGasto;
    FormaPagamento formaPagamento;

public:

    Categoria(TipoGasto tipo, FormaPagamento forma);

    Categoria(std::string nomeCategoria, TipoGasto tipo, FormaPagamento forma);

    // Retorna o nome da categoria. Se nenhum nome foi dado, usa o nome do tipo de gasto.
    std::string getNome();
    
    // getters
    TipoGasto getTipo();
    FormaPagamento getFormaPagamento();
};

#endif