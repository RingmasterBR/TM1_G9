#include "receita.hpp"

Receita::Receita(double valor, Categoria* categoria, std::chrono::year_month_day data,
                 Conta* conta, bool fixo)
    : Lancamentos(valor, categoria, data, conta, fixo) {}

// Receita so entra no saldo quando a data chega; antes disso fica pendente.
bool Receita::aplicarEfeito(double& saldo, double& /*divida*/,
                            std::chrono::year_month_day hoje) const {
    if (data_ > hoje) {
        return false;
    }
    saldo += valor_;
    return true;
}

bool Receita::isDespesa() const {
    return false;
}

std::string Receita::getTipoTexto() const {
    return "Receita";
}
