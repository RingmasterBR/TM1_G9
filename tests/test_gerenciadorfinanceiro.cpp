#include <cstudio>
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
TEST_CASE("GerenciadorFinanceiro - Relatorio mensal") {
    Usuario usuario("Ana", 1);
    GerenciadorFinanceiro gerenciador(&usuario);
 
    CHECK_NOTHROW(gerenciador.gerarRelatorioMensal(10, 2026));
}
 
TEST_CASE("GerenciadorFinanceiro - Salvar e carregar dados") {
    Usuario usuario("Ana", 1);
    GerenciadorFinanceiro gerenciador(&usuario);
 
    gerenciador.salvarDados("teste_dados.txt");
    CHECK_NOTHROW(gerenciador.carregarDados("teste_dados.txt"));
    CHECK(std::remove("teste_dados.txt") == 0); // arquivo foi criado (e ja apagado)
}
