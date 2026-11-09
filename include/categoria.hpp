/**
 * @file categoria.hpp
 * @brief Declaracao da classe Categoria e dos enums TipoGasto e FormaPagamento.
 */
#ifndef CATEGORIA_HPP
#define CATEGORIA_HPP

#include <string>

/**
 * @brief Tipos de gasto usados para classificar lancamentos e orcamentos.
 */
enum TipoGasto {
    Alimentacao,
    Transporte,
    Lazer,
    Saude,
    Educacao,
    Outros
};

/**
 * @brief Formas de pagamento possiveis para um lancamento.
 */
enum FormaPagamento {
    Credito,
    Debito,
    Pix
};

/**
 * @brief Classifica um lancamento por tipo de gasto e forma de pagamento.
 *
 * Uma categoria pode ter um nome personalizado (ex: "Mercado"). Se nao tiver,
 * o nome exibido e o nome do tipo de gasto.
 */
class Categoria {
private:
    std::string nome_;              /**< Nome personalizado (pode ser vazio). */
    TipoGasto tipoGasto_;           /**< Tipo de gasto da categoria. */
    FormaPagamento formaPagamento_; /**< Forma de pagamento da categoria. */

public:
    /**
     * @brief Cria uma categoria sem nome personalizado.
     * @param tipo Tipo de gasto.
     * @param forma Forma de pagamento.
     * @throws std::invalid_argument se tipo ou forma estiverem fora dos valores do enum.
     */
    Categoria(TipoGasto tipo, FormaPagamento forma);

    /**
     * @brief Cria uma categoria com nome personalizado.
     * @param nome Nome da categoria (ex: "Mercado").
     * @param tipo Tipo de gasto.
     * @param forma Forma de pagamento.
     * @throws std::invalid_argument se tipo ou forma estiverem fora dos valores do enum.
     */
    Categoria(const std::string& nome, TipoGasto tipo, FormaPagamento forma);

    /**
     * @brief Retorna o nome da categoria.
     * @return O nome personalizado ou, se nao houver, o nome do tipo de gasto.
     */
    std::string getNome() const;

    /**
     * @brief Retorna o tipo de gasto.
     * @return Valor do enum TipoGasto.
     */
    TipoGasto getTipo() const;

    /**
     * @brief Retorna a forma de pagamento.
     * @return Valor do enum FormaPagamento.
     */
    FormaPagamento getFormaPagamento() const;

    /**
     * @brief Converte um tipo de gasto em texto.
     * @param tipo Tipo de gasto.
     * @return Nome do tipo (ex: "Alimentacao").
     */
    static std::string tipoParaTexto(TipoGasto tipo);

    /**
     * @brief Converte uma forma de pagamento em texto.
     * @param forma Forma de pagamento.
     * @return Nome da forma (ex: "Pix").
     */
    static std::string formaParaTexto(FormaPagamento forma);
};

#endif
