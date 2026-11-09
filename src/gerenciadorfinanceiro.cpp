#include "gerenciadorfinanceiro.hpp"

#include <fstream>
#include <iomanip>
#include <map>
#include <sstream>
#include <stdexcept>

#include "categoria.hpp"
#include "conta.hpp"
#include "lancamentos.hpp"
#include "orcamento.hpp"
#include "usuario.hpp"

// Formata uma data como dd/mm/aaaa
static std::string formatarData(std::chrono::year_month_day data) {
    std::ostringstream texto;
    texto << std::setfill('0') << std::setw(2) << static_cast<unsigned>(data.day()) << "/"
          << std::setw(2) << static_cast<unsigned>(data.month()) << "/"
          << static_cast<int>(data.year());
    return texto.str();
}

GerenciadorFinanceiro::GerenciadorFinanceiro(Usuario* usuario) : usuario_(usuario) {
    if (usuario == nullptr) {
        throw std::invalid_argument("O gerenciador precisa de um usuario.");
    }
}

Usuario* GerenciadorFinanceiro::getUsuario() const {
    return usuario_;
}

const std::vector<Orcamento*>& GerenciadorFinanceiro::getOrcamentos() const {
    return orcamentos_;
}

// Fluxo principal: o lancamento entra na conta, a transacao atualiza saldo e
// divida, e cada orcamento decide se o lancamento conta para ele.
void GerenciadorFinanceiro::registrarLancamento(Lancamentos* lancamento, std::ostream& out) {
    if (lancamento == nullptr) {
        throw std::invalid_argument("Lancamento nulo.");
    }
    if (lancamento->getConta()->getUsuario() != usuario_) {
        throw std::invalid_argument("O lancamento pertence a uma conta de outro usuario.");
    }

    lancamento->adicionarNaConta();
    lancamento->realizarTransacao();

    for (Orcamento* orcamento : orcamentos_) {
        orcamento->adicionarLancamento(lancamento);
    }
    verificarOrcamentos(out);
}

void GerenciadorFinanceiro::adicionarOrcamento(Orcamento* orcamento) {
    if (orcamento == nullptr) {
        throw std::invalid_argument("Orcamento nulo.");
    }
    orcamentos_.push_back(orcamento);
}

int GerenciadorFinanceiro::verificarOrcamentos(std::ostream& out) const {
    int estourados = 0;
    for (const Orcamento* orcamento : orcamentos_) {
        if (orcamento->estourouLimite()) {
            estourados++;
            out << "ALERTA: orcamento de " << orcamento->getCategoria()->getNome()
                << " (" << orcamento->getMes() << "/" << orcamento->getAno()
                << ") estourou o limite de R$ " << std::fixed << std::setprecision(2)
                << orcamento->getLimite() << " (gasto: R$ " << orcamento->getValorGasto()
                << ")\n";
        }
    }
    return estourados;
}

