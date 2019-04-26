#include <iostream>
#include "utils.hpp"

typedef struct LinhaMNT{
    char* rotulo;
    int numArgs;
    int indice;
} LinhaMNT;


typedef struct LinhaMDT{
    char* codigo;
} LinhaMNT;

void expandirMacro(LinhaMDT linhaMDT, char* saida);