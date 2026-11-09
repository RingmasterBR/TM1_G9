#include "orcamento.hpp"

#include <stdexcept>

#include "categoria.hpp"
#include "lancamentos.hpp"

Orcamento::Orcamento(double limite, Categoria* categoria, int mes, int ano)
    : limite_(limite), valorGasto_(0.0), categoria_(categoria), mes_(mes), ano_(ano) {
    if (limite <= 0) {
        throw std::invalid_argument("O limite do orcamento deve ser maior que zero.");
    }
    if (categoria == nullptr) {
        throw std::invalid_argument("O orcamento precisa de uma categoria.");
    }
    if (mes < 1 || mes > 12) {
        throw std::invalid_argument("Mes do orcamento invalido (use 1 a 12).");
    }
}

// Soma o lancamento so se for uma despesa do mesmo tipo de gasto e do mesmo mes/ano.
// A comparacao e pelo tipo de gasto (e nao pelo objeto Categoria), para que uma
// despesa de Alimentacao paga no Pix conte no mesmo orcamento de uma paga no Debito.
bool Orcamento::adicionarLancamento(const Lancamentos* lancamento) {
    if (lancamento == nullptr || !lancamento->isDespesa()) {
        return false;
    }
    if (lancamento->getCategoria()->getTipo() != categoria_->getTipo()) {
        return false;
    }
    std::chrono::year_month_day data = lancamento->getData();
    int mesLancamento = static_cast<int>(static_cast<unsigned>(data.month()));
    int anoLancamento = static_cast<int>(data.year());
    if (mesLancamento != mes_ || anoLancamento != ano_) {
        return false;
    }
    valorGasto_ += lancamento->getValor();
    return true;
}

bool Orcamento::estourouLimite() const {
    return valorGasto_ > limite_;
}

double Orcamento::getSaldoRestante() const {
    return limite_ - valorGasto_;
}

void Orcamento::setLimite(double novoLimite) {
    if (novoLimite <= 0) {
        throw std::invalid_argument("O limite do orcamento deve ser maior que zero.");
    }
    limite_ = novoLimite;
}

double Orcamento::getLimite() const {
    return limite_;
}

double Orcamento::getValorGasto() const {
    return valorGasto_;
}

Categoria* Orcamento::getCategoria() const {
    return categoria_;
}

int Orcamento::getMes() const {
    return mes_;
}

int Orcamento::getAno() const {
    return ano_;
}
