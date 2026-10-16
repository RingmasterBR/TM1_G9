#include "doctest.h"
#include "conta.hpp"
 
TEST_CASE("Conta - Criacao e getters basicos") {
    Conta conta("Ana", 1);
 
    CHECK(conta.getSaldo() == 0.0);
    CHECK(conta.getDivida() == 0.0);
}
 
TEST_CASE("Conta - Atualizar saldo e divida sem transacoes") {
    Conta conta("Ana", 1);
    Conta outra("Bruno", 2);
 
    conta.UpdateDividaESaldo();
 
    CHECK(conta.getSaldo() == 0.0);
    CHECK(conta.getDivida() == 0.0);
    CHECK(outra.getSaldo() == 0.0);
}
