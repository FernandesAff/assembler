#ifndef MACRO_HPP
#define MACRO_HPP

#include <iostream>
#include "utils.hpp"

typedef struct LinhaMNT{
    char* rotulo;
    int numArgs;
    int indice;
} LinhaMNT;


typedef struct LinhaMDT{
    char* codigo;
} LinhaMDT;

void expandirMacro(LinhaMDT linhaMDT, char* saida);

#endif