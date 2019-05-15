#include "utils.hpp"

// char* lerArquivo(char* nomeArquivo){
//     ifstream file;
//     file.open(nomeArquivo);
//     long fsize;
//     char* resultado;
//     int i = 0;

//     fsize = file.tellg();
//     file.seekg(0, ios::end);
//     fsize = file.tellg() - fsize;
//     file.seekg(0, ios::beg);
    
//     resultado = (char*) malloc(fsize*sizeof(char));

//     while (file >> noskipws >> resultado[i]){
//         i++;
//     }
    
//     file.close();

//     return resultado;
// }

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
    instrucao.nome = mnemonico;
    instrucao.operandos = operandos;
    instrucao.tamanho = tamanho;
    return instrucao;
}

list<TD> inicializarTD(){
    list<TD> tabelaDeDiretivas;

    tabelaDeDiretivas.push_back(novaDiretiva((char*) "SECTION", 1, 0));
    tabelaDeDiretivas.push_back(novaDiretiva((char*) "SPACE", -1, -1));
    tabelaDeDiretivas.push_back(novaDiretiva((char*) "CONST", 1, 1));
    tabelaDeDiretivas.push_back(novaDiretiva((char*) "END", 0, 0));

    return tabelaDeDiretivas;
}

list<TD> inicializarTDPre(){
    list<TD> tabelaDeDiretivasPre;
    tabelaDeDiretivasPre.push_back(novaDiretiva((char*) "MACRO", 0, 0));
    tabelaDeDiretivasPre.push_back(novaDiretiva((char*) "EQU", 1, 0));
    tabelaDeDiretivasPre.push_back(novaDiretiva((char*) "IF", 1, 0));

    return tabelaDeDiretivasPre;
}

TD novaDiretiva(char* mnemonico, int operandos, int tamanho){
    TD diretiva;
    diretiva.nome = mnemonico;
    diretiva.operandos = operandos;
    diretiva.tamanho = tamanho;
    return diretiva;
}

TS novoSimbolo(string simbolo, int valor){
    TS simb;
    simb.nome = simbolo;
    simb.valor = valor;
    return simb;
}

void split(const string& str, vector<string>& dest){
	dest.clear();
	string buffer{""};

	for(auto c:str){
        if(c == ';') break;
		if(c != ' ' && c != '	') buffer+=c; else
		if((c == ' ' || c == '	') && buffer != "") { dest.push_back(buffer); buffer = ""; }
	}
	if(buffer != "") dest.push_back(buffer);
	dest.push_back("\n");
}

string upCase(const string& s){
    string s2 = s;
    for (int i=0; i<s.length(); i++)
        s2[i] = toupper(s[i]);
    return s2;
}

bool validLabel(const string& label){
	if(isdigit(label.at(0)) || label.length() > 50){
		return false;
	}else{
		for(auto c:label){
			if(!isalpha(c) && !isdigit(c) && c != '_' && c != ':'){
				return false;
			}
		}
	}
	return true;
}

bool isLabel(const string& token){
	return token.back() == ':';
}

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

void errLex(int line){
    cout<<"Linha " << line <<": Erro lexico\n";
}

void errSin(int line){
    cout<<"Linha " << line <<": Erro sintatico\n";
}

void errSem(int line){
    cout<<"Linha " << line <<": Erro semantico\n";
}

bool validConst(string arg){
    //neg
    if(arg.at(0) == '-'){
      arg = arg.substr(1);
    }
    //hex
    if(arg.size()>1 && arg.at(0) == '0' && arg.at(1) == 'x'){
        arg = arg.substr(2);
    }

    for(auto c:arg){
        if(!isdigit(c))
           return false;
    }
    return true;
}
