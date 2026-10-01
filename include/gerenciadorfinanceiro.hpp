#ifndef GERENCIADORFINANCEIRO_HPP
#define GERENCIADORFINANCEIRO_HPP

#include <string>
#include <vector>

class Usuario;
class Conta;
class Transacao;
class Orcamento;

/**
 * @brief Classe responsável por coordenar contas, transações e orçamentos do usuário.
 */
class GerenciadorFinanceiro {
private:
    Usuario* usuario;
    std::vector<Conta*> contas;
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
     * @brief Retorna as contas gerenciadas.
     * @return Vetor de ponteiros para as contas.
     */
    std::vector<Conta*> getContas();

    /**
     * @brief Adiciona uma nova conta à gestão do usuário.
     * @param conta Ponteiro para a conta a ser adicionada.
     */
    void adicionarConta(Conta* conta);

    /**
     * @brief Busca uma conta pelo nome.
     * @param nome Nome da conta buscada.
     * @return Ponteiro para a conta encontrada, ou nullptr se não existir.
     */
    Conta* buscarConta(std::string nome);

    /**
     * @brief Registra uma transação em uma conta específica.
     * @param nomeConta Nome da conta de destino.
     * @param transacao Ponteiro para a transação a ser registrada.
     */
    void registrarTransacao(std::string nomeConta, Transacao* transacao);

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
