#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Lancamentos.hpp"
#include "Conta.hpp"
#include "Categoria.hpp"

TEST_CASE("Testando a classe Lancamentos e seus atributos") {
    // Instanciação do objeto Lancamentos
    Lancamentos lancamento;

    SUBCASE("Definindo e verificando atributos básicos de uma Receita") {
        lancamento.valor = 250.50;
        lancamento.tipo = Lancamentos::TipoReceita;
        lancamento.LancamentoFixo = false;

        CHECK(lancamento.valor == 250.50);
        CHECK(lancamento.tipo == Lancamentos::TipoReceita);
        CHECK(lancamento.LancamentoFixo == false);
    }

    SUBCASE("Definindo e verificando atributos básicos de uma Despesa Fixa") {
        lancamento.valor = 1200.00;
        lancamento.tipo = Lancamentos::TipoDespesa;
        lancamento.LancamentoFixo = true;

        CHECK(lancamento.valor == 1200.00);
        CHECK(lancamento.tipo == Lancamentos::TipoDespesa);
        CHECK(lancamento.LancamentoFixo == true);
    }
}