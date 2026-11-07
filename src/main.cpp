// Compilar: g++ -std=c++20 *.cpp -o gerenciador
// (std::chrono::year_month_day e C++20)

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "categoria.hpp"
#include "conta.hpp"
#include "despesa.hpp"
#include "gerenciadorfinanceiro.hpp"
#include "orcamento.hpp"
#include "receita.hpp"
#include "usuario.hpp"

// AJUSTE: rotulos dos enums. A ORDEM e a QUANTIDADE precisam bater com
// TipoGasto e FormaPagamento do seu categoria.hpp (o numero escolhido e
// convertido direto para o enum com static_cast).
static const std::vector<std::string> ROTULOS_TIPO_GASTO = {
    "Alimentacao", "Transporte", "Lazer", "Outros"};
static const std::vector<std::string> ROTULOS_FORMA_PAGAMENTO = {
    "Credito", "Debito", "Pix"};

// ===================== Estado global do programa ===========================
static std::vector<Usuario*> usuarios;
static int proximoIdUsuario = 1;

// O Orcamento compara Categoria* por ponteiro, entao a mesma combinacao
// tipo+forma tem que reutilizar o MESMO objeto Categoria.
static std::map<std::pair<int, int>, Categoria*> categorias;

// ============================ Entrada de dados =============================
static void limparEntrada() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static int lerInt(const std::string& msg) {
    int v;
    while (true) {
        std::cout << msg;
        if (std::cin >> v) {
            limparEntrada();
            return v;
        }
        if (std::cin.eof()) std::exit(0);
        limparEntrada();
        std::cout << "Valor invalido. Tente de novo.\n";
    }
}

static double lerDouble(const std::string& msg) {
    double v;
    while (true) {
        std::cout << msg;
        if (std::cin >> v) {
            limparEntrada();
            return v;
        }
        if (std::cin.eof()) std::exit(0);
        limparEntrada();
        std::cout << "Valor invalido. Tente de novo.\n";
    }
}

static std::string lerTexto(const std::string& msg) {
    std::string s;
    std::cout << msg;
    if (!std::getline(std::cin, s)) std::exit(0);
    return s;
}

static bool perguntarSimNao(const std::string& msg) {
    while (true) {
        std::string r = lerTexto(msg + " (s/n): ");
        if (r == "s" || r == "S") return true;
        if (r == "n" || r == "N") return false;
        std::cout << "Responda com s ou n.\n";
    }
}

// ================================= Datas ===================================
static std::chrono::year_month_day hoje() {
    using namespace std::chrono;
    return year_month_day{floor<days>(system_clock::now())};
}

static int mesDe(const std::chrono::year_month_day& d) {
    return static_cast<int>(static_cast<unsigned>(d.month()));
}

static int anoDe(const std::chrono::year_month_day& d) {
    return static_cast<int>(d.year());
}

static std::chrono::year_month_day lerData() {
    using namespace std::chrono;
    if (perguntarSimNao("Usar a data de hoje?")) return hoje();

    while (true) {
        int d = lerInt("Dia: ");
        int m = lerInt("Mes: ");
        int a = lerInt("Ano: ");
        year_month_day data{year{a}, month{static_cast<unsigned>(m)},
                            day{static_cast<unsigned>(d)}};
        if (data.ok()) return data;
        std::cout << "Data invalida. Tente de novo.\n";
    }
}

// ============================== Categoria ==================================
static int escolherOpcao(const std::string& titulo,
                         const std::vector<std::string>& rotulos) {
    std::cout << titulo << "\n";
    for (size_t i = 0; i < rotulos.size(); i++) {
        std::cout << "  " << i + 1 << ") " << rotulos[i] << "\n";
    }
    while (true) {
        int op = lerInt("Escolha: ");
        if (op >= 1 && op <= static_cast<int>(rotulos.size())) return op - 1;
        std::cout << "Opcao invalida.\n";
    }
}

