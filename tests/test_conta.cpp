#include <chrono>
#include <stdexcept>

#include "doctest.h"
#include "usuario.hpp"
#include "conta.hpp"
#include "categoria.hpp"
#include "despesa.hpp"
#include "transacao.hpp"

using namespace std::chrono;

TEST_CASE("Conta - valores iniciais") {
    Usuario usuario("Maria", 1);
    Conta conta(&usuario, "Poupanca");

    CHECK(conta.getNome() == "Poupanca");
    CHECK(conta.getUsuario() == &usuario);
    CHECK(conta.getSaldo() == 0.0);
    CHECK(conta.getDivida() == 0.0);
    CHECK(conta.getLancamentos().empty());
    CHECK(conta.getTransacoes().empty());
}

TEST_CASE("Conta - adicionar lancamento ao historico") {
    Usuario usuario("Maria", 1);
    Conta conta(&usuario, "Corrente");
    Categoria categoria(Lazer, Pix);
    Despesa despesa(50.0, &categoria, year(2026) / 10 / 5, &conta, false);

    conta.addLancamento(&despesa);

    CHECK(conta.getLancamentos().size() == 1);
    // so adicionar nao altera o saldo: quem altera e a Transacao
    CHECK(conta.getSaldo() == 0.0);
}

TEST_CASE("Conta - parametros invalidos lancam excecao") {
    Usuario usuario("Maria", 1);
    CHECK_THROWS_AS(Conta(&usuario, ""), std::invalid_argument);

    Conta conta(&usuario, "Corrente");
    Conta outra(&usuario, "Outra");
    Categoria categoria(Lazer, Pix);
    Despesa daOutraConta(10.0, &categoria, year(2026) / 10 / 5, &outra, false);

    CHECK_THROWS_AS(conta.addLancamento(nullptr), std::invalid_argument);
    CHECK_THROWS_AS(conta.addLancamento(&daOutraConta), std::invalid_argument);
    CHECK_THROWS_AS(conta.addTransacao(nullptr), std::invalid_argument);
}
