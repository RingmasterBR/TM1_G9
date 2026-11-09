#include "usuario.hpp"

#include <stdexcept>

#include "conta.hpp"
#include "gerenciadorfinanceiro.hpp"

Usuario::Usuario(const std::string& nome, int id, const std::string& senha)
    : nome_(nome), id_(id), senha_(senha), gerenciador_(nullptr) {
    if (nome.empty()) {
        throw std::invalid_argument("O nome do usuario nao pode ser vazio.");
    }
    if (id <= 0) {
        throw std::invalid_argument("O id do usuario deve ser positivo.");
    }
    gerenciador_ = new GerenciadorFinanceiro(this);
}

// Desaloca o gerenciador e as contas criadas por criarConta
Usuario::~Usuario() {
    delete gerenciador_;
    for (Conta* conta : contas_) {
        delete conta;
    }
}

int Usuario::getId() const {
    return id_;
}

std::string Usuario::getNome() const {
    return nome_;
}

std::list<Conta*> Usuario::getContas() const {
    return contas_;
}

Conta* Usuario::buscarConta(const std::string& nomeConta) const {
    for (Conta* conta : contas_) {
        if (conta->getNome() == nomeConta) {
            return conta;
        }
    }
    return nullptr;
}

GerenciadorFinanceiro* Usuario::getGerenciadorFinanceiro() const {
    return gerenciador_;
}

bool Usuario::autenticar(const std::string& senhaDigitada) const {
    return senha_ == senhaDigitada;
}

bool Usuario::criarConta(const std::string& nomeConta) {
    if (nomeConta.empty()) {
        throw std::invalid_argument("O nome da conta nao pode ser vazio.");
    }
    if (buscarConta(nomeConta) != nullptr) {
        return false; // ja existe conta com esse nome
    }
    contas_.push_back(new Conta(this, nomeConta));
    return true;
}
