#include <chrono>
#include <stdexcept>

#include "doctest.h"
#include "usuario.hpp"
#include "conta.hpp"
#include "categoria.hpp"
#include "despesa.hpp"
#include "receita.hpp"
#include "orcamento.hpp"

using namespace std::chrono;

TEST_CASE("Orcamento - criacao e limite") {
    Categoria categoria("Lazer", Lazer, Pix);
    Orcamento orcamento(500.0, &categoria, 10, 2026);

    CHECK(orcamento.getLimite() == 500.0);
    CHECK(orcamento.getValorGasto() == 0.0);
    CHECK(orcamento.getCategoria() == &categoria);
    CHECK(orcamento.getMes() == 10);
    CHECK(orcamento.getAno() == 2026);
    CHECK_FALSE(orcamento.estourouLimite());

    orcamento.setLimite(800.0);
    CHECK(orcamento.getLimite() == 800.0);
}

TEST_CASE("Orcamento - soma despesas e detecta estouro") {
    Usuario usuario("Ana", 1);
    Conta conta(&usuario, "Corrente");
    Categoria lazerPix(Lazer, Pix);
    Categoria lazerCredito(Lazer, Credito);
    Orcamento orcamento(200.0, &lazerPix, 10, 2026);

    Despesa cinema(150.0, &lazerPix, year(2026) / 10 / 10, &conta, false);
    CHECK(orcamento.adicionarLancamento(&cinema));
    CHECK(orcamento.getValorGasto() == 150.0);
    CHECK(orcamento.getSaldoRestante() == 50.0);
    CHECK_FALSE(orcamento.estourouLimite());

    // mesmo tipo de gasto com outra forma de pagamento tambem conta
    Despesa show(100.0, &lazerCredito, year(2026) / 10 / 12, &conta, false);
    CHECK(orcamento.adicionarLancamento(&show));
    CHECK(orcamento.getValorGasto() == 250.0);
    CHECK(orcamento.getSaldoRestante() == -50.0);
    CHECK(orcamento.estourouLimite());
}

TEST_CASE("Orcamento - ignora lancamentos que nao pertencem a ele") {
    Usuario usuario("Ana", 1);
    Conta conta(&usuario, "Corrente");
    Categoria lazer(Lazer, Pix);
    Categoria mercado(Alimentacao, Debito);
    Orcamento orcamento(200.0, &lazer, 10, 2026);

    Receita receita(1000.0, &lazer, year(2026) / 10 / 5, &conta, false);
    Despesa outroTipo(50.0, &mercado, year(2026) / 10 / 5, &conta, false);
    Despesa outroMes(50.0, &lazer, year(2026) / 11 / 5, &conta, false);
    Despesa outroAno(50.0, &lazer, year(2025) / 10 / 5, &conta, false);

    CHECK_FALSE(orcamento.adicionarLancamento(&receita));
    CHECK_FALSE(orcamento.adicionarLancamento(&outroTipo));
    CHECK_FALSE(orcamento.adicionarLancamento(&outroMes));
    CHECK_FALSE(orcamento.adicionarLancamento(&outroAno));
    CHECK_FALSE(orcamento.adicionarLancamento(nullptr));
    CHECK(orcamento.getValorGasto() == 0.0);
}

TEST_CASE("Orcamento - parametros invalidos lancam excecao") {
    Categoria categoria(Lazer, Pix);
    CHECK_THROWS_AS(Orcamento(0.0, &categoria, 10, 2026), std::invalid_argument);
    CHECK_THROWS_AS(Orcamento(-1.0, &categoria, 10, 2026), std::invalid_argument);
    CHECK_THROWS_AS(Orcamento(100.0, nullptr, 10, 2026), std::invalid_argument);
    CHECK_THROWS_AS(Orcamento(100.0, &categoria, 0, 2026), std::invalid_argument);
    CHECK_THROWS_AS(Orcamento(100.0, &categoria, 13, 2026), std::invalid_argument);

    Orcamento orcamento(100.0, &categoria, 10, 2026);
    CHECK_THROWS_AS(orcamento.setLimite(0.0), std::invalid_argument);
    CHECK(orcamento.getLimite() == 100.0);
}
