#ifndef CONTA_HPP
#define CONTA_HPP

#include <iostream>
#include <usuario.hpp>

using namespace std;

class Conta {

    private :

        Usuario user;

        double saldo;

    public :

        //constructor
        Conta(string nome, int id) : user(conta, id) {}

        //retorna saldo
        double getSaldo();

        double updateSaldo(double valor);

}

#endif