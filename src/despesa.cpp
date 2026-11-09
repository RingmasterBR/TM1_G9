#include "despesa.hpp"

Despesa::Despesa(double valor, Categoria* categoria, std::chrono::year_month_day data, Conta* conta, bool fixo)
    : Lancamentos(valor, categoria, data, conta, fixo) {}

// Despesa ate hoje sai do saldo; despesa futura vira divida.
bool Despesa::aplicarEfeito(double& saldo, double& divida, std::chrono::year_month_day hoje) const {
    if (data_ > hoje) {
        divida += valor_;
    } else {
        saldo -= valor_;
    }
    return true;
}

bool Despesa::isDespesa() const {
    return true;
}

std::string Despesa::getTipoTexto() const {
    return "Despesa";
}
