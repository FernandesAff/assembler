#include "passagem_2.hpp"

void segundaPassagem(string preName){
    string line;
    vector<string> tokens;
    ifstream fr(preName);
    int lc = 1;
    int pc = 0;

    while(getline(fr,line)){
        if(lc == 1) 
        split(line,tokens);
        analyze(tokens, lc);
        lc++;
    }    
}

void analyze (vector<string> tokens, int lc){
    list<TD> tabDiretivas = inicializarTD();
    list<TI> tabInstrucoes = inicializarTI();
    if(isLabel(tokens[0])){
        if(tokens.size() > 2){
            vector<string> newTokens;
            copyVector(1, tokens.size(), tokens, &newTokens);
            analyze(newTokens, lc);
        }
    }else if(inList(tokens[0], tabInstrucoes)){
        TI inst;
        inList(tokens[0], tabInstrucoes, inst);
        instAnalyzerSem(inst, tokens, lc);
    }else if(inList(tokens[0], tabDiretivas)){
        TD dir;
        inList(tokens[0], tabDiretivas, dir);
        dirAnalyzerSem(dir, tokens, lc);
    }
}