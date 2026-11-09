#include <cstdio>
#include <sstream>
#include <string>

#include "doctest.h"
#include "interfaceterminal.hpp"

// Executa a interface com as linhas de entrada dadas e devolve tudo o que foi escrito.
static std::string executarComEntrada(const std::string& entrada) {
    std::istringstream in(entrada);
    std::ostringstream out;
    InterfaceTerminal interface(in, out);
    interface.executar();
    return out.str();
}

static bool contem(const std::string& texto, const std::string& trecho) {
    return texto.find(trecho) != std::string::npos;
}

// Cadastro + login do usuario "Ana" (senha 123) criando a conta "Corrente".
static const std::string CADASTRO_E_LOGIN =
    "1\nAna\n123\ns\n"      // cadastrar e logar agora
    "Ana\n123\n"            // login
    "s\nCorrente\n";        // criar a primeira conta

TEST_CASE("InterfaceTerminal - encerrar pelo menu") {
    std::string saida = executarComEntrada("0\n");
    CHECK(contem(saida, "Gerenciador Financeiro"));
    CHECK(contem(saida, "Ate logo!"));
}

TEST_CASE("InterfaceTerminal - fim da entrada encerra sem erro") {
    std::string saida = executarComEntrada("");
    CHECK(contem(saida, "Entrada encerrada"));
}

TEST_CASE("InterfaceTerminal - entradas invalidas sao pedidas de novo") {
    std::string saida = executarComEntrada("abc\n7\n0\n");
    CHECK(contem(saida, "Valor invalido"));
    CHECK(contem(saida, "Digite um valor entre 0 e 2"));
}

TEST_CASE("InterfaceTerminal - cadastro, login e erros de login") {
    std::string saida = executarComEntrada(
        "1\nAna\n123\nn\n"      // cadastra sem logar
        "1\n\nAna\nx\nn\n"      // nome vazio, depois nome repetido
        "2\nAna\nerrada\n"      // senha errada
        "2\nAna\n123\nn\n"      // login certo, mas nao cria conta
        "0\n");
    CHECK(contem(saida, "Usuario cadastrado com sucesso!"));
    CHECK(contem(saida, "Este campo nao pode ficar vazio"));
    CHECK(contem(saida, "Ja existe um usuario com esse nome"));
    CHECK(contem(saida, "Nome ou senha incorretos"));
    CHECK(contem(saida, "Sem conta nao e possivel continuar"));
}

TEST_CASE("InterfaceTerminal - transacoes, orcamento, extrato e relatorio") {
    std::string saida = executarComEntrada(
        CADASTRO_E_LOGIN +
        "2\n100\n1\n3\n10\n2026\n"           // orcamento: R$100, Alimentacao/Pix, 10/2026
        "2\n50\n1\n2\n10\n2026\n"            // orcamento repetido (mesmo tipo e periodo)
        "1\n2\n1000\n6\n3\ns\nn\n"           // receita de hoje, Outros/Pix
        "1\n1\n-5\n150,50\n1\n2\nn\n1\n10\n2026\nn\n"  // despesa em 01/10/2026 (valor invalido antes)
        "1\n1\n20\n1\n3\nn\n31\n2\n2026\n28\n2\n2026\ns\n"  // 31/02 invalida, depois 28/02/2026
        "4\n"                                 // extrato
        "3\n10\n2026\n"                       // relatorio de 10/2026
        "3\n0\n"                              // relatorio do mes atual
        "0\n0\n");
    CHECK(contem(saida, "Orcamento cadastrado."));
    CHECK(contem(saida, "Ja existe um orcamento de Alimentacao"));
    CHECK(contem(saida, "Receita registrada."));
    CHECK(contem(saida, "Despesa registrada."));
    CHECK(contem(saida, "Valor invalido. Digite um numero maior que zero."));
    CHECK(contem(saida, "ALERTA: orcamento de Alimentacao"));
    CHECK(contem(saida, "Data invalida"));
    CHECK(contem(saida, "Extrato da conta Corrente"));
    CHECK(contem(saida, "Relatorio de 10/2026"));
    CHECK(contem(saida, "Sessao encerrada."));
}

TEST_CASE("InterfaceTerminal - receita futura fica pendente") {
    std::string saida = executarComEntrada(
        CADASTRO_E_LOGIN +
        "1\n2\n300\n6\n3\nn\n10\n1\n2099\nn\n"   // receita em 10/01/2099
        "4\n0\n0\n");
    CHECK(contem(saida, "entrara no saldo quando a data chegar"));
    CHECK(contem(saida, "(pendente)"));
}

TEST_CASE("InterfaceTerminal - trocar e criar contas") {
    std::string saida = executarComEntrada(
        CADASTRO_E_LOGIN +
        "5\n0\nPoupanca\n"      // cria a conta Poupanca
        "5\n0\nCorrente\n"      // tenta criar conta repetida
        "5\n1\n"                // volta para a Corrente
        "0\n0\n");
    CHECK(contem(saida, "Conta \"Poupanca\" criada."));
    CHECK(contem(saida, "Ja existe uma conta com esse nome."));
    CHECK(contem(saida, "Conta: Poupanca"));
}

TEST_CASE("InterfaceTerminal - exportar dados") {
    std::string saida = executarComEntrada(
        CADASTRO_E_LOGIN +
        "6\nteste_interface.txt\n"
        "6\npasta_inexistente/dados.txt\n"
        "0\n0\n");
    CHECK(contem(saida, "Dados exportados para teste_interface.txt"));
    CHECK(contem(saida, "Erro: Nao foi possivel abrir o arquivo"));
    CHECK(std::remove("teste_interface.txt") == 0);
}
