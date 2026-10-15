#include "doctest.h"
#include "gerenciadorfinanceiro.hpp"
 
TEST_CASE("GerenciadorFinanceiro - Criacao e usuario logado") {
    Usuario usuario("Ana", 1);
    GerenciadorFinanceiro gerenciador(&usuario);
 
    CHECK(gerenciador.getUsuario() == &usuario);
}
