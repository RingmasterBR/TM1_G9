#include "transacao.hpp"
#include "conta.hpp"
#include "despesa.hpp"
#include "receita.hpp"
#include <stdexcept>

// Construtor para transações do tipo Despesa
Transacao::Transacao(const Conta& contaRef, FormaPagamento formaDePagamento, std::string categoriaNome, valorTransacao)
    : conta(new Conta(contaRef)),
      despesa(new Despesa(despesaObj)),
      forma(formaDePagamento),
      categoria(categoriaNome),
      valor(valorTransacao),
      saldoAnterior(contaRef.getSaldo()),
      dividaAnterior(contaRef.getDivida())
{
    // Calcula os valores finais pós-transação
    saldoFinal = updateSaldo(*conta);
    dividaFinal = updateDivida(*conta);
}

// Destrutor para liberação da memória alocada dinamicamente
Transacao::~Transacao() {
    delete conta;
    delete receita;
    delete despesa;
}

Conta Transacao::getConta() const {
    if (conta != nullptr) {
        return *conta;
    }
    throw std::runtime_error("Conta associada nula.");
}

double Transacao::getSaldoFinal() const {
    return saldoFinal;
}

double Transacao::getDividaFinal() const {
    return dividaFinal;
}

double Transacao::getSaldoAnterior() const {
    return saldoAnterior;
}

double Transacao::getDividaAnterior() const {
    return dividaAnterior;
}

int Transacao::ValidarDados() {}


double Transacao::updateSaldo() {
    double saldoAtual = saldoAnterior;
    double dividaAtual = dividaAnterior;

    // Se for despesa paga no cartão de crédito, o saldo não diminui imediatamente na conta corrente
    if (forma != FormaPagamento::Credito) {
        saldoAtual -= valor;
    }
    // Se for receita, o saldo aumenta
    else if () {
        saldoAtual += valor;
    }

    return saldoAtual;
}

double Transacao::updateDivida() {
    double dividaAtual = dividaAnterior;
    double saldoAtual = saldoAnterior;

    // Se for despesa efetuada via crédito, incrementa o valor da dívida da conta
    if (forma == FormaPagamento::Credito) {
        dividaAtual += valor;
    }
    else {
        saldoAtual += valor;
    }

    return dividaAtual;
}

