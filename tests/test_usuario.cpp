#include <stdexcept>

#include "doctest.h"
#include "usuario.hpp"
#include "conta.hpp"
#include "gerenciadorfinanceiro.hpp"

TEST_CASE("Usuario - dados iniciais") {
    Usuario usuario("Carlos Silva", 101, "senhaSegura123");

    CHECK(usuario.getId() == 101);
    CHECK(usuario.getNome() == "Carlos Silva");
    CHECK(usuario.getContas().empty());
    REQUIRE(usuario.getGerenciadorFinanceiro() != nullptr);
    CHECK(usuario.getGerenciadorFinanceiro()->getUsuario() == &usuario);
}

TEST_CASE("Usuario - autenticacao") {
    Usuario usuario("Carlos", 1, "abc");

    CHECK(usuario.autenticar("abc"));
    CHECK_FALSE(usuario.autenticar("ABC"));
    CHECK_FALSE(usuario.autenticar(""));
}

TEST_CASE("Usuario - criar e buscar contas") {
    Usuario usuario("Carlos", 1);

    CHECK(usuario.criarConta("Corrente"));
    CHECK(usuario.criarConta("Poupanca"));
    CHECK(usuario.getContas().size() == 2);

    // nome repetido nao cria outra conta
    CHECK_FALSE(usuario.criarConta("Corrente"));
    CHECK(usuario.getContas().size() == 2);

    REQUIRE(usuario.buscarConta("Poupanca") != nullptr);
    CHECK(usuario.buscarConta("Poupanca")->getNome() == "Poupanca");
    CHECK(usuario.buscarConta("Inexistente") == nullptr);
}

TEST_CASE("Usuario - parametros invalidos lancam excecao") {
    CHECK_THROWS_AS(Usuario("", 1), std::invalid_argument);
    CHECK_THROWS_AS(Usuario("Ana", 0), std::invalid_argument);
    CHECK_THROWS_AS(Usuario("Ana", -5), std::invalid_argument);

    Usuario usuario("Ana", 1);
    CHECK_THROWS_AS(usuario.criarConta(""), std::invalid_argument);
}
