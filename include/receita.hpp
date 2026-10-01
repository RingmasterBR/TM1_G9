#ifndef RECEITA_HPP
#define RECEITA_HPP

#include <string>
#include "transacao.hpp"
#include "categoria.hpp"

/**
* @brief Classe que representa uma receita do usuário, herda de Transacao
*
* Especializa transacao para tratar especificamente de saídas da conta e que
* permite indicar se o gasto é recorrente ou não.
*/

class Receita : public Transacao {
private:
    int diaRecebimento_;
    bool ehFixa_;
    
public:
    /**
    * @brief Construtor de receita.
    * @param valor Valor da receita.
    * @param descricao Descricao do recebimento.
    * @param categoria Ponteiro para a categoria do recebimento.
    * @param data Data do recebimento.
    * @param ehFixa Indica se e uma receita mensal.
    * @param diaRecebimento Dia do mês da do recebimento (1 a 31, padrão: 0 para não fixas).
    */
    Receita(double valor, std::string descricao, Categoria* categoria, std::string data, bool ehFixa = false, int diaRecebimento = 0);

    /**
    * @brief Destrutor da classe.
    */
    ~Receita() = default;

    /**
    * @brief Função para verificar se a receita é fixa.
    * @return Retorna true se for, false senão.
    */
    bool isFixa() const;

    /**
    * @brief Define se a receita é mensal ou não.
    * @param ehFixa Seta o estado da despesa.
    */
    void setFixa(bool ehFixa);

    /**
    * @brief Retorna o dia dos mês que a receita é adicionada.
    * @return Número do dia do mês (1 a 31).
    */
    int getDiaRecebimento() const;

    /**
    * @brief Atualiza o dia do mês para o recebimento de despesa fixa.
    * @param diaCobranca Novo dia do mês (1 a 31).
    */
    void setDiaRecebimento(int diaCobranca);

    /**
    * @brief Realiza a transacao referente a receita. Implementacao deve instanciar objeto transacao.
    * @param diaCobranca Novo dia do mês (1 a 31).
    */
    void realizarTransacaoReceita();


};

#endif