/**
 * @file conta.hpp
 * @brief Declaracao da classe Conta.
 */
#ifndef CONTA_HPP
#define CONTA_HPP

#include <list>
#include <string>

class Usuario;
class Lancamentos;
class Transacao;

/**
 * @brief Conta financeira de um usuario (ex: "Corrente", "Poupanca").
 *
 * Guarda o saldo, a divida (despesas com data futura), o historico de
 * lancamentos e as transacoes que alteraram o saldo. A Conta e dona das
 * transacoes (desaloca no destrutor), mas nao dos lancamentos.
 */
class Conta {
private:
    Usuario* usuario_;                      /**< Dono da conta. */
    std::string nome_;                      /**< Nome da conta. */
    double saldo_;                          /**< Saldo atual. */
    double divida_;                         /**< Total de despesas futuras ja registradas. */
    std::list<Lancamentos*> lancamentos_;   /**< Todos os lancamentos registrados (historico). */
    std::list<Transacao*> transacoes_;      /**< Transacoes que alteraram saldo ou divida. */

public:
    /**
     * @brief Cria uma conta com saldo e divida zerados.
     * @param usuario Dono da conta.
     * @param nome Nome da conta (nao pode ser vazio).
     * @throws std::invalid_argument se o nome for vazio.
     */
    Conta(Usuario* usuario, const std::string& nome);

    /**
     * @brief Desaloca as transacoes da conta.
     */
    ~Conta();

    Conta(const Conta&) = delete;
    Conta& operator=(const Conta&) = delete;

    /**
     * @brief Retorna o nome da conta.
     * @return Nome da conta.
     */
    std::string getNome() const;

    /**
     * @brief Retorna o dono da conta.
     * @return Ponteiro para o usuario.
     */
    Usuario* getUsuario() const;

    /**
     * @brief Retorna o saldo atual.
     * @return Saldo em reais.
     */
    double getSaldo() const;

    /**
     * @brief Retorna a divida atual (despesas futuras).
     * @return Divida em reais.
     */
    double getDivida() const;

    /**
     * @brief Retorna o historico de lancamentos da conta.
     * @return Referencia constante para a lista de lancamentos.
     */
    const std::list<Lancamentos*>& getLancamentos() const;

    /**
     * @brief Retorna as transacoes registradas na conta.
     * @return Referencia constante para a lista de transacoes.
     */
    const std::list<Transacao*>& getTransacoes() const;

    /**
     * @brief Adiciona um lancamento ao historico da conta.
     *
     * O lancamento so afeta o saldo quando uma Transacao e criada.
     * @param lancamento Lancamento a adicionar.
     * @throws std::invalid_argument se o lancamento for nulo ou de outra conta.
     */
    void addLancamento(Lancamentos* lancamento);

    /**
     * @brief Registra uma transacao e atualiza saldo e divida com os valores dela.
     * @param transacao Transacao a registrar (a conta passa a ser dona dela).
     * @throws std::invalid_argument se a transacao for nula.
     */
    void addTransacao(Transacao* transacao);
};

#endif
