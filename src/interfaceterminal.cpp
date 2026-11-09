#include "interfaceterminal.hpp"

#include <iomanip>
#include <limits>
#include <list>
#include <stdexcept>

#include "categoria.hpp"
#include "conta.hpp"
#include "despesa.hpp"
#include "gerenciadorfinanceiro.hpp"
#include "orcamento.hpp"
#include "receita.hpp"
#include "usuario.hpp"

// Rotulos dos menus. A ORDEM precisa bater com os enums TipoGasto e
// FormaPagamento, pois o indice escolhido e convertido direto para o enum.
static const std::vector<std::string> ROTULOS_TIPO_GASTO = {
    "Alimentacao", "Transporte", "Lazer", "Saude", "Educacao", "Outros"};
static const std::vector<std::string> ROTULOS_FORMA_PAGAMENTO = {
    "Credito", "Debito", "Pix"};

InterfaceTerminal::InterfaceTerminal(std::istream& in, std::ostream& out)
    : in_(in), out_(out), proximoIdUsuario_(1) {}

// Cada Usuario libera suas Contas e seu GerenciadorFinanceiro, e cada Conta
// libera suas Transacoes. O resto foi criado aqui e e liberado aqui.
InterfaceTerminal::~InterfaceTerminal() {
    for (Usuario* usuario : usuarios_) {
        delete usuario;
    }
    for (Lancamentos* lancamento : lancamentos_) {
        delete lancamento;
    }
    for (Orcamento* orcamento : orcamentos_) {
        delete orcamento;
    }
    for (auto& par : categorias_) {
        delete par.second;
    }
}

std::chrono::year_month_day InterfaceTerminal::hoje() {
    using namespace std::chrono;
    return year_month_day{floor<days>(system_clock::now())};
}

// ============================ Entrada de dados =============================
// Se a entrada acabar (Ctrl+D ou fim do arquivo), as funcoes de leitura lancam
// std::runtime_error, que e tratada em executar() para encerrar o programa.

std::string InterfaceTerminal::lerTexto(const std::string& mensagem) {
    out_ << mensagem;
    std::string texto;
    if (!std::getline(in_, texto)) {
        throw std::runtime_error("Fim da entrada.");
    }
    return texto;
}

std::string InterfaceTerminal::lerTextoNaoVazio(const std::string& mensagem) {
    while (true) {
        std::string texto = lerTexto(mensagem);
        if (!texto.empty()) {
            return texto;
        }
        out_ << "Este campo nao pode ficar vazio.\n";
    }
}

int InterfaceTerminal::lerInt(const std::string& mensagem) {
    while (true) {
        std::string texto = lerTexto(mensagem);
        try {
            size_t posicao = 0;
            int valor = std::stoi(texto, &posicao);
            if (posicao == texto.size()) {
                return valor;
            }
        } catch (const std::invalid_argument&) {
            // texto nao e numero: pede de novo
        } catch (const std::out_of_range&) {
            // numero grande demais: pede de novo
        }
        out_ << "Valor invalido. Digite um numero inteiro.\n";
    }
}

int InterfaceTerminal::lerIntEntre(const std::string& mensagem, int minimo, int maximo) {
    while (true) {
        int valor = lerInt(mensagem);
        if (valor >= minimo && valor <= maximo) {
            return valor;
        }
        out_ << "Digite um valor entre " << minimo << " e " << maximo << ".\n";
    }
}

double InterfaceTerminal::lerDoublePositivo(const std::string& mensagem) {
    while (true) {
        std::string texto = lerTexto(mensagem);
        // aceita virgula como separador decimal (ex: 12,50)
        for (char& c : texto) {
            if (c == ',') {
                c = '.';
            }
        }
        try {
            size_t posicao = 0;
            double valor = std::stod(texto, &posicao);
            if (posicao == texto.size() && valor > 0) {
                return valor;
            }
        } catch (const std::invalid_argument&) {
        } catch (const std::out_of_range&) {
        }
        out_ << "Valor invalido. Digite um numero maior que zero.\n";
    }
}

bool InterfaceTerminal::perguntarSimNao(const std::string& mensagem) {
    while (true) {
        std::string resposta = lerTexto(mensagem + " (s/n): ");
        if (resposta == "s" || resposta == "S") return true;
        if (resposta == "n" || resposta == "N") return false;
        out_ << "Responda com s ou n.\n";
    }
}

