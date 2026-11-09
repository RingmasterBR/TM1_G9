#include "lancamentos.hpp"

#include <stdexcept>

#include "conta.hpp"
#include "transacao.hpp"

Lancamentos::Lancamentos(double valor, Categoria* categoria, std::chrono::year_month_day data,
                         Conta* conta, bool fixo)
    : valor_(valor), categoria_(categoria), data_(data), conta_(conta),
      fixo_(fixo), processado_(false) {
    if (valor <= 0) {
        throw std::invalid_argument("O valor do lancamento deve ser maior que zero.");
    }
    if (categoria == nullptr) {
        throw std::invalid_argument("O lancamento precisa de uma categoria.");
    }
    if (!data.ok()) {
        throw std::invalid_argument("Data do lancamento invalida.");
    }
    if (conta == nullptr) {
        throw std::invalid_argument("O lancamento precisa de uma conta.");
    }
}

void Lancamentos::adicionarNaConta() {
    conta_->addLancamento(this);
}

void Lancamentos::realizarTransacao() {
    Transacao* transacao = new Transacao(conta_, valor_);
    // Se a transacao alterou saldo/divida, a conta passa a ser dona dela
    if (!transacao->registrarNaConta()) {
        delete transacao;
    }
}

void Lancamentos::marcarProcessado() {
    processado_ = true;
}

double Lancamentos::getValor() const {
    return valor_;
}

Categoria* Lancamentos::getCategoria() const {
    return categoria_;
}

std::chrono::year_month_day Lancamentos::getData() const {
    return data_;
}

Conta* Lancamentos::getConta() const {
    return conta_;
}

bool Lancamentos::isFixo() const {
    return fixo_;
}

bool Lancamentos::isProcessado() const {
    return processado_;
}
