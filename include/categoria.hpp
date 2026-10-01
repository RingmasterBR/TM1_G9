#ifndef CATEGORIA_HPP
#define CATEGORIA_HPP

//Inclusoes proprias da linguagem
#include <iostream>
#include <string>
#include <list>

//Inclusoes do projeto
#include "usuario.hpp"
#include "conta.hpp"
#include "transacao.hpp"

/**
 * @brief Classe responsável por definir e padronizar as categorias de gastos.
 * 
 * Gerencia o agrupamento de transações financeiras de acordo com suas categorias e
 * fornece métodos para listagem e filtragem por tipo de gasto.
 */
class Categoria{
    
    public :
    //Atributos
        /**
         * @brief Nome da categoria atual.
         */
        std::string categoria;

        /**
         * @brief Lista contendo todas as transações registradas.
         */
        std::list<Transacao> transacoes;

        /**
         * @brief Lista de transações filtradas por uma categoria específica.
         */
        std::list<Transacao> transacoesPorCategorias;

        /**
         * @brief Enumeração das categorias padrão para classificação de gastos.
         */
        enum categoriaGasto {Alimentacao, Saude, Moradia, Transporte, Lazer, Outros};

        /**
         * @brief Construtor padrão da classe Categoria.
         * 
         * Deve inicializar os atributos com valores padrão.
         */
        Categoria(){};

        /**
         * @brief Sobrecarga de construtor que recebe o nome da categoria.
         * @param categoria Nome do tipo de categoria a ser atribuído.
         */
        Categoria(std::string categoria){};

        /**
         * @brief Sobrecarga de construtor que recebe uma transação.
         * @param transacao Referência para a transação inicializadora.
         */
        Categoria(Transacao& transacao){};

        /**
         * @brief Sobrecarga de construtor que recebe uma transação e o nome da categoria para registro.
         * @param transacao Referência para a transação.
         * @param categoria Nome da categoria a ser registrada.
         */
        Categoria(Transacao& transacao, std::string categoria){}

        /**
         * @brief Destrutor padrão da classe Categoria.
         */
        ~Categoria() = default;

        /**
         * @brief Insere novas transações na lista geral de transações.
         * @param transacao Referência constante para a transação a ser inserida.
         */
        void InserirTransacoes(const Transacao& transacao);
        
        /**
         * @brief Define a categoria com base na indicação contida na transação.
         * @param transacao Referência constante para a transação contendo a categoria.
         */
        void setCategoriaGasto(const Transacao& transacao);

        /**
         * @brief Valida a categoria informada e atribui "Outros" caso seja diferente das enunciadas no enum.
         */
        void ValidarCategoria();
        
        /**
         * @brief Retorna a lista contendo todas as transações registradas.
         * @param transacao Transação parâmetro para a consulta.
         * @return std::list<Transacao> Lista com todas as transações.
         */
        std::list<Transacao> getListTransacoes(const Transacao& transacao) const;

        /**
         * @brief Retorna a lista de transações filtradas por uma categoria específica.
         * @param transacoes Referência para a lista base de transações.
         * @param transacao Referência constante para a transação com o critério de filtro.
         * @return std::list<Transacao> Lista de transações filtradas por categoria.
         */
        std::list<Transacao> getListTransacoesCategoria(std::list<Transacao>& transacoes, const Transacao& transacao) const;
 };

#endif  