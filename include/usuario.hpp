#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <iostream>
#include <string>

using namespace std;

class Usuario {

    private :

        /// @param nome Nome do usuário.
        string nome;

        /// @param id ID do usuário.
        int id;

    public :

        /**
        * @brief Construtor: carrega o nome e id do usuário.
        * @param nome Nome do usuário.
        * @param id   ID do usuário.
        */
        Usuario(string nome, int id) : nome(nome), id(id) {}

        /**
        * @brief Retorna o nome do usuário.
        * @return Nome do usuário.
        */
        string getNome();

        /**
        * @brief Retorna o ID do usuário.
        * @return ID do usuário.
        */
        int getId();

};

#endif