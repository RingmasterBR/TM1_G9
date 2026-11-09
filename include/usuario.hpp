/**
 * @file usuario.hpp
 * @brief Declaracao da classe Usuario.
 */
#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <list>
#include <string>

class Conta;
class GerenciadorFinanceiro;

/**
 * @brief Usuario do sistema, dono de contas e de um gerenciador financeiro.
 *
 * O Usuario cria e desaloca as proprias contas e o seu GerenciadorFinanceiro,
 * por isso nao pode ser copiado.
 */
class Usuario {
private:
    std::string nome_;                      /**< Nome de login do usuario. */
    int id_;                                /**< Identificador numerico. */
    std::string senha_;                     /**< Senha de acesso. */
    std::list<Conta*> contas_;              /**< Contas do usuario (o usuario e dono delas). */
    GerenciadorFinanceiro* gerenciador_;    /**< Gerenciador dos orcamentos e relatorios. */

public:
    /**
     * @brief Cria um usuario.
     * @param nome Nome do usuario (nao pode ser vazio).
     * @param id Identificador (deve ser positivo).
     * @param senha Senha de acesso (pode ser vazia).
     * @throws std::invalid_argument se o nome for vazio ou o id nao for positivo.
     */
    Usuario(const std::string& nome, int id, const std::string& senha = "");

    /**
     * @brief Desaloca as contas e o gerenciador do usuario.
     */
    ~Usuario();

    Usuario(const Usuario&) = delete;
    Usuario& operator=(const Usuario&) = delete;

    /**
     * @brief Retorna o identificador do usuario.
     * @return Id do usuario.
     */
    int getId() const;

    /**
     * @brief Retorna o nome do usuario.
     * @return Nome do usuario.
     */
    std::string getNome() const;

    /**
     * @brief Retorna as contas do usuario.
     * @return Lista (copia) de ponteiros para as contas.
     */
    std::list<Conta*> getContas() const;

    /**
     * @brief Procura uma conta pelo nome.
     * @param nomeConta Nome da conta.
     * @return Ponteiro para a conta ou nullptr se nao existir.
     */
    Conta* buscarConta(const std::string& nomeConta) const;

    /**
     * @brief Retorna o gerenciador financeiro do usuario.
     * @return Ponteiro para o gerenciador.
     */
    GerenciadorFinanceiro* getGerenciadorFinanceiro() const;

    /**
     * @brief Verifica se a senha informada e a senha do usuario.
     * @param senhaDigitada Senha a conferir.
     * @return true se a senha estiver correta.
     */
    bool autenticar(const std::string& senhaDigitada) const;

    /**
     * @brief Cria uma nova conta para o usuario.
     * @param nomeConta Nome da conta (nao pode ser vazio).
     * @return true se a conta foi criada; false se ja existe conta com esse nome.
     * @throws std::invalid_argument se o nome for vazio.
     */
    bool criarConta(const std::string& nomeConta);
};

#endif
