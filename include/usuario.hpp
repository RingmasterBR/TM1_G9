#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <iostream>
#include <string>
#include <list>

// Forward declaration para evitar dependência circular com Conta
class Conta;

class Usuario {
    private :
        std::string nome;
        int id;
        std::string senha;
        std::list<Conta*> listaContas; 

    public :
        Usuario(std::string nomeUsuario, int idUsuario, std::string senhaUsuario);
        int getUserId();
        std::string getName();
        std::list<Conta*> getContas();
        
        // Retorna true (1) se a conta foi criada com sucesso e false (0) se já existir
        bool criarConta(std::string nomedaConta);
};

#endif