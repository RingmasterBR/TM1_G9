#include "receita.hpp"

// Construtor da classe Receita
Receita::Receita(double valor, std::string descricao, Categoria* categoria, std::string data, bool ehFixa, int diaRecebimento)
    : Transacao(/* parâmetros exigidos pela Transacao base, ex: conta, forma, categoria, valor */),
      ehFixa_(ehFixa),
      diaRecebimento_(diaRecebimento) 
{}

bool Receita::isFixa() const {
    return ehFixa_;
}

void Receita::setFixa(bool ehFixa) {
    ehFixa_ = ehFixa;
}

int Receita::getDiaRecebimento() const {
    return diaRecebimento_;
}

void Receita::setDiaRecebimento(int diaRecebimento) {
    diaRecebimento_ = diaRecebimento;
}

double Receita::realizarTransacaoReceita() {
double resultado = 0.0; 
    // Obtem o dia atual
    int diaHoje = /* obter dia atual do sistema */; 
    int diaRecebimento = this->getDiaRecebimento(); 

    // Se for fixa e o dia de recebimento for hoje
    if (this->isFixa() && (diaRecebimento == diaHoje)) {
        // Instancia o objeto Transacao com os dados desta receita
        Transacao transacao(*conta, FormaPagamento::Pix, categoria->getNome(), *this);

    } else {
        // Se nao for do dia de hoje, nao chama a atualizacao e retorna o getSaldo da transacao
        Transacao transacao(*conta, FormaPagamento::Pix, categoria->getNome(), *this);
    }

}