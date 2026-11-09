/**
 * @file gerenciadorfinanceiro.hpp
 * @brief Declaracao da classe GerenciadorFinanceiro.
 */
#ifndef GERENCIADORFINANCEIRO_HPP
#define GERENCIADORFINANCEIRO_HPP

#include <iostream>
#include <string>
#include <vector>

class Usuario;
class Lancamentos;
class Orcamento;

/**
 * @brief Coordena as operacoes entre conta, lancamentos e orcamentos de um usuario.
 *
 * Registra lancamentos (atualizando a conta e os orcamentos), emite alertas de
 * orcamentos estourados, gera relatorios e exporta os dados para arquivo.
 * O gerenciador guarda ponteiros para os orcamentos, mas nao e dono deles.
 */
class GerenciadorFinanceiro {
private:
    Usuario* usuario_;                   /**< Usuario dono do gerenciador. */
    std::vector<Orcamento*> orcamentos_; /**< Orcamentos cadastrados. */

public:
    /**
     * @brief Cria o gerenciador de um usuario.
     * @param usuario Usuario dono (nao pode ser nulo).
     * @throws std::invalid_argument se o usuario for nulo.
     */
    explicit GerenciadorFinanceiro(Usuario* usuario);

    /** @brief Retorna o usuario. @return Ponteiro para o usuario. */
    Usuario* getUsuario() const;

    /** @brief Retorna os orcamentos. @return Referencia constante para os orcamentos. */
    const std::vector<Orcamento*>& getOrcamentos() const;

    /**
     * @brief Registra um lancamento na conta dele e nos orcamentos.
     *
     * Adiciona o lancamento a conta, cria a transacao que atualiza saldo e
     * divida, repassa o lancamento aos orcamentos e emite os alertas.
     * @param lancamento Lancamento (Receita ou Despesa) a registrar.
     * @param out Onde os alertas sao escritos.
     * @throws std::invalid_argument se o lancamento for nulo ou de uma conta de outro usuario.
     */
    void registrarLancamento(Lancamentos* lancamento, std::ostream& out = std::cout);

    /**
     * @brief Adiciona um orcamento.
     * @param orcamento Orcamento a adicionar.
     * @throws std::invalid_argument se o orcamento for nulo.
     */
    void adicionarOrcamento(Orcamento* orcamento);

    /**
     * @brief Escreve um alerta para cada orcamento que estourou o limite.
     * @param out Onde os alertas sao escritos.
     * @return Quantidade de orcamentos estourados.
     */
    int verificarOrcamentos(std::ostream& out = std::cout) const;

    /**
     * @brief Escreve o relatorio de um mes: receitas, despesas, gastos por tipo e orcamentos.
     * @param mes Mes de referencia (1 a 12).
     * @param ano Ano de referencia.
     * @param out Onde o relatorio e escrito.
     * @throws std::invalid_argument se o mes for invalido.
     */
    void gerarRelatorioMensal(int mes, int ano, std::ostream& out = std::cout) const;

    /**
     * @brief Exporta usuario, contas, lancamentos e orcamentos para um arquivo de texto.
     *
     * Formato: uma linha por registro, campos separados por ';'.
     * @param arquivo Caminho do arquivo de destino.
     * @throws std::runtime_error se o arquivo nao puder ser aberto.
     */
    void salvarDados(const std::string& arquivo) const;

    /**
     * @brief Le um arquivo gerado por salvarDados e conta os registros validos.
     * @param arquivo Caminho do arquivo de origem.
     * @return Quantidade de registros reconhecidos.
     * @throws std::runtime_error se o arquivo nao puder ser aberto ou tiver linha invalida.
     */
    int carregarDados(const std::string& arquivo) const;
};

#endif