std::chrono::year_month_day InterfaceTerminal::lerData() {
    using namespace std::chrono;
    if (perguntarSimNao("Usar a data de hoje?")) {
        return hoje();
    }
    while (true) {
        int dia = lerIntEntre("Dia: ", 1, 31);
        int mes = lerIntEntre("Mes: ", 1, 12);
        int ano = lerIntEntre("Ano: ", 1900, 2100);
        year_month_day data{year{ano}, month{static_cast<unsigned>(mes)},
                            day{static_cast<unsigned>(dia)}};
        if (data.ok()) {
            return data;
        }
        out_ << "Data invalida (esse dia nao existe nesse mes). Tente de novo.\n";
    }
}

int InterfaceTerminal::escolherOpcao(const std::string& titulo, const std::vector<std::string>& rotulos) {
    out_ << titulo << "\n";
    for (size_t i = 0; i < rotulos.size(); i++) {
        out_ << "  " << i + 1 << ") " << rotulos[i] << "\n";
    }
    return lerIntEntre("Escolha: ", 1, static_cast<int>(rotulos.size())) - 1;
}

// Reutiliza a mesma Categoria para a mesma combinacao tipo + forma.
Categoria* InterfaceTerminal::escolherCategoria() {
    int tipo = escolherOpcao("Tipo de gasto/receita:", ROTULOS_TIPO_GASTO);
    int forma = escolherOpcao("Forma de pagamento:", ROTULOS_FORMA_PAGAMENTO);

    std::pair<int, int> chave{tipo, forma};
    auto encontrada = categorias_.find(chave);
    if (encontrada != categorias_.end()) {
        return encontrada->second;
    }
    Categoria* nova = new Categoria(static_cast<TipoGasto>(tipo), static_cast<FormaPagamento>(forma));
    categorias_[chave] = nova;
    return nova;
}

// ========================== Cadastro e login ===============================
Usuario* InterfaceTerminal::buscarUsuario(const std::string& nome) const {
    for (Usuario* usuario : usuarios_) {
        if (usuario->getNome() == nome) {
            return usuario;
        }
    }
    return nullptr;
}

void InterfaceTerminal::cadastrar() {
    out_ << "\n--- Cadastro ---\n";
    std::string nome = lerTextoNaoVazio("Digite seu nome: ");
    if (buscarUsuario(nome) != nullptr) {
        out_ << "Ja existe um usuario com esse nome.\n";
        return;
    }
    std::string senha = lerTexto("Digite a senha desejada: ");
    usuarios_.push_back(new Usuario(nome, proximoIdUsuario_++, senha));
    out_ << "Usuario cadastrado com sucesso!\n";
}

Usuario* InterfaceTerminal::login() {
    out_ << "\n--- Login ---\n";
    std::string nome = lerTexto("Nome de cadastro: ");
    std::string senha = lerTexto("Senha: ");

    Usuario* usuario = buscarUsuario(nome);
    if (usuario != nullptr && usuario->autenticar(senha)) {
        out_ << "Login realizado. Bem-vindo(a), " << nome << "!\n";
        return usuario;
    }
    out_ << "Nome ou senha incorretos.\n";
    return nullptr;
}

// ================================ Contas ===================================
Conta* InterfaceTerminal::criarConta(Usuario* usuario) {
    std::string nome = lerTextoNaoVazio("Nome da nova conta: ");
    if (!usuario->criarConta(nome)) {
        out_ << "Ja existe uma conta com esse nome.\n";
        return nullptr;
    }
    out_ << "Conta \"" << nome << "\" criada.\n";
    return usuario->buscarConta(nome);
}

// Deixa o usuario escolher uma conta existente ou criar uma nova.
Conta* InterfaceTerminal::escolherConta(Usuario* usuario) {
    std::list<Conta*> contas = usuario->getContas();
    if (contas.empty()) {
        out_ << "\nVoce ainda nao tem nenhuma conta.\n";
        if (!perguntarSimNao("Deseja criar uma conta agora?")) {
            return nullptr;
        }
        return criarConta(usuario);
    }

    std::vector<Conta*> indice(contas.begin(), contas.end());
    out_ << "\nSuas contas:\n";
    for (size_t i = 0; i < indice.size(); i++) {
        out_ << "  " << i + 1 << ") " << indice[i]->getNome() << "\n";
    }
    out_ << "  0) Criar nova conta\n";
    int escolha = lerIntEntre("Qual conta deseja usar? ", 0, static_cast<int>(indice.size()));
    if (escolha == 0) {
        return criarConta(usuario);
    }
    return indice[escolha - 1];
}

