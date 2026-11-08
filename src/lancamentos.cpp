
#include <string>
#include <chrono>
#include <list>
#include "categoria.hpp"
#include "conta.hpp"
#include "lancamentos.hpp"
#include "transacao.hpp"

//Adiciona o lancamento na lista de lancamentos da conta
void Lancamentos :: addLancamentosFuturos(){
    if (conta != nullptr) {
        conta->addLancamento(this);
    }
}

//Instancia objeto de transacao
void Lancamentos :: realizarTransacao(){
    if (conta == nullptr) {
        return;
    }
    Transacao* t = new Transacao(conta, valor);
    // Se a transacao alterou saldo/divida, a conta passa a ser dona dela
    if (!t->updateListaTransacao()) {
        delete t;
    }
} 



