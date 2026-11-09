#include <chrono>
#include <stdexcept>

#include "doctest.h"
#include "usuario.hpp"
#include "conta.hpp"
#include "categoria.hpp"
#include "despesa.hpp"
#include "receita.hpp"
#include "transacao.hpp"
#include "interfaceterminal.hpp"

using namespace std::chrono;

TEST_CASE("Transacao - conta sem lancamentos nao altera nada") {
    Usuario usuario("Carlos", 1);
    Conta conta(&usuario, "Corrente");
    Transacao transacao(&conta, 100.0);

    CHECK(transacao.getConta() == &conta);
    CHECK(transacao.getValor() == 100.0);
    CHECK(transacao.getSaldoAnterior() == 0.0);
    CHECK(transacao.getDividaAnterior() == 0.0);
    CHECK(transacao.getSaldoFinal() == 0.0);
    CHECK(transacao.getDividaFinal() == 0.0);
    CHECK_FALSE(transacao.registrarNaConta());
    CHECK(conta.getTransacoes().empty());
}

TEST_CASE("Transacao - aplica os lancamentos pendentes da conta") {
    Usuario usuario("Carlos", 1);
    Conta conta(&usuario, "Corrente");
    Categoria categoria(Outros, Pix);
    year_month_day hoje = InterfaceTerminal::hoje();
    year_month_day futuro = sys_days(hoje) + days(40);

    Receita receita(1000.0, &categoria, hoje, &conta, false);
    Despesa despesa(200.0, &categoria, hoje, &conta, false);
    Despesa parcela(300.0, &categoria, futuro, &conta, false);
    conta.addLancamento(&receita);
    conta.addLancamento(&despesa);
    conta.addLancamento(&parcela);

    Transacao* transacao = new Transacao(&conta, 1000.0);
    CHECK(transacao->getSaldoFinal() == 800.0);
    CHECK(transacao->getDividaFinal() == 300.0);
    REQUIRE(transacao->registrarNaConta()); // a conta passa a ser dona da transacao

    CHECK(conta.getSaldo() == 800.0);
    CHECK(conta.getDivida() == 300.0);
    CHECK(receita.isProcessado());
    CHECK(parcela.isProcessado());
}

TEST_CASE("Transacao - conta nula lanca excecao") {
    CHECK_THROWS_AS(Transacao(nullptr, 10.0), std::invalid_argument);
}
