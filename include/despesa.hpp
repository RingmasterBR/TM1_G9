#ifndef DESPESA_HPP
#define DESPESA_HPP

#include <string>
#include "transacao.hpp"
#include "categoria.hpp"

/**
* @brief Classe que representa uma despesa do usuário, herda de Transacao
*
* Especializa transacao para tratar especificamente de saídas da conta e que
* permite indicar se o gasto é recorrente ou não.
*/

class Despesa : public Transacao {
private:
    int diaCobranca_;
    bool ehFixa_;
    
public:
    /**
    * @brief Construtor de despesa.
    * @param valor Valor da despesa.
    * @param descricao Descrição do gasto.
    * @param categoria Ponteiro para a categoria do gasto.
    * @param data Data da despesa.
    * @param ehFixa Indica se é uma despesa mensal.
    * @param diaCobranca Dia do mês da cobrança (1 a 31, padrão: 0 para não fixas).
    */
    Despesa(double valor, std::string descricao, Categoria* categoria, std::string data, bool ehFixa = false, int diaCobranca = 0);

    /**
    * @brief Destrutor da classe.
    */
    ~Despesa() = default;

    /**
    * @brief Função para verificar se a despesa é fixa ou mensal.
    * @return Retorna true se for, false senão.
    */
    bool isFixa() const;

    /**
    * @brief Define se a despesa é mensal ou não.
    * @param ehFixa Seta o estado da despesa.
    */
    void setFixa(bool ehFixa);

    /**
    * @brief Retorna o dia dos mês que a despesa é cobrada.
    * @return Número do dia do mês (1 a 31).
    */
    int getDiaCobranca() const;

    /**
    * @brief Atualiza o dia do mês para a cobrança de despesa fixa.
    * @param diaCobranca Novo dia do mês (1 a 31).
    */
    void setDiaCobranca(int diaCobranca);

    /**
    * @brief Realiza a transacao referente a despesa. Implementacao deve instanciar objeto transacao.
    * @param diaCobranca Novo dia do mês (1 a 31).
    */
    void realizarTransacaoDespesa();

};

#endif