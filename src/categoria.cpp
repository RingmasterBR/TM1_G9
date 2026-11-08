#include "categoria.hpp"

// Construtor: Inicializa os atributos privados com os valores recebidos
Categoria::Categoria(TipoGasto tipo, FormaPagamento forma) 
    : nome(""), tipoGasto(tipo), formaPagamento(forma) {}

// Construtor com nome personalizado
Categoria::Categoria(std::string nomeCategoria, TipoGasto tipo, FormaPagamento forma)
    : nome(nomeCategoria), tipoGasto(tipo), formaPagamento(forma) {}

// Retorna o nome dado pelo usuario ou, se nao houver, o nome do tipo de gasto
std::string Categoria::getNome() {
    if (!nome.empty()) {
        return nome;
    }
    switch (tipoGasto) {
        case Alimentacao: return "Alimentacao";
        case Transporte:  return "Transporte";
        case Lazer:       return "Lazer";
        case Saude:       return "Saude";
        case Educacao:    return "Educacao";
        default:          return "Outros";
    }
}

// Retorna o tipo de gasto (ex: Alimentacao, Transporte, Lazer, etc.)
TipoGasto Categoria::getTipo() {
    return tipoGasto;
}

// Retorna a forma de pagamento (ex: Credito, Debito, Pix)
FormaPagamento Categoria::getFormaPagamento() {
    return formaPagamento;
}