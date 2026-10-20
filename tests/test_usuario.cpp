#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Usuario.hpp"
#include "Conta.hpp"

TEST_CASE("Testando a classe Usuario e suas operações") {
    // Cenário inicial: Criando um usuário de teste
    Usuario usuario("Carlos Silva", 101, "senhaSegura123");

    SUBCASE("Verificando dados iniciais do usuário (Getters)") {
        CHECK(usuario.getUserId() == 101);
        CHECK(usuario.getName() == "Carlos Silva");
        // Uma nova conta recém-criada deve iniciar com a lista de contas vazia
        CHECK(usuario.getContas().empty() == true);
    }

    SUBCASE("Criando contas com sucesso") {
        // Criando a primeira conta
        bool primeiraCriacao = usuario.criarConta("Conta Corrente");
        CHECK(primeiraCriacao == true);

        // Criando uma segunda conta com nome diferente
        bool segundaCriacao = usuario.criarConta("Conta Poupança");
        CHECK(segundaCriacao == true);

        // Verificando se a quantidade de contas na lista é 2
        CHECK(usuario.getContas().size() == 2);
    }

    SUBCASE("Tentando criar contas duplicadas (deve falhar)") {
        // Criando a conta inicial
        CHECK(usuario.criarConta("Conta Principal") == true);

        // Tentando criar outra conta com o mesmo nome exato
        bool tentativaDuplicada = usuario.criarConta("Conta Principal");
        
        // A função deve retornar false impedindo a duplicidade
        CHECK(tentativaDuplicada == false);

        // O tamanho da lista de contas deve continuar sendo 1
        CHECK(usuario.getContas().size() == 1);
    }
}