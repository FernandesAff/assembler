#include "passagem_1.hpp"

list<TS> tabSimbolos;
int text = -1;
int dado = -1;

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

    for(TS t:tabSimbolos){
        cout << t.nome << " " << t.valor << " " << t.cte << " " << t.isLabel << " " << t.tam << " " << t.valorCte << endl; 
    }
    
}

void analyze (vector<string> tokens, int *labelCounter, int lc, int *pc){
    list<TD> tabDiretivas = inicializarTD();
    list<TI> tabInstrucoes = inicializarTI();
    int textAux= text, dadoAux = dado;
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
        *pc += inst.tamanho;
        if(dado != -1) printError(ERRO_SEMANTICO_MSG, lc);
    }else if(inList(tokens[0], tabDiretivas)){
        TD dir;
        inList(tokens[0], tabDiretivas, dir);
        *pc += dirAnalyzer(dir, tokens, lc, &textAux, &dadoAux);
        if(dado == -1 && upCase(dir.nome) != "SECTION") printError(ERRO_SEMANTICO_MSG, lc);
        if(textAux != -1){
            text = textAux + *pc;
        }
        if(dadoAux != -1){
            dado = dadoAux + *pc;
        }
    }else{
        printError(ERRO_SINTATICO_MSG, lc);
    }
}