// ========================= Orcamentos e transacoes =========================
void InterfaceTerminal::criarOrcamento(Usuario* usuario) {
    out_ << "\n--- Novo orcamento ---\n";
    double limite = lerDoublePositivo("Limite (R$): ");
    Categoria* categoria = escolherCategoria();
    int mes = lerIntEntre("Mes (1-12): ", 1, 12);
    int ano = lerIntEntre("Ano: ", 1900, 2100);

    GerenciadorFinanceiro* gerenciador = usuario->getGerenciadorFinanceiro();
    
    //verifica se o orcamento digitado ja e existente
    for (const Orcamento* existente : gerenciador->getOrcamentos()) {
        if (existente->getCategoria()->getTipo() == categoria->getTipo() && existente->getMes() == mes && existente->getAno() == ano) {
            out_ << "Ja existe um orcamento de " << categoria->getNome() << " para "
                 << mes << "/" << ano << ".\n";
            return;
        }
    }

    Orcamento* orcamento = new Orcamento(limite, categoria, mes, ano);
    orcamentos_.push_back(orcamento);
    gerenciador->adicionarOrcamento(orcamento);

    // Despesas ja registradas no periodo tambem contam para o novo orcamento
    for (const Conta* conta : usuario->getContas()) {
        for (const Lancamentos* lancamento : conta->getLancamentos()) {
            orcamento->adicionarLancamento(lancamento);
        }
    }
    out_ << "Orcamento cadastrado.\n";
    gerenciador->verificarOrcamentos(out_);
}

void InterfaceTerminal::registrarTransacao(Usuario* usuario, Conta* conta) {
    out_ << "\n--- Nova transacao ---\n";
    int tipo = lerIntEntre("1 = Despesa, 2 = Receita: ", 1, 2);
    double valor = lerDoublePositivo("Valor (R$): ");
    Categoria* categoria = escolherCategoria();
    std::chrono::year_month_day data = lerData();
    bool fixo = perguntarSimNao("O lancamento e fixo/recorrente?");

    Lancamentos* lancamento = nullptr;

    if (tipo == 1) {
        lancamento = new Despesa(valor, categoria, data, conta, fixo);
    } else {
        lancamento = new Receita(valor, categoria, data, conta, fixo);
    }
    lancamentos_.push_back(lancamento);

    usuario->getGerenciadorFinanceiro()->registrarLancamento(lancamento, out_);

    out_ << lancamento->getTipoTexto() << " registrada.\n";

    //Se o lancamento possui data atual, isProcessado = true, se nao isProcessado = false
    //Indica ao usuario se isProcessado false que o a receita entrara no saldo quando chegar a data
    if (!lancamento->isProcessado()) {
        out_ << "A receita tem data futura e entrara no saldo quando a data chegar.\n";
    }
    out_ << std::fixed << std::setprecision(2) << "Saldo: R$ " << conta->getSaldo()
         << " | Divida: R$ " << conta->getDivida() << "\n";
}

// =============================== Relatorios ================================
//Gera relatorio do mes e ano indicado
void InterfaceTerminal::gerarRelatorio(Usuario* usuario) {
    out_ << "\n--- Relatorio ---\n";
    int mes = lerIntEntre("Mes (1-12, 0 = mes atual): ", 0, 12);
    int ano;
    if (mes == 0) {
        mes = static_cast<int>(static_cast<unsigned>(hoje().month()));
        ano = static_cast<int>(hoje().year());
    } else {
        ano = lerIntEntre("Ano: ", 1900, 2100);
    }
    out_ << "\n";
    usuario->getGerenciadorFinanceiro()->gerarRelatorioMensal(mes, ano, out_);
}

