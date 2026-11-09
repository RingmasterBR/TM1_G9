#include <chrono>

#include "doctest.h"
#include "usuario.hpp"
#include "conta.hpp"
#include "categoria.hpp"
#include "receita.hpp"

using namespace std::chrono;

TEST_CASE("Receita - construcao") {
    Usuario usuario("Ana", 1);
    Conta conta(&usuario, "Salario");
    Categoria categoria(Outros, Pix);
    Receita receita(5000.0, &categoria, year(2026) / 10 / 5, &conta, true);

    CHECK(receita.getValor() == 5000.0);
    CHECK_FALSE(receita.isDespesa());
    CHECK(receita.isFixo());
    CHECK(receita.getTipoTexto() == "Receita");
}

TEST_CASE("Receita - data passada aumenta o saldo") {
    Usuario usuario("Ana", 1);
    Conta conta(&usuario, "Salario");
    Categoria categoria(Outros, Pix);
    Receita receita(250.0, &categoria, year(2026) / 10 / 5, &conta, false);

    double saldo = 100.0;
    double divida = 40.0;
    CHECK(receita.aplicarEfeito(saldo, divida, year(2026) / 10 / 5));
    CHECK(saldo == 350.0);
    CHECK(divida == 40.0);
}

TEST_CASE("Receita - data futura fica pendente") {
    Usuario usuario("Ana", 1);
    Conta conta(&usuario, "Salario");
    Categoria categoria(Outros, Pix);
    Receita receita(250.0, &categoria, year(2026) / 12 / 5, &conta, false);

    double saldo = 100.0;
    double divida = 0.0;
    CHECK_FALSE(receita.aplicarEfeito(saldo, divida, year(2026) / 10 / 5));
    CHECK(saldo == 100.0);
}
