#ifndef TIPOTRANSACAO_HPP
#define TIPOTRANSACAO_HPP

//Inclusoes propria c++
#include <iostream>
#include <string>

//Inclusoes do projeto
#include "usuario.hpp"
#include "conta.hpp"
#include "categoria.hpp"

enum class TipoTransacao {
    Entrada,
    Saida
};

#endif