#ifndef ANALISADOR_SEMANTICO_HPP
#define ANALISADOR_SEMANTICO_HPP

#include <iostream>
#include "utils.hpp"
#include "analisador_sintatico.hpp"
#include "passagem_1.hpp"
#include "passagem_2.hpp"

void dirAnalyzerSem(TD dir, vector<string> tokens, int lc);

bool textAnalyzer(vector<string> token);

void instAnalyzer(TI inst, vector<string> tokens, int lc);

int analyzeExpression(string token1, string token2, string token3, int lc);

vector<int> analyzeCopy(vector<string> tokens, int lc);

int analyzeAccOps(vector<string> tokens, TI inst, int lc);

int analyzeJmpOps(vector<string> tokens, TI inst, int lc);

int analyzeStoreOps(vector<string> tokens, TI inst, int lc);

bool varDeclared(string token);

bool sectionText(TS simbolo);

bool labelDeclared(string token);

#endif