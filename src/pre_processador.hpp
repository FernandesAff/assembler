#ifndef PRE_PROCESSADOR_HPP
#define PRE_PROCESSADOR_HPP

#include <iostream>
#include <vector>
#include <string>
#include "utils.hpp"

void equ(const string& label, const string& arg, list<TS>& tab, int line);

//se false, pula prox linha. Em caso de erro retorna true
bool ifd(const string& label, list<TS>& tab, int line);

string takeFName(string fName);

std::vector<int> preProc(string fileIn);

#endif