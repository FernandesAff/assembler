#ifndef ANALISADOR_SINTATICO_HPP
#define ANALISADOR_SINTATICO_HPP

#include <iostream>
#include "utils.hpp"

extern list<TS> tabSimbolos;

void printError(string msgErro, int line);

void labelAnalyzer(string label, int lc, int pc, int* labelCounter);

bool sameLineLabel(int labelCounter);

bool textAnalyzer(string token, int counter);

void instAnalyzer(TI inst, vector<string> tokens, int lc, int *pc);

int dirAnalyzer(TD dir, vector<string> tokens, int lc);

void analyzeExpression(vector<string> tokens, int lc);

void analyzeCopy(vector<string> tokens, int lc);

#endif