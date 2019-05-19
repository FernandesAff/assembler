#ifndef ANALISADOR_SEMANTICO_HPP
#define ANALISADOR_SEMANTICO_HPP

#include <iostream>
#include "utils.hpp"

void instAnalyzerSem(TI inst, vector<string> tokens, int lc);

void dirAnalyzerSem(TD dir, vector<string> tokens, int lc);

bool textAnalyzer(vector<string> token);

#endif