void GerenciadorFinanceiro::gerarRelatorioMensal(int mes, int ano, std::ostream& out) const {
    if (mes < 1 || mes > 12) {
        throw std::invalid_argument("Mes invalido (use 1 a 12).");
    }

    out << std::fixed << std::setprecision(2);
    out << "===== Relatorio de " << mes << "/" << ano << " =====\n";
    out << "Usuario: " << usuario_->getNome() << "\n";

    double totalReceitas = 0.0;
    double totalDespesas = 0.0;
    std::map<TipoGasto, double> gastosPorTipo;
    int lancamentosNoMes = 0;

    for (const Conta* conta : usuario_->getContas()) {
        out << "\nConta: " << conta->getNome() << " | saldo atual: R$ " << conta->getSaldo()
            << " | divida: R$ " << conta->getDivida() << "\n";

        for (const Lancamentos* lancamento : conta->getLancamentos()) {
            std::chrono::year_month_day data = lancamento->getData();
            if (static_cast<unsigned>(data.month()) != static_cast<unsigned>(mes) ||
                static_cast<int>(data.year()) != ano) {
                continue;
            }
            lancamentosNoMes++;
            out << "  " << formatarData(data) << "  " << std::left << std::setw(8)
                << lancamento->getTipoTexto() << std::right << "  "
                << lancamento->getCategoria()->getNome() << "  R$ " << lancamento->getValor()
                << "\n";

            if (lancamento->isDespesa()) {
                totalDespesas += lancamento->getValor();
                gastosPorTipo[lancamento->getCategoria()->getTipo()] += lancamento->getValor();
            } else {
                totalReceitas += lancamento->getValor();
            }
        }
    }

    if (lancamentosNoMes == 0) {
        out << "\nNenhum lancamento neste mes.\n";
    }

    out << "\nTotal de receitas: R$ " << totalReceitas << "\n";
    out << "Total de despesas: R$ " << totalDespesas << "\n";
    out << "Resultado do mes:  R$ " << totalReceitas - totalDespesas << "\n";

    if (!gastosPorTipo.empty()) {
        out << "\nGastos por tipo:\n";
        for (const auto& par : gastosPorTipo) {
            out << "  " << Categoria::tipoParaTexto(par.first) << ": R$ " << par.second << "\n";
        }
    }

    out << "\nOrcamentos do mes:\n";
    int orcamentosNoMes = 0;
    for (const Orcamento* orcamento : orcamentos_) {
        if (orcamento->getMes() != mes || orcamento->getAno() != ano) {
            continue;
        }
        orcamentosNoMes++;
        out << "  " << orcamento->getCategoria()->getNome()
            << " | limite: R$ " << orcamento->getLimite()
            << " | gasto: R$ " << orcamento->getValorGasto()
            << " | restante: R$ " << orcamento->getSaldoRestante()
            << (orcamento->estourouLimite() ? "  (ESTOUROU)" : "") << "\n";
    }
    if (orcamentosNoMes == 0) {
        out << "  Nenhum orcamento cadastrado para este mes.\n";
    }
}

// Uma linha por registro, campos separados por ";".
void GerenciadorFinanceiro::salvarDados(const std::string& arquivo) const {
    std::ofstream saida(arquivo);
    if (!saida.is_open()) {
        throw std::runtime_error("Nao foi possivel abrir o arquivo para escrita: " + arquivo);
    }

    saida << std::fixed << std::setprecision(2);
    saida << "USUARIO;" << usuario_->getNome() << ";" << usuario_->getId() << "\n";

    for (const Conta* conta : usuario_->getContas()) {
        saida << "CONTA;" << conta->getNome() << ";" << conta->getSaldo() << ";"
              << conta->getDivida() << "\n";
        for (const Lancamentos* lancamento : conta->getLancamentos()) {
            const Categoria* categoria = lancamento->getCategoria();
            saida << "LANCAMENTO;" << conta->getNome() << ";" << lancamento->getTipoTexto() << ";"
                  << lancamento->getValor() << ";"
                  << Categoria::tipoParaTexto(categoria->getTipo()) << ";"
                  << Categoria::formaParaTexto(categoria->getFormaPagamento()) << ";"
                  << formatarData(lancamento->getData()) << ";"
                  << (lancamento->isFixo() ? "fixo" : "variavel") << "\n";
        }
    }

    for (const Orcamento* orcamento : orcamentos_) {
        saida << "ORCAMENTO;" << orcamento->getCategoria()->getNome() << ";"
              << orcamento->getLimite() << ";" << orcamento->getValorGasto() << ";"
              << orcamento->getMes() << ";" << orcamento->getAno() << "\n";
    }
}

int GerenciadorFinanceiro::carregarDados(const std::string& arquivo) const {
    std::ifstream entrada(arquivo);
    if (!entrada.is_open()) {
        throw std::runtime_error("Nao foi possivel abrir o arquivo para leitura: " + arquivo);
    }

    // Quantidade de campos esperada para cada tipo de registro
    const std::map<std::string, int> camposPorRegistro = {
        {"USUARIO", 3}, {"CONTA", 4}, {"LANCAMENTO", 8}, {"ORCAMENTO", 6}};

    std::string linha;
    int numeroLinha = 0;
    int registros = 0;
    while (std::getline(entrada, linha)) {
        numeroLinha++;
        if (linha.empty()) {
            continue;
        }
        std::vector<std::string> campos;
        std::stringstream leitor(linha);
        std::string campo;
        while (std::getline(leitor, campo, ';')) {
            campos.push_back(campo);
        }

        auto registro = camposPorRegistro.find(campos[0]);
        if (registro == camposPorRegistro.end() ||
            static_cast<int>(campos.size()) != registro->second) {
            throw std::runtime_error("Linha " + std::to_string(numeroLinha) +
                                     " invalida no arquivo " + arquivo);
        }
        registros++;
    }
    return registros;
}
