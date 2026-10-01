#ifndef GERENCIADORFINANCEIRO_HPP
#define GERENCIADORFINANCEIRO_HPP

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

class Usuario;    
class Conta;      
class Transacao;  
class Orcamento;  
class Categoria;  
 
/**
 * @brief Classe coordenadora do sistema de gerenciamento de gastos pessoais.
 *
 * O GerenciadorFinanceiro orquestra as operações entre contas, transações
 * e orçamentos do usuário, além de ser responsável por solicitar a geração
 * de relatórios e a persistência dos dados em arquivo de texto.
 */
class GerenciadorFinanceiro {
public:
    /**
     * @brief Constrói o gerenciador financeiro para um usuário específico.
     * @param usuario Usuário logado no sistema.
     * @throws std::invalid_argument se o usuário for nulo.
     */
    explicit GerenciadorFinanceiro(const std::shared_ptr<Usuario>& usuario);
 
    ~GerenciadorFinanceiro() = default;
 
    // ---- Conhecimento (atributos) ----
 
    /**
     * @brief Retorna o usuário atualmente logado no sistema.
     * @return Ponteiro compartilhado para o usuário.
     */
    std::shared_ptr<Usuario> getUsuario() const;
 
    /**
     * @brief Retorna a lista de contas gerenciadas.
     * @return Vetor de ponteiros compartilhados para as contas.
     */
    const std::vector<std::shared_ptr<Conta>>& getContas() const;
 
    /**
     * @brief Retorna a lista de orçamentos gerenciados.
     * @return Vetor de ponteiros compartilhados para os orçamentos.
     */
    const std::vector<std::shared_ptr<Orcamento>>& getOrcamentos() const;
 
    // ---- Realização (métodos) ----
 
    /**
     * @brief Adiciona uma nova conta à gestão do usuário.
     * @param conta Conta a ser adicionada.
     * @throws std::invalid_argument se a conta for nula.
     */
    void adicionarConta(const std::shared_ptr<Conta>& conta);
 
    /**
     * @brief Remove uma conta previamente cadastrada, identificada pelo nome.
     * @param identificador Nome/identificador da conta.
     * @throws std::runtime_error se a conta não for encontrada.
     */
    void removerConta(const std::string& identificador);
 
    /**
     * @brief Busca uma conta pelo seu identificador.
     * @param identificador Nome/identificador da conta.
     * @return Ponteiro compartilhado para a conta encontrada.
     * @throws std::runtime_error se a conta não for encontrada.
     */
    std::shared_ptr<Conta> buscarConta(const std::string& identificador) const;
 
    /**
     * @brief Registra uma transação em uma conta específica, atualizando
     *        seu saldo e verificando os orçamentos relacionados.
     * @param identificadorConta Identificador da conta de destino.
     * @param transacao Transação a ser registrada (Receita ou Despesa).
     * @throws std::runtime_error se a conta não for encontrada.
     * @throws std::invalid_argument se a transação for nula ou inválida.
     */
    void registrarTransacao(const std::string& identificadorConta,
                             const std::shared_ptr<Transacao>& transacao);
 
    /**
     * @brief Adiciona um novo orçamento à gestão do usuário.
     * @param orcamento Orçamento a ser adicionado.
     * @throws std::invalid_argument se o orçamento for nulo.
     */
    void adicionarOrcamento(const std::shared_ptr<Orcamento>& orcamento);
 
    /**
     * @brief Verifica todos os orçamentos cadastrados, emitindo alertas
     *        para aqueles que ultrapassaram o limite definido.
     */
    void verificarOrcamentos() const;
 
    /**
     * @brief Gera um relatório resumido de receitas e despesas do período.
     * @param mes Mês de referência (1-12).
     * @param ano Ano de referência.
     * @return Texto formatado com o resumo financeiro do período.
     * @throws std::invalid_argument se o mês for inválido (fora de 1-12).
     */
    std::string gerarRelatorioMensal(int mes, int ano) const;
 
    /**
     * @brief Gera um relatório agregando as transações de uma categoria.
     * @param categoria Categoria a ser detalhada no relatório.
     * @return Texto formatado com o resumo da categoria.
     * @throws std::invalid_argument se a categoria for nula.
     */
    std::string gerarRelatorioPorCategoria(const std::shared_ptr<Categoria>& categoria) const;
 
    /**
     * @brief Persiste todos os dados (usuário, contas e transações) em
     *        um arquivo de texto.
     * @param caminhoArquivo Caminho do arquivo de destino.
     * @throws std::runtime_error se o arquivo não puder ser aberto/gravado.
     */
    void salvarDados(const std::string& caminhoArquivo) const;
 
    /**
     * @brief Carrega dados previamente salvos a partir de um arquivo de texto.
     * @param caminhoArquivo Caminho do arquivo de origem.
     * @throws std::runtime_error se o arquivo não puder ser aberto/lido.
     */
    void carregarDados(const std::string& caminhoArquivo);
 
private:
    std::shared_ptr<Usuario> usuario_;
    std::vector<std::shared_ptr<Conta>> contas_;
    std::vector<std::shared_ptr<Orcamento>> orcamentos_;
};
 
#endif