static Categoria* escolherCategoria() {
    int tipo = escolherOpcao("Tipo de gasto:", ROTULOS_TIPO_GASTO);
    int forma = escolherOpcao("Forma de pagamento:", ROTULOS_FORMA_PAGAMENTO);

    std::pair<int, int> chave{tipo, forma};
    auto it = categorias.find(chave);
    if (it != categorias.end()) return it->second;

    Categoria* nova = new Categoria(static_cast<TipoGasto>(tipo),
                                    static_cast<FormaPagamento>(forma));
    categorias[chave] = nova;
    return nova;
}

// ======================= Passo 1: cadastro de usuario ======================
static Usuario* buscarUsuarioPorNome(const std::string& nome) {
    for (Usuario* u : usuarios) {
        if (u->getName() == nome) return u;
    }
    return nullptr;
}

static void cadastrar() {
    std::cout << "\n--- Cadastro ---\n";
    std::string nome = lerTexto("Digite seu nome: ");
    if (nome.empty()) {
        std::cout << "O nome nao pode ser vazio.\n";
        return;
    }
    if (buscarUsuarioPorNome(nome) != nullptr) {
        std::cout << "Ja existe um usuario com esse nome.\n";
        return;
    }
    std::string senha = lerTexto("Digite a senha desejada: ");

    Usuario* novo = new Usuario(nome, proximoIdUsuario++, senha);
    usuarios.push_back(novo);
    std::cout << "Usuario cadastrado com sucesso!\n";
}

// ============================ Passo 2: login ===============================
// Devolve o usuario cujo nome e senha batem, ou nullptr.
static Usuario* login() {
    std::cout << "\n--- Login ---\n";
    std::string nome = lerTexto("Nome de cadastro: ");
    std::string senha = lerTexto("Senha: ");

    for (Usuario* u : usuarios) {
        // autenticar() precisa existir em Usuario: compara a senha digitada
        if (u->getName() == nome && u->autenticar(senha)) {
            std::cout << "Login realizado. Bem-vindo(a), " << nome << "!\n";
            return u;
        }
    }
    std::cout << "Nome ou senha incorretos.\n";
    return nullptr;
}

// ============================ Passo 3: conta ===============================
// Se o usuario nao tem conta, oferece criar. Devolve a conta a usar, ou nullptr.
static Conta* garantirConta(Usuario* usuario) {
    std::list<Conta*> contas = usuario->getContas();

    if (contas.empty()) {
        std::cout << "\nVoce ainda nao tem nenhuma conta.\n";
        if (!perguntarSimNao("Deseja criar uma conta agora?")) return nullptr;

        std::string nome = lerTexto("Nome da nova conta: ");
        if (nome.empty() || !usuario->criarConta(nome)) {
            std::cout << "Nao foi possivel criar a conta (nome vazio ou repetido).\n";
            return nullptr;
        }
        std::cout << "Conta \"" << nome << "\" criada e adicionada a sua lista de contas.\n";
        return usuario->getContas().back();  // criarConta faz push_back
    }

    // Ja tem conta(s): se for so uma, usa; se forem varias, deixa escolher.
    if (contas.size() == 1) return contas.front();

    std::vector<Conta*> indice(contas.begin(), contas.end());
    std::cout << "\nSuas contas:\n";
    for (size_t i = 0; i < indice.size(); i++) {
        std::cout << "  " << i + 1 << ") " << indice[i]->NomeDaConta << "\n";
    }
    while (true) {
        int escolha = lerInt("Qual conta deseja usar? ");
        if (escolha >= 1 && escolha <= static_cast<int>(indice.size())) {
            return indice[escolha - 1];
        }
        std::cout << "Opcao invalida.\n";
    }
}

// =========================== Passo 4: orcamento ============================
// O orcamento precisa existir ANTES da transacao para o gasto ser contado nele.
static void criarOrcamento(Usuario* usuario) {
    std::cout << "\n--- Novo orcamento ---\n";
    double limite = lerDouble("Limite (R$): ");
    if (limite <= 0) {
        std::cout << "O limite precisa ser maior que zero.\n";
        return;
    }
    Categoria* categoria = escolherCategoria();
    int mes = lerInt("Mes (1-12): ");
    int ano = lerInt("Ano: ");
    if (mes < 1 || mes > 12) {
        std::cout << "Mes invalido.\n";
        return;
    }

    usuario->getGerenciadorFinanceiro()->adicionarOrcamento(
        new Orcamento(limite, categoria, mes, ano));
    std::cout << "Orcamento cadastrado.\n";
}

