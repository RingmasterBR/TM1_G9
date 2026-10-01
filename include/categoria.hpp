#ifndef CATEGORIA_HPP
#define CATEGORIA_HPP

//Inclusoes propria c++
#include <iostream>
#include <string>

//Inclusoes do projeto
#include "usuario.hpp"
#include "conta.hpp"
#include "categoria.hpp"

/**
 * @brief Tipo de gasto associado a uma categoria.
 */
enum class TipoGasto {
    Alimentacao,
    Transporte,
    Lazer,
    Saude,
    Educacao,
    Outros
};
 
/**
 * @brief Forma de pagamento utilizada na transação.
 */

enum class categoria {
    Credito,
    Debito,
    Pix
};

/**
 * @brief Representa uma categoria de gasto, combinando o tipo de gasto
 *        (ex: alimentação, transporte) e a forma de pagamento utilizada
 *        (ex: crédito, débito, pix).
 */

class Categoria {
private:
    std::string nome;
    TipoGasto tipo;
    FormaPagamento forma;

public:
    /**
     * @brief Construtor da classe Categoria.
     * @param nome Nome da categoria.
     * @param tipo Tipo de gasto associado.
     * @param forma Forma de pagamento associada.
     */
    Categoria(std::string nome, TipoGasto tipo, FormaPagamento forma);
 
    /**
     * @brief Retorna o nome da categoria.
     * @return Nome da categoria.
     */
    std::string getNome();
 
    /**
     * @brief Retorna o tipo de gasto da categoria.
     * @return Tipo de gasto.
     */
    TipoGasto getTipo();
 
    /**
     * @brief Retorna a forma de pagamento da categoria.
     * @return Forma de pagamento.
     */
    FormaPagamento getFormaPagamento();
};



#endif
