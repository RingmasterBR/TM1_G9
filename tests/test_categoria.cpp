#include "doctest.h"
#include "categoria.hpp"

TEST_CASE("Categoria - Criacao e getters basicos") {
    Categoria cat("Mercado", TipoGasto::Alimentacao, FormaPagamento::Debito);
 
    CHECK(cat.getNome() == "Mercado");
    CHECK(cat.getTipo() == TipoGasto::Alimentacao);
    CHECK(cat.getFormaPagamento() == FormaPagamento::Debito);
}

TEST_CASE("Categoria - Todos os tipos de gasto") {
    Categoria a("A", TipoGasto::Alimentacao, FormaPagamento::Pix);
    Categoria b("B", TipoGasto::Transporte, FormaPagamento::Pix);
    Categoria c("C", TipoGasto::Lazer, FormaPagamento::Pix);
    Categoria d("D", TipoGasto::Saude, FormaPagamento::Pix);
    Categoria e("E", TipoGasto::Educacao, FormaPagamento::Pix);
    Categoria f("F", TipoGasto::Outros, FormaPagamento::Pix);
 
    CHECK(a.getTipo() == TipoGasto::Alimentacao);
    CHECK(b.getTipo() == TipoGasto::Transporte);
    CHECK(c.getTipo() == TipoGasto::Lazer);
    CHECK(d.getTipo() == TipoGasto::Saude);
    CHECK(e.getTipo() == TipoGasto::Educacao);
    CHECK(f.getTipo() == TipoGasto::Outros);
}
