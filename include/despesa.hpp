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
    bool ehFixa_;
    
public:
    /**
    * @brief Construtor de despesa.
    * @param valor Valor da despesa.
    * @param descricao Descrição do gasto.
    * @param categoria Ponteiro para a categoria do gasto.
    * @param data Data da despesa.
    * @param ehFixa Indica se é uma despesa mensal.
    */
    Despesa(double valor, std::string descricao, Categoria* categoria, std::string data, bool ehFixa = false);

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
};

#endif