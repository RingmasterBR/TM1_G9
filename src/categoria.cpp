#include "categoria.hpp"

#include <stdexcept>

// Garante que os valores recebidos (muitas vezes vindos de um static_cast de int)
// existem nos enums.
static void validarEnums(TipoGasto tipo, FormaPagamento forma) {
    if (tipo < Alimentacao || tipo > Outros) {
        throw std::invalid_argument("Tipo de gasto invalido.");
    }
    if (forma < Credito || forma > Pix) {
        throw std::invalid_argument("Forma de pagamento invalida.");
    }
}

Categoria::Categoria(TipoGasto tipo, FormaPagamento forma)
    : nome_(""), tipoGasto_(tipo), formaPagamento_(forma) {
    validarEnums(tipo, forma);
}

Categoria::Categoria(const std::string& nome, TipoGasto tipo, FormaPagamento forma)
    : nome_(nome), tipoGasto_(tipo), formaPagamento_(forma) {
    validarEnums(tipo, forma);
}

std::string Categoria::getNome() const {
    if (!nome_.empty()) {
        return nome_;
    }
    return tipoParaTexto(tipoGasto_);
}

TipoGasto Categoria::getTipo() const {
    return tipoGasto_;
}

FormaPagamento Categoria::getFormaPagamento() const {
    return formaPagamento_;
}

std::string Categoria::tipoParaTexto(TipoGasto tipo) {
    switch (tipo) {
        case Alimentacao: return "Alimentacao";
        case Transporte:  return "Transporte";
        case Lazer:       return "Lazer";
        case Saude:       return "Saude";
        case Educacao:    return "Educacao";
        default:          return "Outros";
    }
}

std::string Categoria::formaParaTexto(FormaPagamento forma) {
    switch (forma) {
        case Credito: return "Credito";
        case Debito:  return "Debito";
        default:      return "Pix";
    }
}
