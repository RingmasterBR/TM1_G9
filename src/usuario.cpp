#include <iostream>
#include <string>
#include <list>

#include "usuario.hpp"
#include "conta.hpp"
#include "gerenciadorfinanceiro.hpp"

// Construtor usando a lista de inicialização
Usuario::Usuario(std::string nomeUsuario, int idUsuario, std::string senhaUsuario): nome(nomeUsuario), id(idUsuario), senha(senhaUsuario) {
     gerenciadorFinanceiro = new GerenciadorFinanceiro(this);
} 

// Desaloca o gerenciador e as contas criadas por criarConta
Usuario::~Usuario() {
    delete gerenciadorFinanceiro;
    for (Conta* c : listaContas) {
        delete c;
    }
}

bool Usuario::autenticar(std::string senhaDigitada) {
    return senha == senhaDigitada;
}

int Usuario::getUserId() {
    return id;
}

std::string Usuario::getName() {
    return nome;
}

GerenciadorFinanceiro* Usuario::getGerenciadorFinanceiro(){
    return gerenciadorFinanceiro;
}

// Percorre a lista de contas do usuário para verificar duplicidade e criar nova conta
bool Usuario::criarConta(std::string nomedaConta) {
    for (auto* c : listaContas) {
        if (c->NomeDaConta == nomedaConta) {
            return false; // Conta com esse nome já existe
        }
    }
    // Se não encontrou nenhuma igual, cria  e adiciona
    Conta* novaConta = new Conta(this, nomedaConta);
    listaContas.push_back(novaConta);
    return true;
}

std::list<Conta*> Usuario::getContas() {
    return listaContas;
}
