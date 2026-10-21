#include <iostream>
#include <list>
#include <string>

#include "transacao.hpp"
#include "conta.hpp"

// Construtor corrigido usando a lista de inicialização correta
Conta::Conta(Usuario* usuario, std::string nomeDaContaAtual) 
    : user(usuario), 
    saldo(0.0), 
    divida(0.0), 
    NomeDaConta(nomeDaContaAtual) {}

void Conta::setSaldo() {
    if (!listaTransacao.empty()) {
        saldo = listaTransacao.back()->getSaldoFinal();
    }
} 

void Conta::setDivida() {
    if (!listaTransacao.empty()) {
        divida = listaTransacao.back()->getDividaFinal();
    }
}

void Conta::addLancamento(Lancamentos* lancamento) { 
    lancamentosFuturos.push_back(lancamento);
}

void Conta::addTransacao(Transacao* transacao) {
    listaTransacao.push_back(transacao);
    setSaldo();
    setDivida();
}

double Conta::getSaldo() {
    return saldo;
}

double Conta::getDivida() {
    return divida;
}