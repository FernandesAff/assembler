#include "passagem_2.hpp"

string objName;

void segundaPassagem(string preName){
    ofstream myfile;
    objName = preName.substr(0, preName.size()-4) + ".obj";

    myfile.open (objName);
    myfile << "";
    myfile.close();

    string line;
    vector<string> tokens;
    ifstream fr(preName);
    int lc = 1;
    int pc = 0;

    if(text == -1) printError(ERRO_SEMANTICO_MSG + ": SECTION TEXT INEXISTENTE");

    while(getline(fr,line)){
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
        instAnalyzer(inst, tokens, lc);
    }else if(inList(tokens[0], tabDiretivas)){
        TD dir;
        inList(tokens[0], tabDiretivas, dir);
        dirAnalyzerSem(dir, tokens, lc);
    }
}