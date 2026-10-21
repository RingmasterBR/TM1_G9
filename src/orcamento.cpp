#include "orcamento.hpp"

// Construtor: define o limite, a categoria e o periodo (mes/ano) do orcamento.
// O valorGasto_ comeca em 0, porque ainda nao houve nenhum gasto.
Orcamento::Orcamento(double limite, Categoria* categoria, int mes, int ano)
    : limite_(limite), valorGasto_(0), categoria_(categoria), mes_(mes), ano_(ano) {}

 // Soma um lancamento no total gasto, mas so se ele "pertencer" a este orcamento.
void Orcamento::adicionarLancamento(Lancamentos* lancamento) {
    if (lancamento == nullptr) {
        return;
    }
    // Receitas nao entram no orcamento de gastos
    if (lancamento->tipo != Lancamentos::TipoDespesa) {
        return;
    }
    // Precisa ser da mesma categoria e do mesmo mes/ano do orcamento
    if (lancamento->categoria != categoria_) {
        return;
    }
    
    //  Tem que ser do mesmo mes e ano do orcamento.
    //    A data do lancamento e um std::chrono::year_month_day. Os static_cast
    //    convertem o mes e o ano dela para int, para comparar com mes_ e ano_.
    int mesDoLancamento = static_cast<int>(static_cast<unsigned>(lancamento->data.month()));
    int anoDoLancamento = static_cast<int>(lancamento->data.year());
    if (mesDoLancamento != mes_ || anoDoLancamento != ano_) {
    }
    valorGasto_ += lancamento->valor;
}

bool Orcamento::estourouLimite() const {
    return valorGasto_ > limite_;
}

// Quanto ainda pode ser gasto. Fica negativo se o limite foi ultrapassado.
double Orcamento::getSaldoRestante() const {
    return limite_ - valorGasto_;
}

// Troca o limite. Nao mexe no valor ja gasto.
void Orcamento::setLimite(double novoLimite) {
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