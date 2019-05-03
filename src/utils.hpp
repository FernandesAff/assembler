#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

//linha da tabela de simbolos
typedef struct TS{
    char* nome;
    int* valor;
} TS;

//linha da tabela de instruções
typedef struct TI{
    char* nome;
    int operandos;
    int codigo;
    int tamanho;
} TI;

//linha da tabela de diretivas
typedef struct TD{
    char* nome;
    int operandos;
    int tamanho;
} TD;

char* lerArquivo(char* nomeArquivo);

void escreverArquivo(char* string, char* nomeArquivo);

list<TI> inicializarTI();

TI novaInstrucao(char* mnemonico, int operandos, int codigo, int tamanho);

list<TD> inicializarTD();

list<TD> inicializarTDPre();

TD novaDiretiva(char* mnemonico, int operandos, int tamanho);

TS novoSimbolo(char* simbolo, int* valor);

//Divide a string str em elementos e passa para o vetor dest, finalizando com um "/0"
//Ignora espacos, tabs e comentarios
void split(const string& str, std::vector<string>& dest);

string upCase(const string& s);

bool validLabel(const string& label);

bool isLabel(const string& token);

template <typename T>
bool inList(const string& nome, T list);

#endif


