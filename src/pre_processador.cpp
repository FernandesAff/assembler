/* 
Passagem zero do montador, retira espacos, tabs e quebras de linha desnecessarios.
Processa as diretivas de pre-processamento EQU e IF
Recebe o arquivo <nome>.asm contendo o codigo do usuario.
Gera um arquivo pre-processado <nome>.pre salvo em /out 
Retorna um vetor que relaciona as linhas dos arquivos de entrada e saida.

Erros detectados:
-- Nome de rotulo invalido ok
-- Rotulo nao definido (todo IF deve ter um EQU antes) ok
-- Rotulo repetido
-- Dois rotulos na mesma linha ok
-- Diretiva sem argumento
-- Diretiva com argumento invalido
*/

#include "pre_processador.hpp"
#include "utils.cpp"

void equ(const string& label, const string& arg, list<TS>& tab, int line){
	if(arg == "/0" || !validConst(arg)) 
		errLex(line);
	else
		if(inList(label,tab)) 
			errSem(line);
		else	
			tab.push_back(novoSimbolo(label.substr(0,label.size()-1), stoi(arg)));
}

bool ifd(const string& label, list<TS>& tab, int line){
	bool b;
	TS simbol;
	if(label == "\0" || !validLabel(label)){
		errLex(line);
		b = true;
	}else{
		if(inList(label,tab,simbol)){
			if(simbol.valor == 0)
				b = false;
			else
				b = true;
		}else{			
			errSem(line);
			b = true;
		}
	}	
	return b;
}

string takeFName(string fName){
	string buff = "";
	for(auto c:fName){
		if(c == '.') return buff;
		(c != '/')? buff+=c:buff="";
		
	}
}

std::vector<int> preProc(string fileIn){

	int lineCount = 0;
	string line, labelEqu = "", nomeLabel = "", labelAnt = "";
    list<TS> tabelaDeEqus;
	list<TD> tabelaDirPre = inicializarTDPre();
    std::vector<string> tokens;
	std::vector<int> lines;

    std::ifstream fr(fileIn);
	string fileName = takeFName(fileIn);
	std::ofstream fw(fileName+".pre");
    
	while(std::getline(fr,line)){
		lineCount++;
		split(line,tokens);
		if(tokens[0] != "\0"){
			nomeLabel = "";
			for(int t=0;t<tokens.size();t++){
				if(isLabel(tokens[t])){
					if(!validLabel(tokens[t]))
						errLex(lineCount);
					if(nomeLabel != "") 
						errSin(lineCount);
					else
						nomeLabel = (tokens[t]);
				}
				else if(inList(upCase(tokens[t]),tabelaDirPre)){
					if(upCase(tokens[t]) == "EQU"){
						if(nomeLabel != "")
							labelEqu = nomeLabel;
						else 
							if(labelAnt != ""){
								labelEqu = labelAnt;
								labelAnt = "";
							}else{
								errSin(lineCount);
							}
						if(labelEqu != ""){
							equ(upCase(labelEqu), tokens[t+1], tabelaDeEqus, lineCount);
							nomeLabel = "/0";
						}
					}else{
						if(!ifd(upCase(tokens[t+1]), tabelaDeEqus, lineCount)){
							std::getline(fr,line);
							lineCount++;
						}
					}
					break;
				}
				else if(tokens[t]=="\0"){
					if(nomeLabel != "\0") labelAnt=nomeLabel;
				}
				else{
					if(labelAnt != ""){
						fw << labelAnt << " ";
						labelAnt = "";
					}
					for(auto t:tokens){
						fw << t << " ";
					}
					fw << endl;
					lines.push_back(lineCount);
					break;
				}
			}
		}
	}
}

