#include <iostream>
#include "src/pre_processador.hpp"
#include "src/passagem_1.hpp"
#include "src/passagem_2.hpp"
#include "src/utils.hpp"

int main(int argc, char const *argv[]){ 
    string fileIn = argv[1];
    preProc(fileIn);
    return 0;
}
