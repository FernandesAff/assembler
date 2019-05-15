#include "passagem_1.hpp"

void primeiraPassagem (string preName){
    list<TD> tabDiretivas = inicializarTD();
    list<TI> tabInstrucoes = inicializarTI();
    list<TS> tabSimbolos = 
    string line;
    vector<string> tokens;
    ifstream fr(preName);

    while(getline(fr,line)){
        split(line,tokens);

        if(tokens[0] != "\0"){
            nomeLabel = "";
            for(int t=0;t<tokens.size();t++){
                if(isLabel(tokens[t])){

                }
            }
        }
    }
}