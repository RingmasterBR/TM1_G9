#ifndef CONTA_HPP
#define CONTA_HPP

#include <iostream>
#include "usuario.hpp"

class Conta {

    private :

        /// @param user Usuário associado a conta.
        Usuario user;

        /// @param saldo Saldo atual da conta.
        double saldo;

        /// @param divida Divida total da conta.
        double divida;

    public :

        /**
        * @brief Construtor: cria a conta e carrega o Nome e ID para o usuário.
        * @param nome Nome do usuário.
        * @param id   ID do usuário.
        */
        Conta(string nome, int id) : user(conta, id) {}

        /**
        * @brief Retorna o Saldo atual da conta.
        * @return Saldo atual.
        */
        double getSaldo();

        /**
        * @brief Retorna a Divida total da conta.
        * @return Divida atual.
        */
        double getDivida();

        /**
        * @brief Soma um valor ao saldo da conta.
        * @param valor Valor a ser somado.
        */
        double updateSaldo(double valor);

        /**
        * @brief Define um valor à Divida da conta.
        * @param valor Novo valor.
        */
        double setDivida(double valor);

        /**
        * @brief Subtrai um valor ao saldo da conta.
        * @param valor Valor a ser subtraido.
        */
        double subSaldo(double valor);

}

#endif