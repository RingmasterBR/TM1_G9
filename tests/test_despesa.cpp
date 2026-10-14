#include "doctest.h"
#include "despesa.hpp"
#include "categoria.hpp"

TEST_CASE("Despesa - Criacao e getters basicos") {
    Categoria cat("Alimentacao");
    Despesa d(150.0, "Mercado", &cat, "14/10/2026", false);

    CHECK(d.getValor() == 150.0);
    CHECK(d.getDescricao() == "Mercado");
    CHECK(d.isFixa() == false);
    CHECK(d.getDiaCobranca() == 0);
}

TEST_CASE("Despesa - Configuração de despesa fixa") {
    Categoria cat("Moradia");
    Despesa d(1200.0, "Aluguel", &cat, "01/10/2026", true, 5);

    CHECK(d.isFixa() == true);
    CHECK(d.getDiaCobranca() == 5);

    d.setDiaCobranca(10);
    CHECK(d.getDiaCobranca() == 10);

    d.setFixa(false);
    CHECK(d.isFixa() == false);
}