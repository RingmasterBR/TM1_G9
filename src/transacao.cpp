#include "transacao.hpp"

#include <chrono>
#include <stdexcept>

#include "conta.hpp"
#include "lancamentos.hpp"

Transacao::Transacao(Conta* conta, double valor)
    : conta_(conta), valor_(valor) {
    if (conta == nullptr) {
        throw std::invalid_argument("A transacao precisa de uma conta.");
    }
    saldoAnterior_ = conta->getSaldo();
    dividaAnterior_ = conta->getDivida();
    saldoFinal_ = saldoAnterior_;
    dividaFinal_ = dividaAnterior_;
    calcularSaldoEDivida();
}

// Percorre os lancamentos da conta e aplica os que ainda nao foram processados.
// O efeito de cada um e decidido pela propria subclasse (polimorfismo).
void Transacao::calcularSaldoEDivida() {
    using namespace std::chrono;
    year_month_day hoje = floor<days>(system_clock::now());

    for (Lancamentos* lancamento : conta_->getLancamentos()) {
        if (lancamento->isProcessado()) {
            continue;
        }
        if (lancamento->aplicarEfeito(saldoFinal_, dividaFinal_, hoje)) {
            lancamento->marcarProcessado();
        }
    }
}

bool Transacao::registrarNaConta() {
    if (saldoFinal_ != saldoAnterior_ || dividaFinal_ != dividaAnterior_) {
        conta_->addTransacao(this);
        return true;
    }
    return false;
}

Conta* Transacao::getConta() const {
    return conta_;
}

double Transacao::getValor() const {
    return valor_;
}

double Transacao::getSaldoAnterior() const {
    return saldoAnterior_;
}

double Transacao::getDividaAnterior() const {
    return dividaAnterior_;
}

double Transacao::getSaldoFinal() const {
    return saldoFinal_;
}

double Transacao::getDividaFinal() const {
    return dividaFinal_;
}
