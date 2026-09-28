#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <iostream>
#include <string>

using namespace std;

class Usuario {

    private :

        string nome;
        int id;

    public :

        // constructor 
        Usuario(string nome, int id) : nome(nome), id(id) {}

        //retorna o nome
        string getNome();

        //retorna id 
        int getId();

};

#endif