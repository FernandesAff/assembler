#include "passagem_1.hpp"

list<TS> tabSimbolos;

void primeiraPassagem (string preName){
    list<TD> tabDiretivas = inicializarTD();
    list<TI> tabInstrucoes = inicializarTI();
    string line;
    vector<string> tokens;
    ifstream fr(preName);
    int labelCounter = 0; //
    int lc = 1;
    int pc = 0;

    while(getline(fr,line)){
        split(line,tokens);
        if(tokens[0] != "\0"){
            for(int t=0;t<tokens.size()-1;t++){
                if(isLabel(tokens[t])){
                    labelAnalyzer(tokens[t], lc, pc, &labelCounter);
                }else if(inList(tokens[t], tabInstrucoes)){
                    TI inst;
                    inList(tokens[t], tabInstrucoes, inst);
                    cout << "INST " << inst.nome << endl;
                }else if(inList(tokens[t], tabDiretivas)){
                    TD dir;
                    inList(tokens[t], tabDiretivas, dir);
                    cout << "DIR " << dir.nome << endl;
                }
            }
        }
        lc++;
        labelCounter = 0;
    }
}