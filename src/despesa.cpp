#include "despesa.hpp"

// Construtor da classe Despesa
Despesa::Despesa(double valor, std::string descricao, Categoria* categoria, std::string data, bool ehFixa, int diaCobranca)
    : Transacao(/* parâmetros exigidos pela Transacao base, ex: conta, forma, categoria, valor */),
      ehFixa_(ehFixa),
      diaCobranca_(diaCobranca) 
{}

bool Despesa::isFixa() const {
    return ehFixa_;
}

void Despesa::setFixa(bool ehFixa) {
    ehFixa_ = ehFixa;
}

int Despesa::getDiaCobranca() const {
    return diaCobranca_;
}

void Despesa::setDiaCobranca(int diaCobranca) {
    diaCobranca_ = diaCobranca;
}

double Despesa::realizarTransacaoDespesa() {
    double resultado = 0.0;
    
    int diaHoje = /* obter dia atual */; 
    int diaTransacao = /* obter dia desta despesa */; // ou diaCobranca_

    if (ehFixa_) {
        if (diaTransacao == diaHoje) {
            // Instancia o objeto transação (ajuste os parâmetros conforme o construtor da sua classe Transacao)
            Transacao transacao(*conta, FormaPagamento::Credito, categoria->getNome(), *this.valor);
            
            // Executa a atualização da dívida
            resultado = transacao.updateDivida(*this.valor);
        }
    } else {
        if (diaTransacao == diaHoje) {
            double valorModificado = valor * (-1.0);
            
            // Instancia o objeto transação utilizando o valor modificado ou a despesa
            Transacao transacao(*conta, FormaPagamento::Debito, categoria->getNome(), *this.valor);
            
            // Executa a atualização do valor/saldo
            resultado = transacao.updateSaldo(*this.valor);
        }
    }

    return resultado;
}