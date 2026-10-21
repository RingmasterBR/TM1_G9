#include "categoria.hpp"

// Construtor: Inicializa os atributos privados com os valores recebidos
Categoria::Categoria(TipoGasto tipo, FormaPagamento forma) 
    : tipoGasto(tipo), formaPagamento(forma) {}

// Retorna o tipo de gasto (ex: Alimentacao, Transporte, Lazer, etc.)
TipoGasto Categoria::getTipo() {
    return tipoGasto;
}

// Retorna a forma de pagamento (ex: Credito, Debito, Pix)
FormaPagamento Categoria::getFormaPagamento() {
    return formaPagamento;
}