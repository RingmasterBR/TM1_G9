#include <iostream>
#include <fstream>
#include <stdexcept>
#include "gerenciadorfinanceiro.hpp"

GerenciadorFinanceiro::GerenciadorFinanceiro(Usuario* usuario) : usuario_(usuario) {}

Usuario* GerenciadorFinanceiro::getUsuario() {
    return usuario_;
}

// Fluxo principal do sistema: registrar um lancamento (despesa ou receita).
// O gerenciador nao calcula nada sozinho, ele so chama:
//   1. a Conta atualiza saldo e divida
//   2. cada Orcamento decide se o lancamento conta para ele
//   3. verifica se algum orcamento estourou o limite

void GerenciadorFinanceiro::registrarLancamento(Lancamentos* lancamento) {
    if (lancamento == nullptr || lancamento->conta == nullptr) {
        return;
    }

    lancamento->conta->UpdateDividaESaldo();

    for (size_t i = 0; i < orcamentos_.size(); i++) {
        orcamentos_[i]->adicionarLancamento(lancamento);
    }

    verificarOrcamentos();
}

// Cadastra um orcamento na lista, ignorando ponteiro nulo.
void GerenciadorFinanceiro::adicionarOrcamento(Orcamento* orcamento) {
    if (orcamento == nullptr) {
        return;
    }
    orcamentos_.push_back(orcamento);
}

// Percorre os orcamentos e mostra um alerta para cada um que estourou o limite.
// Se nenhum estourou, nao imprime nada.
void GerenciadorFinanceiro::verificarOrcamentos() {
    for (size_t i = 0; i < orcamentos_.size(); i++) {
        Orcamento* orcamento = orcamentos_[i];

        if (orcamento->estourouLimite()) {
            std::cout << "ALERTA: orcamento";
            if (orcamento->getCategoria() != nullptr) {
                std::cout << " de " << orcamento->getCategoria()->getNome();
            }
            std::cout << " estourou o limite de R$ " << orcamento->getLimite() << std::endl;
        }
    }
}

// Mostra na tela os orcamentos do mes/ano pedido: limite, gasto e o que sobrou.
void GerenciadorFinanceiro::gerarRelatorioMensal(int mes, int ano) {
    std::cout << "===== Relatorio de " << mes << "/" << ano << " =====" << std::endl;
    if (usuario_ != nullptr) {
        std::cout << "Usuario: " << usuario_->getNome() << std::endl;
    }

    int encontrados = 0;
    for (size_t i = 0; i < orcamentos_.size(); i++) {
        Orcamento* orcamento = orcamentos_[i];

        if (orcamento->getMes() == mes && orcamento->getAno() == ano) {
            encontrados++;
            if (orcamento->getCategoria() != nullptr) {
                std::cout << orcamento->getCategoria()->getNome();
            } else {
                std::cout << "Sem categoria";
            }
            std::cout << " | limite: " << orcamento->getLimite()
                      << " | gasto: " << orcamento->getValorGasto()
                      << " | restante: " << orcamento->getSaldoRestante() << std::endl;
        }
    }

    // "encontrados" conta quantos orcamentos sao do periodo pedido
    if (encontrados == 0) {
        std::cout << "Nenhum orcamento cadastrado para este mes." << std::endl;
    }
}

// Grava os dados em um arquivo de texto, uma linha por item, campos separados por ";"
// Se o arquivo nao puder ser aberto, lanca excecao.
void GerenciadorFinanceiro::salvarDados(std::string arquivo) {
    std::ofstream saida(arquivo.c_str());
    if (!saida.is_open()) {
        throw std::runtime_error("Nao foi possivel abrir o arquivo para escrita: " + arquivo);
    }

    if (usuario_ != nullptr) {
        saida << "USUARIO;" << usuario_->getNome() << ";" << usuario_->getId() << "\n";
    }

    for (size_t i = 0; i < orcamentos_.size(); i++) {
        Orcamento* orcamento = orcamentos_[i];
        std::string nomeCategoria = "";
        if (orcamento->getCategoria() != nullptr) {
            nomeCategoria = orcamento->getCategoria()->getNome();
        }

        saida << "ORCAMENTO;" << nomeCategoria << ";" << orcamento->getLimite() << ";"
              << orcamento->getValorGasto() << ";" << orcamento->getMes() << ";"
              << orcamento->getAno() << "\n";
    }
}

// Le o arquivo gravado pelo salvarDados. Por enquanto so conta quantas linhas
void GerenciadorFinanceiro::carregarDados(std::string arquivo) {
    std::ifstream entrada(arquivo.c_str());
    if (!entrada.is_open()) {
        throw std::runtime_error("Nao foi possivel abrir o arquivo para leitura: " + arquivo);
    }

    
    std::string linha;
    int orcamentosLidos = 0;
    while (std::getline(entrada, linha)) {
        if (linha.compare(0, 10, "ORCAMENTO;") == 0) {
            orcamentosLidos++;
        }
    }
    std::cout << "Arquivo " << arquivo << ": " << orcamentosLidos << " orcamento(s) encontrado(s)." << std::endl;
}
