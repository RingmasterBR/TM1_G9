#include "conta.hpp"

#include <stdexcept>

#include "lancamentos.hpp"
#include "transacao.hpp"

Conta::Conta(Usuario* usuario, const std::string& nome)
    : usuario_(usuario), nome_(nome), saldo_(0.0), divida_(0.0) {
    if (nome.empty()) {
        throw std::invalid_argument("O nome da conta nao pode ser vazio.");
    }
}

// Desaloca as transacoes registradas na conta
Conta::~Conta() {
    for (Transacao* transacao : transacoes_) {
        delete transacao;
    }
}

std::string Conta::getNome() const {
    return nome_;
}

Usuario* Conta::getUsuario() const {
    return usuario_;
}

double Conta::getSaldo() const {
    return saldo_;
}

double Conta::getDivida() const {
    return divida_;
}

const std::list<Lancamentos*>& Conta::getLancamentos() const {
    return lancamentos_;
}

const std::list<Transacao*>& Conta::getTransacoes() const {
    return transacoes_;
}

void Conta::addLancamento(Lancamentos* lancamento) {
    if (lancamento == nullptr) {
        throw std::invalid_argument("Lancamento nulo.");
    }
    if (lancamento->getConta() != this) {
        throw std::invalid_argument("O lancamento pertence a outra conta.");
    }
    lancamentos_.push_back(lancamento);
}

//Adiciona transacao a lista de transacao e atualiza o saldo e a divida da conta
void Conta::addTransacao(Transacao* transacao) {
    if (transacao == nullptr) {
        throw std::invalid_argument("Transacao nula.");
    }
    transacoes_.push_back(transacao);
    saldo_ = transacao->getSaldoFinal();
    divida_ = transacao->getDividaFinal();
}
