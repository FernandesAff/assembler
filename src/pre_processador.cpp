/* 
Passagem zero do montador, retira espacos, tabs e quebras de linha desnecessarios.
Processa as diretivas de pre-processamento EQU e IF
Recebe o arquivo <nome>.asm contendo o codigo do usuario.
Gera um arquivo pre-processado <nome>.pre salvo em /out 
Retorna um vetor que relaciona as linhas dos arquivos de entrada e saida.

Erros detectados:
- Nome de rotulo invalido
- Rotulo nao definido (todo IF deve ter um EQU antes)
- Rotulo repetido
- Dois rotulos na mesma linha
- Diretiva sem argumento
- Diretiva com argumento invalido
*/

#include "pre_processador.hpp"
#include "utils.cpp"

std::vector<int> preProc(string fileIn){
	
	int lineCount = 0;
	string line, nomeLabel = "", labelAnt = "";
    list<TS> tabelaDeEqus;
	list<TD> tabelaDirPre = inicializarTDPre();
    std::vector<string> tokens;
	std::vector<int> lines;

    std::ifstream fr(fileIn);
	std::ofstream fw("fileOut.pre"); //TODO: arrumar o nome do arquivo
    
	while(std::getline(fr,line)){
		lineCount++;
		split(line,tokens);
		if(tokens[0] != "\0"){
			nomeLabel = "";
			for(int t=0;t<tokens.size();t++){
				if(isLabel(tokens[t])){
					if(!validLabel(tokens[t])) cout<<"Linha " << lineCount <<": Erro lexico\n";
					if(nomeLabel != "") cout<<"Linha " << lineCount << ": Erro sintatico\n"; 
					else nomeLabel = t;
				}
				else if(inList(upCase(tokens[t]),tabelaDirPre)){
					break;
				}
				else if(tokens[t]=="\0"){
					if(nomeLabel != "\0") labelAnt=nomeLabel;
				}
				else{
					if(labelAnt != "") fw << labelAnt << " "; //perde a linha que a label apareceu
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

	/* 
	Ler a linha, incrementar counter e separar
    nomeLabel = "";
	Procurar Labels ou diretivas de pre-processamento na lista
        Se elemento 0 for NULL, proxima linha
        Se achou label, verifica validade, verifica se nomeLabel = "" e guarda em nomeLabel
        Se achou diretiva (nao le mais essa linha):
            Se EQU, verifica se nomeLabel != "" (se for, verifica labelAnt), verifica validade, 
			verifica se existe argumento e se eh valido
                Procura label L na tabela e, se nao achar, salvar
                nomeLabel = "\0" (a label foi usada)
			SE IF, verifica se existe argumento e eh valido, verifica na tab, incrementa e pula se true	
		Se fim da linha
			Se nomeLabel != "\0" -> labelAnt = nomeLabel
		Se nao
			Verifica se ha labelAnt nao usada (perde a linha que a label apareceu, mas como ja eh 
				verificado se ha erro na label aqui entao nao importa mais)
			Copia linha, salva o numero da linha e prox linha
			
	*/