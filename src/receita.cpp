#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <chrono>
#include "Receita.hpp"
#include "Conta.hpp"
#include "Categoria.hpp"
#include "Usuario.hpp"

TEST_CASE("Testando a classe Receita e suas operações") {
    // Configuração prévia de dependências necessárias
    Usuario usuario("Ana Salario", 404, "senha789");
    Conta conta(&usuario, "Conta Salário");
    Categoria categoria("Trabalho");
    
    // Definindo uma data padrão usando std::chrono (C++20)
    std::year_month_day dataExemplo{std::chrono::year(2026), std::chrono::month(10), std::chrono::day(5)};

    SUBCASE("Construção e verificação de atributos de uma Receita") {
        // Criando uma receita fixa de 5000.00
        Receita receita(5000.00, &categoria, dataExemplo, &conta, true);

        CHECK(receita.valor == 5000.00);
        CHECK(receita.tipo == Lancamentos::TipoReceita);
        CHECK(receita.LancamentoFixo == true);
        CHECK(receita.conta == &conta);
        CHECK(receita.categoria == &categoria);
    }

    SUBCASE("Adicionando receita aos lançamentos futuros da conta") {
        Receita receita(250.00, &categoria, dataExemplo, &conta, false);

        // Executando o método que adiciona à conta
        receita.addLancamentosFuturos();

        // Verificamos que a operação ocorre sem erros e mantém o estado correto
        CHECK(receita.valor == 250.00);
        CHECK(receita.LancamentoFixo == false);
    }
}