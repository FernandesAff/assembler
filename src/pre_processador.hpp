#ifndef PRE_PROCESSADOR_HPP
#define PRE_PROCESSADOR_HPP

#include <iostream>
#include <vector>
#include <string>
#include "utils.hpp"

//Nome, numero de argumentos e definicao da macro
typedef struct MNDT{
    string nome;
    int arg;
    std::string def;
} MNDT;

void equ(const string& label, const string& arg, list<TS>& tab, int line);

//se false, pula prox linha. Em caso de erro retorna true
bool ifd(const string& label, list<TS>& tab, int line);

string takeFName(string fName);

void writeLine(string &labelAnt, const vector<string> &tokens, ofstream &fw);

void preProc(string fileIn);

#endif