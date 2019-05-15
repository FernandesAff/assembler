/* 
Passagem zero do montador, retira espacos, tabs e quebras de linha desnecessarios.
Processa as diretivas de pre-processamento EQU e IF e MACRO
Recebe o arquivo <nome>.asm contendo o codigo do usuario.
Gera um arquivo pre-processado <nome>.pre salvo em /out 

Erros detectados (somente relacionados com diretivas de pre processamento):
-- Nome de rotulo invalido
-- Rotulo nao definido (todo IF deve ter um EQU antes)
-- Rotulo repetido
-- Diretiva sem argumento
-- Diretiva com argumento invalido
*/

#include "pre_processador.hpp"

void equ(const string& label, const string& arg, list<TS>& tab, int line){
	string nLabel = label.substr(0,label.size()-1);
	if(arg == "/0" || !validConst(arg) || !validLabel(label)){ 
		errLex(line); //argumento ausente ou argumento invalido ou label invalida
	}
	else{
		if(inList(nLabel,tab))
			errSem(line);
		else	
			tab.push_back(novoSimbolo((nLabel), stoi(arg)));
	}
}

bool ifd(const string& label, list<TS>& tab, int line){
	bool b;
	TS simbol;
	if(label == "\0" || !validLabel(label)){
		errLex(line); //label ausente ou invalida
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

void writeLine(string labelAnt, vector<string> &tokens, ofstream &fw){
	int t;
	if(labelAnt != ""){
		fw << labelAnt << " ";
		labelAnt = "";
	}
	for(t=0;t<tokens.size()-2;t++){
		fw << tokens[t] << " ";
	}
	fw << tokens[t] << endl;
}

string preProc(string fileIn){
	int lineCount = 0;
	string line, labelEqu = "", nomeLabel = "", labelAnt = "", labelAntMacro = "";
    list<TS> tabelaDeEqus;
	list<TD> tabelaDirPre = inicializarTDPre();
    vector<string> tokens;
	list<MNDT> macros;

    ifstream fr(fileIn);
	string fileName = takeFName(fileIn);
	ofstream fw(fileName+".pre");
    
	while(getline(fr,line)){
		lineCount++;
		split(line,tokens);
		if(tokens[0] != "\0"){
			nomeLabel = "";
			for(int t=0;t<tokens.size();t++){
				if(isLabel(tokens[t])){
					if(nomeLabel == "" && labelAnt == ""){ 
						nomeLabel = (tokens[t]);
					}else{ //+ de 1 label na linha: ignora, escreve a linha e vai pra proxima
						writeLine(labelAnt, tokens, fw);
						break;
					}
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
								errSin(lineCount); //label ausente
							}
						if(labelEqu != ""){
							equ(upCase(labelEqu), tokens[t+1], tabelaDeEqus, lineCount);
							nomeLabel = "/0";
						}
					}else if(upCase(tokens[t]) == "IF"){
						if(!ifd(upCase(tokens[t+1]), tabelaDeEqus, lineCount)){
							getline(fr,line);
							lineCount++;
						}
					}
					else{

					}
					break;
				}
				else if(tokens[t]=="\n"){
					if(nomeLabel != "\0") labelAnt=nomeLabel;
				}
				else{
					writeLine(labelAnt, tokens, fw);
					break;
				}
			}
		}
	}
	return fileName;
}
/* 
Ler a linha, incrementar counter e separar
nomeLabel = "";
Procurar Labels ou diretivas de pre-processamento na lista
	Se elemento 0 for NULL, proxima linha
	Se achou label, verifica validade, verifica se nomeLabel = "" e guarda em nomeLabel
	Se achou diretiva (nao le mais essa linha):
		Se EQU, verifica se nomeLabel != "" (se for, verifica labelAnt), verifica se existe argumento e se eh valido
			Procura label L na tabela e, se nao achar, salvar
			nomeLabel = "\0" (a label foi usada) 
		SE IF, verifica se existe argumento e eh valido, verifica na tab, incrementa e pula se true	
		SE MACRO, verifica nome valido e num de arg
			Salvar nome e numero de variaveis na MNDT, ativar wMacro. Se labelAnt!="" guarda em labelAntMacro
		SE END, verifica se esta em modo macro
			Desativa wMacro e recupera labelAntMacro se !=""
	Se fim da linha
		Se nomeLabel != "\0" -> labelAnt = nomeLabel
	Se nao
		Verifica se ha labelAnt nao usada (perde a linha que a label apareceu, mas como ja eh 
			verificado se ha erro na label aqui entao nao importa mais)
		Copia linha, salva o numero da linha e prox linha
			
	*/

