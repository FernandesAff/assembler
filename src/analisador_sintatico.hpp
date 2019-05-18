#ifndef ANALISADOR_SINTATICO_HPP
#define ANALISADOR_SINTATICO_HPP

#include <iostream>
#include "utils.hpp"

extern list<TS> tabSimbolos;

void printError(string msgErro, int line);

bool labelAnalyzer(string label, int lc, int pc, int* labelCounter);

bool sameLineLabel(int labelCounter);

bool textAnalyzer(string token, int counter);

#endif