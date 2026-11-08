#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <iostream>
#include <string>
#include <list>


// Forward declaration para evitar dependência circular com Conta
class Conta;
class GerenciadorFinanceiro;

class Usuario {
    private :
        std::string nome;
        int id;
        std::string senha;
        std::list<Conta*> listaContas;
        GerenciadorFinanceiro* gerenciadorFinanceiro;

    public :
        Usuario(std::string nomeUsuario, int idUsuario, std::string senhaUsuario = "");
        ~Usuario();

        // Usuario e dono das contas e do gerenciador (desaloca no destrutor),
        // entao nao pode ser copiado
        Usuario(const Usuario&) = delete;
        Usuario& operator=(const Usuario&) = delete;

        int getUserId();
        std::string getName();
        std::list<Conta*> getContas();
        GerenciadorFinanceiro* getGerenciadorFinanceiro();

        // Retorna true se a senha digitada for a senha do usuario
        bool autenticar(std::string senhaDigitada);

        // Retorna true (1) se a conta foi criada com sucesso e false (0) se já existir
        bool criarConta(std::string nomedaConta);
        


};

#endif