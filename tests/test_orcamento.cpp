#include "doctest.h"
#include "orcamento.hpp"
#include "despesa.hpp"
#include "categoria.hpp"

TEST_CASE("Orcamento - Criacao e definicao de limites") {
    Categoria cat("Lazer");
    Orcamento orc(&cat, 500.0);

    CHECK(orc.getLimite() == 500.0);
    CHECK(orc.getValorGasto() == 0.0);
    CHECK(orc.isExcedido() == false);
}

TEST_CASE("Orcamento - Adicao de despesas e controle de limite") {
    Categoria cat("Lazer");
    Orcamento orc(&cat, 200.0);

    Despesa d1(150.0, "Cinema e Pipoca", &cat, "10/10/2026");
    orc.adicionarTransacao(&d1);

    CHECK(orc.getValorGasto() == 150.0);
    CHECK(orc.isExcedido() == false);

    Despesa d2(100.0, "Restaurante", &cat, "12/10/2026");
    orc.adicionarTransacao(&d2);

    CHECK(orc.getValorGasto() == 250.0);
    CHECK(orc.isExcedido() == true);
}