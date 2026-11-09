/**
 * @file main.cpp
 * @brief Ponto de entrada do Sistema de Gerenciamento de Gastos Pessoais.
 */
#include <exception>
#include <iostream>

#include "interfaceterminal.hpp"

/**
 * @brief Cria a interface no terminal e executa o menu principal.
 * @return 0 se o programa terminou normalmente, 1 em caso de erro inesperado.
 */
int main() {
    try {
        InterfaceTerminal interface(std::cin, std::cout);
        interface.executar();
    } catch (const std::exception& erro) {
        std::cerr << "Erro inesperado: " << erro.what() << "\n";
        return 1;
    }
    return 0;
}
