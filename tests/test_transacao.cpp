#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Transacao.hpp"
#include "Conta.hpp"
#include "Usuario.hpp"

TEST_CASE("Testando a classe Transacao e os seus métodos principais") {
    // Cenário inicial para associar à transação
    Usuario usuario("Carlos Transacao", 505, "senhaTransacao123");
    Conta conta(&usuario, "Conta Transações");

    SUBCASE("Construção e verificação de getters básicos da Transação") {
        // Criando uma transação com valor inicial
        Transacao transacao(&conta, 100.0);

        // Verificando se a conta associada está correta
        CHECK(transacao.getConta() == &conta);
        
        // Como o saldo e dívida iniciais da conta são 0.0, os valores esperados são 0.0
        CHECK(transacao.getSaldoAnterior() == 0.0);
        CHECK(transacao.getDividaAnterior() == 0.0);
        CHECK(transacao.getSaldoFinal() == 0.0);
        CHECK(transacao.getDividaFinal() == 0.0);
    }
}