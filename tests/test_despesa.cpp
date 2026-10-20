
#include <chrono>

#include "despesa.hpp"
#include "conta.hpp"
#include "categoria.hpp"
#include "usuario.hpp"
#include "doctest.h"


TEST_CASE("Testando a classe Despesa e suas operacoes") {
    Usuario usuario("Carlos Aluguel", 303, "senha123");
    Conta conta(&usuario, "Conta Corrente");
    
    // Ajuste os parâmetros de Categoria conforme o seu enum real em Categoria.hpp
    Categoria categoria(TipoGasto::Alimentacao, FormaPagamento::Pix); 

    // Adicionado o 'std::chrono::' para o compilador encontrar o tipo correto
    std::chrono::year_month_day dataExemplo{std::chrono::year(2026), std::chrono::month(10), std::chrono::day(15)};

    SUBCASE("Construção e verificação de atributos de uma Despesa") {
        Despesa despesa(1500.00, &categoria, dataExemplo, &conta, true);

        CHECK(despesa.valor == 1500.00);
        CHECK(despesa.tipo == Lancamentos::TipoDespesa);
        CHECK(despesa.LancamentoFixo == true);
        CHECK(despesa.conta == &conta);
        CHECK(despesa.categoria == &categoria);
    }

    SUBCASE("Adicionando despesa aos lançamentos futuros da conta") {
        Despesa despesa(350.00, &categoria, dataExemplo, &conta, false);
        despesa.addLancamentosFuturos();

        CHECK(despesa.valor == 350.00);
        CHECK(despesa.LancamentoFixo == false);
    }
}