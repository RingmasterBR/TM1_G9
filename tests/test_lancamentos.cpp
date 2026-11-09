#include <chrono>
#include <stdexcept>

#include "doctest.h"
#include "usuario.hpp"
#include "conta.hpp"
#include "categoria.hpp"
#include "despesa.hpp"
#include "receita.hpp"

using namespace std::chrono;

// Lancamentos e abstrata: os testes usam as subclasses por ponteiro da classe base.

TEST_CASE("Lancamentos - getters pela classe base") {
    Usuario usuario("Ana", 1);
    Conta conta(&usuario, "Corrente");
    Categoria categoria(Saude, Credito);
    year_month_day data = year(2026) / 10 / 20;

    Despesa despesa(80.0, &categoria, data, &conta, true);
    Lancamentos* lancamento = &despesa;

    CHECK(lancamento->getValor() == 80.0);
    CHECK(lancamento->getCategoria() == &categoria);
    CHECK(lancamento->getData() == data);
    CHECK(lancamento->getConta() == &conta);
    CHECK(lancamento->isFixo());
    CHECK_FALSE(lancamento->isProcessado());

    lancamento->marcarProcessado();
    CHECK(lancamento->isProcessado());
}

TEST_CASE("Lancamentos - polimorfismo entre Receita e Despesa") {
    Usuario usuario("Ana", 1);
    Conta conta(&usuario, "Corrente");
    Categoria categoria(Outros, Pix);
    year_month_day data = year(2026) / 10 / 20;

    Receita receita(100.0, &categoria, data, &conta, false);
    Despesa despesa(30.0, &categoria, data, &conta, false);
    Lancamentos* lancamentos[] = {&receita, &despesa};

    double saldo = 0.0;
    double divida = 0.0;
    year_month_day hoje = year(2026) / 11 / 1;
    for (Lancamentos* lancamento : lancamentos) {
        lancamento->aplicarEfeito(saldo, divida, hoje);
    }

    CHECK(saldo == 70.0);
    CHECK(divida == 0.0);
    CHECK(lancamentos[0]->getTipoTexto() == "Receita");
    CHECK(lancamentos[1]->getTipoTexto() == "Despesa");
    CHECK_FALSE(lancamentos[0]->isDespesa());
    CHECK(lancamentos[1]->isDespesa());
}

TEST_CASE("Lancamentos - adicionarNaConta e realizarTransacao") {
    Usuario usuario("Ana", 1);
    Conta conta(&usuario, "Corrente");
    Categoria categoria(Outros, Pix);
    Receita receita(500.0, &categoria, year(2026) / 10 / 1, &conta, false);

    receita.adicionarNaConta();
    receita.realizarTransacao();

    CHECK(conta.getLancamentos().size() == 1);
    CHECK(conta.getTransacoes().size() == 1);
    CHECK(conta.getSaldo() == 500.0);
    CHECK(receita.isProcessado());

    // Nada pendente: a nova transacao nao muda nada e e descartada
    receita.realizarTransacao();
    CHECK(conta.getTransacoes().size() == 1);
}

TEST_CASE("Lancamentos - parametros invalidos lancam excecao") {
    Usuario usuario("Ana", 1);
    Conta conta(&usuario, "Corrente");
    Categoria categoria(Outros, Pix);
    year_month_day dataValida = year(2026) / 10 / 1;
    year_month_day dataInvalida = year(2026) / 2 / 30;

    CHECK_THROWS_AS(Despesa(0.0, &categoria, dataValida, &conta, false), std::invalid_argument);
    CHECK_THROWS_AS(Despesa(-10.0, &categoria, dataValida, &conta, false), std::invalid_argument);
    CHECK_THROWS_AS(Despesa(10.0, nullptr, dataValida, &conta, false), std::invalid_argument);
    CHECK_THROWS_AS(Receita(10.0, &categoria, dataInvalida, &conta, false), std::invalid_argument);
    CHECK_THROWS_AS(Receita(10.0, &categoria, dataValida, nullptr, false), std::invalid_argument);
}
