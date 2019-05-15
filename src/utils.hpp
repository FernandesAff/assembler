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
    string nome;
    int valor;
} TS;

//linha da tabela de instruções
typedef struct TI{
    string nome;
    int operandos;
    int codigo;
    int tamanho;
} TI;

//linha da tabela de diretivas
typedef struct TD{
    string nome;
    int operandos;
    int tamanho;
} TD;

list<TI> inicializarTI();

TI novaInstrucao(string mnemonico, int operandos, int codigo, int tamanho);

list<TD> inicializarTD();

list<TD> inicializarTDPre();

TD novaDiretiva(string mnemonico, int operandos, int tamanho);

TS novoSimbolo(string simbolo, int valor);

//Divide a string str em elementos e passa para o vetor dest, finalizando com um "/0"
//Ignora espacos, tabs e comentarios
void split(const string& str, std::vector<string>& dest);

string upCase(const string& s);

bool validLabel(const string& label);

bool isLabel(const string& token);

template <typename T>
bool inList(const string& nome, list<T> list){
	for(auto l:list){
		if(l.nome==nome){
			return true;
		}
	}
	return false;
}

template <typename T, typename Y>
bool inList(const string& nome, list<T> list, Y& elem){
	for(auto l:list){
		if(l.nome==nome){
            elem = l;
			return true;
		}
	}
	return false;
}

void errLex(int line);

void errSin(int line);

void errSem(int line);

bool validConst(string arg);

#endif


