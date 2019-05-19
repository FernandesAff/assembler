#include "passagem_1.hpp"

list<TS> tabSimbolos;

void primeiraPassagem (string preName){
    string line;
    vector<string> tokens;
    ifstream fr(preName);
    int labelCounter = 0; //
    int lc = 1;
    int pc = 0;

    while(getline(fr,line)){
        split(line,tokens);
        analyze(tokens, &labelCounter, lc , &pc);
        lc++;
        labelCounter = 0;
    }

    // for(TS t:tabSimbolos){
    //     cout << t.nome << " " << t.valor << endl; 
    // }
    
}

void analyze (vector<string> tokens, int *labelCounter, int lc, int *pc){
    list<TD> tabDiretivas = inicializarTD();
    list<TI> tabInstrucoes = inicializarTI();
    if(isLabel(tokens[0])){
        labelAnalyzer(tokens[0], lc, *pc, labelCounter);
        if(tokens.size() > 2){
            vector<string> newTokens;
            copyVector(1, tokens.size(), tokens, &newTokens);
            analyze(newTokens, labelCounter, lc, pc);
        }
    }else if(inList(tokens[0], tabInstrucoes)){
        TI inst;
        inList(tokens[0], tabInstrucoes, inst);
        instAnalyzer(inst, tokens, lc, pc);
    }else if(inList(tokens[0], tabDiretivas)){
        TD dir;
        inList(tokens[0], tabDiretivas, dir);
        *pc += dirAnalyzer(dir, tokens, lc);
    }else{
        printError(ERRO_SINTATICO_MSG, lc);
    }
}