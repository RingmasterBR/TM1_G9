#include <stdexcept>

#include "doctest.h"
#include "categoria.hpp"

TEST_CASE("Categoria - criacao com nome e getters") {
    Categoria categoria("Mercado", Alimentacao, Debito);

    CHECK(categoria.getNome() == "Mercado");
    CHECK(categoria.getTipo() == Alimentacao);
    CHECK(categoria.getFormaPagamento() == Debito);
}

TEST_CASE("Categoria - sem nome usa o nome do tipo de gasto") {
    CHECK(Categoria(Alimentacao, Pix).getNome() == "Alimentacao");
    CHECK(Categoria(Transporte, Pix).getNome() == "Transporte");
    CHECK(Categoria(Lazer, Pix).getNome() == "Lazer");
    CHECK(Categoria(Saude, Pix).getNome() == "Saude");
    CHECK(Categoria(Educacao, Pix).getNome() == "Educacao");
    CHECK(Categoria(Outros, Pix).getNome() == "Outros");
}

TEST_CASE("Categoria - conversao de forma de pagamento para texto") {
    CHECK(Categoria::formaParaTexto(Credito) == "Credito");
    CHECK(Categoria::formaParaTexto(Debito) == "Debito");
    CHECK(Categoria::formaParaTexto(Pix) == "Pix");
}

TEST_CASE("Categoria - valores fora do enum lancam excecao") {
    CHECK_THROWS_AS(Categoria(static_cast<TipoGasto>(99), Pix), std::invalid_argument);
    CHECK_THROWS_AS(Categoria("X", Lazer, static_cast<FormaPagamento>(-1)), std::invalid_argument);
}
