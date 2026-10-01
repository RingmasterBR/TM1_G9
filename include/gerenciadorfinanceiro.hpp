#ifndef GERENCIADORFINANCEIRO_HPP
#define GERENCIADORFINANCEIRO_HPP
 
#include <string>
#include <vector>
#include "usuario.hpp"
#include "conta.hpp"
#include "transacao.hpp"
#include "orcamento.hpp"
 
/**
 * @brief Classe responsável por coordenar as operações entre o usuário,
 *        suas contas, transações e orçamentos.
 *
 * As contas pertencem ao Usuario (que já mantém sua própria lista).
 * A conta a ser usada em cada operação já é escolhida previamente
 * pelo usuário (via interface) e passada diretamente para os métodos.
 */
class GerenciadorFinanceiro {
private:
    Usuario* usuario;
    std::vector<Orcamento*> orcamentos;
 
public:
    /**
     * @brief Construtor da classe GerenciadorFinanceiro.
     * @param usuario Usuário logado no sistema.
     */
    GerenciadorFinanceiro(Usuario* usuario);
 
    /**
     * @brief Retorna o usuário logado.
     * @return Ponteiro para o usuário.
     */
    Usuario* getUsuario();
 
    /**
     * @brief Registra uma transação em uma conta já escolhida pelo usuário.
     * @param conta Conta de destino da transação.
     * @param transacao Ponteiro para a transação a ser registrada.
     */
    void registrarTransacao(Conta* conta, Transacao* transacao);
 
    /**
     * @brief Adiciona um novo orçamento à gestão do usuário.
     * @param orcamento Ponteiro para o orçamento a ser adicionado.
     */
    void adicionarOrcamento(Orcamento* orcamento);
 
    /**
     * @brief Verifica todos os orçamentos e alerta sobre os que ultrapassaram o limite.
     */
    void verificarOrcamentos();
 
    /**
     * @brief Gera um relatório com o resumo financeiro do mês informado.
     * @param mes Mês de referência (1 a 12).
     * @param ano Ano de referência.
     */
    void gerarRelatorioMensal(int mes, int ano);
 
    /**
     * @brief Salva os dados do sistema em um arquivo de texto.
     * @param arquivo Caminho do arquivo de destino.
     */
    void salvarDados(std::string arquivo);
 
    /**
     * @brief Carrega os dados do sistema a partir de um arquivo de texto.
     * @param arquivo Caminho do arquivo de origem.
     */
    void carregarDados(std::string arquivo);
};
 
#endif

   
