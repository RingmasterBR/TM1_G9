#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Usuario.hpp"
#include "Conta.hpp"
#include "Lancamentos.hpp"

TEST_CASE("Testando a classe Conta e as suas operações") {
    // Instanciação prévia de um utilizador válido para associar à conta
    Usuario usuario("Maria Souza", 202, "senhaSegura456");

    SUBCASE("Verificação do construtor e valores iniciais") {
        Conta conta(&usuario, "Conta Poupança");

        CHECK(conta.NomeDaConta == "Conta Poupança");
        CHECK(conta.getSaldo() == 0.0);
        CHECK(conta.getDivida() == 0.0);
    }

    SUBCASE("Adicionando lançamentos futuros à conta") {
        Conta conta(&usuario, "Conta Corrente");

        // Adicionando um lançamento (pode ser nullptr para testar o método se a classe permitir, 
        // ou um objeto válido do tipo Lancamentos)
        Lancamentos* lancamentoExemplo = nullptr; 
        conta.addLancamento(lancamentoExemplo);

        // Garantimos que a operação ocorre sem falhas e mantém o estado consistente
        CHECK(conta.getSaldo() == 0.0);
        CHECK(conta.getDivida() == 0.0);
        CHECK(conta.NomeDaConta == "Conta Corrente");
    }
}