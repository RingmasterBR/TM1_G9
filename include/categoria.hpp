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
 


#endif
