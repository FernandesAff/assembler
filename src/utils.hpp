#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <list>

using namespace std;

//linha da tabela de simbolos
typedef struct TS{
    char* simbolo;
    int* valor;
} TS;

//linha da tabela de instruções
typedef struct TI{
    char* mnemonico;
    int operandos;
    int codigo;
    int tamanho;
} TI;

//linha da tabela de diretivas
typedef struct TD{
    char* mnemonico;
    int operandos;
    int tamanho;
} TD;

char* lerArquivo(char* nomeArquivo);

void escreverArquivo(char* string, char* nomeArquivo);

list<TI> inicializarTI();

TI novaInstrucao(char* mnemonico, int operandos, int codigo, int tamanho);

list<TD> inicializarTD();

TD novaDiretiva(char* mnemonico, int operandos, int tamanho);

#endif