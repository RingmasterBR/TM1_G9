#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <chrono>

#include "Despesa.hpp"
#include "Conta.hpp"
#include "Categoria.hpp"
#include "Usuario.hpp"

TEST_CASE("Testando a classe Despesa e suas operações") {
    // Configuração prévia de dependências necessárias
    Usuario usuario("Carlos Aluguel", 303, "senha123");
    Conta conta(&usuario, "Conta Corrente");
    Categoria categoria("Moradia");
    
    // Definindo uma data padrão usando std::chrono (C++20)
    std::year_month_day dataExemplo{std::chrono::year(2026), std::chrono::month(10), std::chrono::day(15)};

    SUBCASE("Construção e verificação de atributos de uma Despesa") {
        // Criando uma despesa fixa de 1500.00
        Despesa despesa(1500.00, &categoria, dataExemplo, &conta, true);

        CHECK(despesa.valor == 1500.00);
        CHECK(despesa.tipo == Lancamentos::TipoDespesa);
        CHECK(despesa.LancamentoFixo == true);
        CHECK(despesa.conta == &conta);
        CHECK(despesa.categoria == &categoria);
    }

    SUBCASE("Adicionando despesa aos lançamentos futuros da conta") {
        Despesa despesa(350.00, &categoria, dataExemplo, &conta, false);

        // Executando o método que adiciona à conta
        despesa.addLancamentosFuturos();

        // Verificamos que a operação ocorreu sem erros
        CHECK(despesa.valor == 350.00);
        CHECK(despesa.LancamentoFixo == false);
    }
}