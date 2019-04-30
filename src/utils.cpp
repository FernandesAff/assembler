#include "utils.hpp"

char* lerArquivo(char* nomeArquivo){
    ifstream file;
    file.open(nomeArquivo);
    long fsize;
    char* resultado;
    int i = 0;

    fsize = file.tellg();
    file.seekg(0, ios::end);
    fsize = file.tellg() - fsize;
    file.seekg(0, ios::beg);
    
    resultado = (char*) malloc(fsize*sizeof(char));

    while (file >> noskipws >> resultado[i]){
        i++;
    }
    
    file.close();

    return resultado;
}

void escreverArquivo(char* string, char* nomeArquivo){
    ofstream file;
    file.open(nomeArquivo);

    file << string;

    file.close();
}

list<TI> inicializarTI(){
    list<TI> tabelaDeInstrucoes;

    tabelaDeInstrucoes.push_back(novaInstrucao((char*) "ADD", 1, 1, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao((char*) "SUB", 1, 2, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao((char*) "MULT", 1, 3, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao((char*) "DIV", 1, 4, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao((char*) "JMP", 1, 5, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao((char*) "JMPN", 1, 6, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao((char*) "JMPP", 1, 7, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao((char*) "JMPZ", 1, 8, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao((char*) "COPY", 2, 9, 3));
    tabelaDeInstrucoes.push_back(novaInstrucao((char*) "LOAD", 1, 10, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao((char*) "STORE", 1, 11, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao((char*) "INPUT", 1, 12, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao((char*) "OUTPUT", 1, 13, 2));
    tabelaDeInstrucoes.push_back(novaInstrucao((char*) "STOP", 0, 14, 1));

    return tabelaDeInstrucoes;
}

TI novaInstrucao(char* mnemonico, int operandos, int codigo, int tamanho){
    TI instrucao;
    instrucao.codigo = codigo;
    instrucao.mnemonico = mnemonico;
    instrucao.operandos = operandos;
    instrucao.tamanho = tamanho;
    return instrucao;
}

list<TD> inicializarTD(){
    list<TD> tabelaDeDiretivas;

    tabelaDeDiretivas.push_back(novaDiretiva((char*) "SECTION", 1, 0));
    tabelaDeDiretivas.push_back(novaDiretiva((char*) "SPACE", -1, -1));
    tabelaDeDiretivas.push_back(novaDiretiva((char*) "CONST", 1, 1));
    tabelaDeDiretivas.push_back(novaDiretiva((char*) "EQU", 1, 0));
    tabelaDeDiretivas.push_back(novaDiretiva((char*) "IF", 1, 0));
    tabelaDeDiretivas.push_back(novaDiretiva((char*) "MACRO", 0, 0));
    tabelaDeDiretivas.push_back(novaDiretiva((char*) "END", 0, 0));

    return tabelaDeDiretivas;
}

TD novaDiretiva(char* mnemonico, int operandos, int tamanho){
    TD diretiva;
    diretiva.mnemonico = mnemonico;
    diretiva.operandos = operandos;
    diretiva.tamanho = tamanho;
    return diretiva;
}