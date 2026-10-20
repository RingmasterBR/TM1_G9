
#include <string>
#include <chrono>
#include <list>
#include "categoria.hpp"
#include "conta.hpp"
#include "lancamentos.hpp"
#include "transacao.hpp"

//Instancia objeto de transacao
void Lancamentos :: realizarTransacao(){
    new Transacao(conta, valor);
} 



