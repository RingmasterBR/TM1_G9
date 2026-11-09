/**
 * @file interfaceterminal.hpp
 * @brief Declaracao da classe InterfaceTerminal.
 */
#ifndef INTERFACETERMINAL_HPP
#define INTERFACETERMINAL_HPP

#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

class Usuario;
class Conta;
class Categoria;
class Lancamentos;
class Orcamento;

/**
 * @brief Interface textual (menus no terminal) do sistema.
 *
 * Le e valida as entradas do usuario, cria os objetos do sistema e chama as
 * classes de dominio. E dona de todos os usuarios, categorias, lancamentos e
 * orcamentos que cria, e os desaloca no destrutor.
 *
 * A entrada e a saida sao recebidas no construtor (normalmente std::cin e
 * std::cout), o que permite testar a interface com std::stringstream.
 */
class InterfaceTerminal {
private:
    std::istream& in_;                                      /**< Entrada de dados. */
    std::ostream& out_;                                     /**< Saida de dados. */
    std::vector<Usuario*> usuarios_;                        /**< Usuarios cadastrados. */
    std::map<std::pair<int, int>, Categoria*> categorias_;  /**< Categorias por (tipo, forma). */
    std::vector<Lancamentos*> lancamentos_;                 /**< Lancamentos criados. */
    std::vector<Orcamento*> orcamentos_;                    /**< Orcamentos criados. */
    int proximoIdUsuario_;                                  /**< Id do proximo usuario cadastrado. */

    /** @brief Le um inteiro, repetindo ate o texto digitado ser um numero valido. */
    int lerInt(const std::string& mensagem);
    /** @brief Le um inteiro no intervalo [minimo, maximo], repetindo se estiver fora. */
    int lerIntEntre(const std::string& mensagem, int minimo, int maximo);
    /** @brief Le um numero real maior que zero (aceita virgula como decimal). */
    double lerDoublePositivo(const std::string& mensagem);
    /**
     * @brief Le uma linha de texto.
     * @throws std::runtime_error se a entrada acabar.
     */
    std::string lerTexto(const std::string& mensagem);
    /** @brief Le uma linha de texto, repetindo enquanto estiver vazia. */
    std::string lerTextoNaoVazio(const std::string& mensagem);
    /** @brief Faz uma pergunta de sim/nao. @return true para "s". */
    bool perguntarSimNao(const std::string& mensagem);
    /** @brief Le uma data valida (ou usa a data de hoje). */
    std::chrono::year_month_day lerData();
    /** @brief Mostra opcoes numeradas e retorna o indice escolhido (a partir de 0). */
    int escolherOpcao(const std::string& titulo, const std::vector<std::string>& rotulos);
    /** @brief Pergunta tipo de gasto e forma de pagamento e retorna a categoria correspondente. */
    Categoria* escolherCategoria();

    /** @brief Procura um usuario cadastrado pelo nome. @return Usuario ou nullptr. */
    Usuario* buscarUsuario(const std::string& nome) const;
    /** @brief Fluxo de cadastro de um novo usuario. */
    void cadastrar();
    /** @brief Fluxo de login. @return Usuario autenticado ou nullptr. */
    Usuario* login();
    /** @brief Pede o nome e cria uma conta para o usuario. @return Conta criada ou nullptr. */
    Conta* criarConta(Usuario* usuario);
    /** @brief Deixa o usuario escolher uma conta ou criar uma nova. @return Conta escolhida ou nullptr. */
    Conta* escolherConta(Usuario* usuario);
    /** @brief Fluxo de criacao de um orcamento. */
    void criarOrcamento(Usuario* usuario);
    /** @brief Fluxo de registro de uma receita ou despesa na conta. */
    void registrarTransacao(Usuario* usuario, Conta* conta);
    /** @brief Pede mes/ano e mostra o relatorio mensal. */
    void gerarRelatorio(Usuario* usuario);
    /** @brief Mostra todos os lancamentos, o saldo e a divida da conta. */
    void mostrarExtrato(Conta* conta);
    /** @brief Pede o nome do arquivo e exporta os dados do usuario. */
    void exportarDados(Usuario* usuario);
    /** @brief Menu da conta, repetido ate o usuario escolher sair. */
    void sessao(Usuario* usuario);

public:
    /**
     * @brief Cria a interface.
     * @param in Fluxo de entrada (ex: std::cin).
     * @param out Fluxo de saida (ex: std::cout).
     */
    InterfaceTerminal(std::istream& in, std::ostream& out);

    /**
     * @brief Desaloca todos os objetos criados pela interface.
     */
    ~InterfaceTerminal();

    InterfaceTerminal(const InterfaceTerminal&) = delete;
    InterfaceTerminal& operator=(const InterfaceTerminal&) = delete;

    /**
     * @brief Executa o menu principal ate o usuario escolher sair ou a entrada acabar.
     */
    void executar();

    /**
     * @brief Retorna a data de hoje.
     * @return Data atual do sistema.
     */
    static std::chrono::year_month_day hoje();
};

#endif
