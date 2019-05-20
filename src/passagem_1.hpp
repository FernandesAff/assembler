#ifndef PASSAGEM_1_HPP
#define PASSAGEM_1_HPP

#include <iostream>
#include "analisador_sintatico.hpp"
#include "utils.hpp"

extern int text;
extern int dado;

void primeiraPassagem (string preName);

void analyze (vector<string> tokens, int *labelCounter, int lc, int *pc);

#endif