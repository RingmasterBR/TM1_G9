#include <chrono>

#include "receita.hpp"
#include "conta.hpp"
#include "categoria.hpp"
#include "usuario.hpp"
#include "doctest.h"


TEST_CASE("Testando a classe Receita e suas operacoes") {
    // Configuração prévia de dependências necessárias
    Usuario usuario("Ana Salario", 404, "senha789");
    Conta conta(&usuario, "Conta Salário");
    
    // Instanciando categoria conforme os enums definidos em categoria.hpp
    Categoria categoria(TipoGasto::Educacao, FormaPagamento::Pix);
    
    // Definindo uma data padrão usando std::chrono::year_month_day (C++20)
    std::chrono::year_month_day dataExemplo{std::chrono::year(2026), std::chrono::month(10), std::chrono::day(5)};

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