//Mostra o extrato da conta
void InterfaceTerminal::mostrarExtrato(Conta* conta) {
    out_ << "\n--- Extrato da conta " << conta->getNome() << " ---\n";
    out_ << std::fixed << std::setprecision(2);
    if (conta->getLancamentos().empty()) {
        out_ << "Nenhum lancamento.\n";
    }
    for (const Lancamentos* lancamento : conta->getLancamentos()) {
        std::chrono::year_month_day data = lancamento->getData();
        out_ << "  " << std::setfill('0') << std::setw(2) << static_cast<unsigned>(data.day())
             << "/" << std::setw(2) << static_cast<unsigned>(data.month()) << "/"
             << static_cast<int>(data.year()) << std::setfill(' ') << "  "
             << lancamento->getTipoTexto() << "  " << lancamento->getCategoria()->getNome()
             << "  R$ " << lancamento->getValor()
             << (lancamento->isFixo() ? "  (fixo)" : "")
             << (lancamento->isProcessado() ? "" : "  (pendente)") << "\n";
    }
    out_ << "Saldo: R$ " << conta->getSaldo() << " | Divida: R$ " << conta->getDivida() << "\n";
}

//gerenciador financeiro gera relatorio de dados do usuario em um arquivo .txt
void InterfaceTerminal::exportarDados(Usuario* usuario) {
    std::string arquivo = lerTextoNaoVazio("Nome do arquivo (ex: dados.txt): ");
    try {
        usuario->getGerenciadorFinanceiro()->salvarDados(arquivo);
        out_ << "Dados exportados para " << arquivo << ".\n";
    } catch (const std::runtime_error& erro) {
        out_ << "Erro: " << erro.what() << "\n";
    }
}

// ============================ Sessao do usuario ============================
//Indica as funcionalidades da sessao atual daquele usuario.
void InterfaceTerminal::sessao(Usuario* usuario) {
    Conta* conta = escolherConta(usuario);
    if (conta == nullptr) {
        out_ << "Sem conta nao e possivel continuar. Voltando ao inicio.\n";
        return;
    }

    while (true) {
        out_ << std::fixed << std::setprecision(2)
             << "\n===== " << usuario->getNome() << " | Conta: " << conta->getNome()
             << " | Saldo: R$ " << conta->getSaldo() << " =====\n"
             << "1) Nova transacao\n"
             << "2) Novo orcamento\n"
             << "3) Relatorio mensal\n"
             << "4) Extrato da conta\n"
             << "5) Trocar ou criar conta\n"
             << "6) Exportar dados para arquivo\n"
             << "0) Sair (logout)\n";
        int opcao = lerIntEntre("Escolha: ", 0, 6);

        // Erros de validacao das classes viram mensagem e o menu continua
        try {
            switch (opcao) {
                case 1: registrarTransacao(usuario, conta); break;
                case 2: criarOrcamento(usuario); break;
                case 3: gerarRelatorio(usuario); break;
                case 4: mostrarExtrato(conta); break;
                case 5: {
                    Conta* outra = escolherConta(usuario);
                    if (outra != nullptr) {
                        conta = outra;
                    }
                    break;
                }
                case 6: exportarDados(usuario); break;
                default:
                    out_ << "Sessao encerrada.\n";
                    return;
            }
        } catch (const std::invalid_argument& erro) {
            out_ << "Erro: " << erro.what() << "\n";
        }
    }
}

// =============================== Menu inicial ==============================
//Execucao principal do prompt, da ao usuario a opcao de cadastrar, logar e encerrar, 
void InterfaceTerminal::executar() {
    try {
        while (true) {
            out_ << "\n===== Gerenciador Financeiro =====\n"
                 << "1) Cadastrar\n"
                 << "2) Logar\n"
                 << "0) Encerrar\n";
            int opcao = lerIntEntre("Escolha: ", 0, 2);

            if (opcao == 0) {
                out_ << "Ate logo!\n";
                return;
            }
            if (opcao == 1) {
                cadastrar();
                if (!perguntarSimNao("\nDeseja logar agora?")) {
                    continue;
                }
            }
            Usuario* usuario = login();
            if (usuario != nullptr) {
                sessao(usuario);
            }
        }
    } catch (const std::runtime_error&) {
        // A entrada acabou (ex: Ctrl+D): encerra normalmente.
        out_ << "\nEntrada encerrada. Ate logo!\n";
    }
}
