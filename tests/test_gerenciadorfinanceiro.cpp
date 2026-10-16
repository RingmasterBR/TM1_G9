#include "doctest.h"
#include "gerenciadorfinanceiro.hpp"
 
TEST_CASE("GerenciadorFinanceiro - Criacao e usuario logado") {
    Usuario usuario("Ana", 1);
    GerenciadorFinanceiro gerenciador(&usuario);
 
    CHECK(gerenciador.getUsuario() == &usuario);
}
TEST_CASE("GerenciadorFinanceiro - Orcamentos") {
    Usuario usuario("Ana", 1);
    GerenciadorFinanceiro gerenciador(&usuario);
 
    // sem nenhum orcamento cadastrado
    CHECK_NOTHROW(gerenciador.verificarOrcamentos());
 
    // com um orcamento cadastrado
    Categoria cat("Mercado", TipoGasto::Alimentacao, FormaPagamento::Debito);
    Orcamento orcamento(100.0, &cat, 10, 2026);
    gerenciador.adicionarOrcamento(&orcamento);
    CHECK_NOTHROW(gerenciador.verificarOrcamentos());
}
