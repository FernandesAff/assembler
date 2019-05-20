#ifndef PASSAGEM_2_HPP
#define PASSAGEM_2_HPP

#include <iostream>
#include "analisador_semantico.hpp"
#include "analisador_sintatico.hpp"
#include "utils.hpp"
#include "passagem_1.hpp"

extern string objName;

void segundaPassagem(string preName);

void analyze (vector<string> tokens, int lc);

#endif