// =========================== Passo 5: transacao ============================
static void realizarTransacao(Usuario* usuario, Conta* conta) {
    std::cout << "\n--- Nova transacao ---\n";
    int tipo = lerInt("1 = Despesa, 2 = Receita: ");
    if (tipo != 1 && tipo != 2) {
        std::cout << "Tipo invalido.\n";
        return;
    }

    double valor = lerDouble("Valor (R$): ");
    if (valor <= 0) {
        std::cout << "O valor precisa ser maior que zero.\n";
        return;
    }

    Categoria* categoria = escolherCategoria();
    std::chrono::year_month_day data = lerData();
    bool fixo = perguntarSimNao("O lancamento e fixo/recorrente?");

    Lancamentos* lancamento = nullptr;
    if (tipo == 1) {
        lancamento = new Despesa(valor, categoria, data, conta, fixo);
    } else {
        lancamento = new Receita(valor, categoria, data, conta, fixo);
    }

    lancamento->addLancamentosFuturos();  // entra na lista de lancamentos da Conta
    lancamento->realizarTransacao();      // cria a Transacao da Conta

    // O gerenciador repassa o lancamento aos orcamentos e confere os limites
    usuario->getGerenciadorFinanceiro()->registrarLancamento(lancamento);

    std::cout << (tipo == 1 ? "Despesa" : "Receita") << " registrada.\n";
    std::cout << "Saldo: R$ " << conta->getSaldo()
              << " | Divida: R$ " << conta->getDivida() << "\n";
}

// =========================== Passo 6: relatorio ============================
static void gerarRelatorio(Usuario* usuario) {
    std::cout << "\n--- Relatorio ---\n";
    int mes = lerInt("Mes (1-12, 0 = mes atual): ");
    int ano;
    if (mes == 0) {
        mes = mesDe(hoje());
        ano = anoDe(hoje());
    } else {
        ano = lerInt("Ano: ");
    }

    GerenciadorFinanceiro* gerenciador = usuario->getGerenciadorFinanceiro();
    gerenciador->gerarRelatorioMensal(mes, ano);
    gerenciador->verificarOrcamentos();  // alerta dos orcamentos que estouraram
}

// ============================ Sessao do usuario ============================
static void sessao(Usuario* usuario) {
    Conta* conta = garantirConta(usuario);
    if (conta == nullptr) {
        std::cout << "Sem conta nao e possivel continuar. Voltando ao inicio.\n";
        return;
    }

    if (perguntarSimNao("\nDeseja definir um orcamento antes de comecar?")) {
        criarOrcamento(usuario);
    }

    bool primeira = true;
    while (perguntarSimNao(primeira ? "\nDeseja fazer alguma transacao?"
                                    : "\nDeseja fazer outra transacao?")) {
        realizarTransacao(usuario, conta);
        primeira = false;
    }

    if (perguntarSimNao("\nDeseja gerar algum relatorio?")) {
        gerarRelatorio(usuario);
    }

    std::cout << "\nSessao encerrada.\n";
}

// ================================= main ====================================
int main() {
    while (true) {
        std::cout << "\n===== Gerenciador Financeiro =====\n"
                  << "1) Cadastrar\n"
                  << "2) Logar\n"
                  << "0) Encerrar\n";
        int op = lerInt("Escolha: ");

        if (op == 0) {
            std::cout << "Ate logo!\n";
            return 0;
        }
        if (op != 1 && op != 2) {
            std::cout << "Opcao invalida.\n";
            continue;
        }

        if (op == 1) {
            cadastrar();
            if (!perguntarSimNao("\nDeseja logar agora?")) continue;
        }

        Usuario* usuario = login();
        if (usuario != nullptr) sessao(usuario);
    }
}