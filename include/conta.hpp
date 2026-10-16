ifndef CONTA_HPP
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
        Conta(string nome, int id) : user(nome, id), saldo(0), divida(0) {}
 
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
        * @brief Update o valor de divida e de saldo.
        */
 
        void UpdateDividaESaldo(){}
 
 
};
 
#endif
