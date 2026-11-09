#include <chrono>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "doctest.h"
#include "usuario.hpp"
#include "conta.hpp"
#include "categoria.hpp"
#include "despesa.hpp"
#include "receita.hpp"
#include "orcamento.hpp"
#include "gerenciadorfinanceiro.hpp"
#include "interfaceterminal.hpp"

using namespace std::chrono;

TEST_CASE("GerenciadorFinanceiro - criacao") {
    Usuario usuario("Ana", 1);
    GerenciadorFinanceiro gerenciador(&usuario);

    CHECK(gerenciador.getUsuario() == &usuario);
    CHECK(gerenciador.getOrcamentos().empty());
    CHECK_THROWS_AS(GerenciadorFinanceiro(nullptr), std::invalid_argument);
}

TEST_CASE("GerenciadorFinanceiro - registrar lancamentos atualiza conta e orcamentos") {
    Usuario usuario("Ana", 1);
    usuario.criarConta("Corrente");
    Conta* conta = usuario.buscarConta("Corrente");
    GerenciadorFinanceiro* gerenciador = usuario.getGerenciadorFinanceiro();
    Categoria mercado("Mercado", Alimentacao, Debito);

    year_month_day hoje = InterfaceTerminal::hoje();
    year_month_day futuro = sys_days(hoje) + days(40);
    int mes = static_cast<int>(static_cast<unsigned>(hoje.month()));
    int ano = static_cast<int>(hoje.year());

    Orcamento orcamento(100.0, &mercado, mes, ano);
    gerenciador->adicionarOrcamento(&orcamento);
    std::ostringstream saida;

    Receita salario(1000.0, &mercado, hoje, conta, false);
    gerenciador->registrarLancamento(&salario, saida);
    CHECK(conta->getSaldo() == 1000.0);
    CHECK(saida.str().empty()); // nenhum orcamento estourado ainda

    Despesa compra(150.0, &mercado, hoje, conta, false);
    gerenciador->registrarLancamento(&compra, saida);
    CHECK(conta->getSaldo() == 850.0);
    CHECK(orcamento.estourouLimite());
    CHECK(saida.str().find("ALERTA") != std::string::npos);
    CHECK(gerenciador->verificarOrcamentos(saida) == 1);

    Despesa parcela(200.0, &mercado, futuro, conta, false);
    gerenciador->registrarLancamento(&parcela, saida);
    CHECK(conta->getSaldo() == 850.0);
    CHECK(conta->getDivida() == 200.0);
    CHECK(conta->getTransacoes().size() == 3);
    CHECK(conta->getLancamentos().size() == 3);
}

TEST_CASE("GerenciadorFinanceiro - parametros invalidos lancam excecao") {
    Usuario usuario("Ana", 1);
    Usuario outro("Bia", 2);
    outro.criarConta("Corrente");
    Categoria categoria(Lazer, Pix);
    Despesa deOutroUsuario(10.0, &categoria, year(2026) / 10 / 1,
                           outro.buscarConta("Corrente"), false);
    GerenciadorFinanceiro* gerenciador = usuario.getGerenciadorFinanceiro();

    CHECK_THROWS_AS(gerenciador->registrarLancamento(nullptr), std::invalid_argument);
    CHECK_THROWS_AS(gerenciador->registrarLancamento(&deOutroUsuario), std::invalid_argument);
    CHECK_THROWS_AS(gerenciador->adicionarOrcamento(nullptr), std::invalid_argument);
    CHECK_THROWS_AS(gerenciador->gerarRelatorioMensal(13, 2026), std::invalid_argument);
}

TEST_CASE("GerenciadorFinanceiro - relatorio mensal") {
    Usuario usuario("Ana", 1);
    usuario.criarConta("Corrente");
    Conta* conta = usuario.buscarConta("Corrente");
    GerenciadorFinanceiro* gerenciador = usuario.getGerenciadorFinanceiro();
    Categoria lazer(Lazer, Pix);
    Categoria salarioCategoria(Outros, Pix);
    Orcamento orcamento(100.0, &lazer, 10, 2026);
    gerenciador->adicionarOrcamento(&orcamento);

    std::ostringstream ignorar;
    Receita salario(1000.0, &salarioCategoria, year(2026) / 10 / 5, conta, false);
    Despesa cinema(120.0, &lazer, year(2026) / 10 / 8, conta, false);
    gerenciador->registrarLancamento(&salario, ignorar);
    gerenciador->registrarLancamento(&cinema, ignorar);

    std::ostringstream relatorio;
    gerenciador->gerarRelatorioMensal(10, 2026, relatorio);
    std::string texto = relatorio.str();
    CHECK(texto.find("Total de receitas: R$ 1000.00") != std::string::npos);
    CHECK(texto.find("Total de despesas: R$ 120.00") != std::string::npos);
    CHECK(texto.find("Lazer: R$ 120.00") != std::string::npos);
    CHECK(texto.find("ESTOUROU") != std::string::npos);

    std::ostringstream vazio;
    gerenciador->gerarRelatorioMensal(3, 2026, vazio);
    CHECK(vazio.str().find("Nenhum lancamento neste mes") != std::string::npos);
    CHECK(vazio.str().find("Nenhum orcamento cadastrado") != std::string::npos);
}

TEST_CASE("GerenciadorFinanceiro - salvar e carregar dados") {
    Usuario usuario("Ana", 1);
    usuario.criarConta("Corrente");
    Conta* conta = usuario.buscarConta("Corrente");
    GerenciadorFinanceiro* gerenciador = usuario.getGerenciadorFinanceiro();
    Categoria lazer(Lazer, Pix);
    Orcamento orcamento(100.0, &lazer, 10, 2026);
    gerenciador->adicionarOrcamento(&orcamento);
    std::ostringstream ignorar;
    Despesa cinema(50.0, &lazer, year(2026) / 10 / 8, conta, true);
    gerenciador->registrarLancamento(&cinema, ignorar);

    gerenciador->salvarDados("teste_dados.txt");
    // USUARIO + CONTA + LANCAMENTO + ORCAMENTO
    CHECK(gerenciador->carregarDados("teste_dados.txt") == 4);
    CHECK(std::remove("teste_dados.txt") == 0);
}

TEST_CASE("GerenciadorFinanceiro - erros de arquivo lancam excecao") {
    Usuario usuario("Ana", 1);
    GerenciadorFinanceiro* gerenciador = usuario.getGerenciadorFinanceiro();

    CHECK_THROWS_AS(gerenciador->carregarDados("arquivo_que_nao_existe.txt"), std::runtime_error);
    CHECK_THROWS_AS(gerenciador->salvarDados("pasta_inexistente/dados.txt"), std::runtime_error);

    {
        std::ofstream arquivo("teste_invalido.txt");
        arquivo << "USUARIO;Ana;1\nLINHA QUALQUER\n";
    }
    CHECK_THROWS_AS(gerenciador->carregarDados("teste_invalido.txt"), std::runtime_error);
    CHECK(std::remove("teste_invalido.txt") == 0);
}
