#include <chrono>

#include "doctest.h"
#include "usuario.hpp"
#include "conta.hpp"
#include "categoria.hpp"
#include "despesa.hpp"

using namespace std::chrono;

TEST_CASE("Despesa - construcao") {
    Usuario usuario("Carlos", 1);
    Conta conta(&usuario, "Corrente");
    Categoria categoria(Alimentacao, Pix);
    Despesa despesa(1500.0, &categoria, year(2026) / 10 / 15, &conta, true);

    CHECK(despesa.getValor() == 1500.0);
    CHECK(despesa.isDespesa());
    CHECK(despesa.isFixo());
    CHECK(despesa.getTipoTexto() == "Despesa");
}

TEST_CASE("Despesa - data passada ou de hoje diminui o saldo") {
    Usuario usuario("Carlos", 1);
    Conta conta(&usuario, "Corrente");
    Categoria categoria(Alimentacao, Pix);
    year_month_day hoje = year(2026) / 10 / 15;

    Despesa passada(100.0, &categoria, year(2026) / 10 / 1, &conta, false);
    Despesa deHoje(50.0, &categoria, hoje, &conta, false);

    double saldo = 1000.0;
    double divida = 0.0;
    CHECK(passada.aplicarEfeito(saldo, divida, hoje));
    CHECK(deHoje.aplicarEfeito(saldo, divida, hoje));
    CHECK(saldo == 850.0);
    CHECK(divida == 0.0);
}

TEST_CASE("Despesa - data futura aumenta a divida") {
    Usuario usuario("Carlos", 1);
    Conta conta(&usuario, "Corrente");
    Categoria categoria(Educacao, Credito);
    Despesa futura(300.0, &categoria, year(2026) / 12 / 10, &conta, false);

    double saldo = 1000.0;
    double divida = 0.0;
    CHECK(futura.aplicarEfeito(saldo, divida, year(2026) / 10 / 15));
    CHECK(saldo == 1000.0);
    CHECK(divida == 300.0);
}
