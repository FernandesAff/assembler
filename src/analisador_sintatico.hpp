#ifndef ANALISADOR_SINTATICO_HPP
#define ANALISADOR_SINTATICO_HPP

#include <iostream>
#include "utils.hpp"

extern list<TS> tabSimbolos;

void labelAnalyzer(string label, int lc, int pc, int* labelCounter);

bool sameLineLabel(int labelCounter);

int dirAnalyzer(TD dir, vector<string> tokens, int lc, int *text, int *data);

#endif