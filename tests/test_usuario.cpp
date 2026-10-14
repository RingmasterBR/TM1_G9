#include "doctest.h"
#include "usuario.hpp"
 
TEST_CASE("Usuario - Criacao e getters basicos") {
    Usuario u("Ana", 1);
 
    CHECK(u.getNome() == "Ana");
    CHECK(u.getId() == 1);
}
 
TEST_CASE("Usuario - Usuarios diferentes e copia") {
    Usuario ana("Ana", 1);
    Usuario bruno("Bruno", 2);
    Usuario copia = bruno;
 
    CHECK(ana.getNome() != bruno.getNome());
    CHECK(ana.getId() != bruno.getId());
    CHECK(copia.getNome() == "Bruno");
    CHECK(copia.getId() == 2);
}
