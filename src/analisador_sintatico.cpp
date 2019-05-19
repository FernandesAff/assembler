#include "analisador_sintatico.hpp"

void printError(string msgErro, int line){
    cout << RED << "Linha " << line << ":" << msgErro << endl;
}

void labelAnalyzer(string label, int lc, int pc, int* labelCounter){
    if (!validLabel(label)){
        printError(ERRO_LEXICO_MSG, lc);
    } else if(inList(label, tabSimbolos)){
        printError(ERRO_SEMANTICO_MSG, lc); //verificar se esse é o erro adequado
    } else if(sameLineLabel(*labelCounter)){
        printError(ERRO_SINTATICO_MSG, lc);
    } else{
        tabSimbolos.push_back(novoSimbolo(label.substr(0, label.size()-1), pc));
    }
    labelCounter++;
}

bool sameLineLabel(int labelCounter){
    return (labelCounter > 0 ?  true : false);
}

bool textAnalyzer(string token, int counter){
    if(counter == 0){
        return (upCase(token).compare("SECTION") == 0 ? true : false);
    }else if(counter == 1){
        return (upCase(token).compare("TEXT") == 0 ? true : false);
    }else{
        return false;
    }
}

void instAnalyzer(TI inst, vector<string> tokens, int lc, int *pc){
    if(upCase(inst.nome) == "COPY"){
        analyzeCopy(tokens, lc);
    }else if(upCase(inst.nome) == "STOP"){
        if(tokens.size() != 2) printError(ERRO_SINTATICO_MSG, lc);
    }else if(tokens.size() == inst.operandos){
        analyzeExpression(tokens, lc);
    }else if(tokens.size() - 2  == inst.operandos){
        if(!validVar(tokens[1])) printError(ERRO_LEXICO_MSG, lc);
    }else{
        printError(ERRO_SINTATICO_MSG, lc);
    }
    *pc += inst.tamanho;
}

int dirAnalyzer(TD dir, vector<string> tokens, int lc){
    int increment = 0;
    if(upCase(dir.nome) == "SECTION"){
        if(tokens.size() == 3){
            if(upCase(tokens[1]) != "DATA" && upCase(tokens[1]) != "TEXT") printError(ERRO_SINTATICO_MSG, lc);
        }else {
            printError(ERRO_SINTATICO_MSG, lc);
        }
    }else if(upCase(dir.nome) == "SPACE"){
        if(tokens.size() == 2){
            increment++;
        }else if(tokens.size() == 3){
            if(isNumber(tokens[1])){
                increment += stoi(tokens[1]);
            }else{
                printError(ERRO_SINTATICO_MSG, lc);
            }
        }else {
            printError(ERRO_SINTATICO_MSG, lc);
        }
    }else if(upCase(dir.nome) == "CONST"){
        if(tokens.size() == 3){
            if(validConst(tokens[1])){
                increment++;
            }else{
               printError(ERRO_SINTATICO_MSG, lc); 
            }
        }else{
            printError(ERRO_SINTATICO_MSG, lc);
        }
    }else{
        printError(ERRO_SINTATICO_MSG, lc);
    }
    return increment;
}

void analyzeExpression(vector<string> tokens, int lc){
    if(!validVar(tokens[1])) printError(ERRO_LEXICO_MSG, lc);
    if(tokens[2] != "+") printError(ERRO_SINTATICO_MSG, lc);
    if(!validVar(tokens[3])) printError(ERRO_LEXICO_MSG, lc);
}

void analyzeCopy(vector<string> tokens, int lc){
    if(tokens.size() == 6){
        if(tokens[2] == "+"){
            if(!validVar(tokens[1])) printError(ERRO_LEXICO_MSG, lc);
            if(!validVar(tokens[3].substr(0, tokens[3].size()-1))) printError(ERRO_LEXICO_MSG, lc);
            if(tokens[3].back() != ',') printError(ERRO_SINTATICO_MSG, lc);
            if(!validVar(tokens[4])) printError(ERRO_LEXICO_MSG, lc);
        }else if(tokens[3] == "+"){
            if(!validVar(tokens[1].substr(0, tokens[1].size()-1))) printError(ERRO_LEXICO_MSG, lc);
            if(tokens[1].back() != ',') printError(ERRO_SINTATICO_MSG, lc);
            if(!validVar(tokens[2])) printError(ERRO_LEXICO_MSG, lc);
            if(!validVar(tokens[4])) printError(ERRO_LEXICO_MSG, lc);
        }else{
            printError(ERRO_SINTATICO_MSG, lc);
        }
    }else if(tokens.size() == 8){
        if(!validVar(tokens[1])) printError(ERRO_LEXICO_MSG, lc);
        if(tokens[2] != "+") printError(ERRO_SINTATICO_MSG, lc);
        if(!validVar(tokens[3].substr(0, tokens[3].size()-1))) printError(ERRO_LEXICO_MSG, lc);
        if(tokens[3].back() != ',') printError(ERRO_SINTATICO_MSG, lc);
        if(!validVar(tokens[4])) printError(ERRO_LEXICO_MSG, lc);
        if(tokens[5] != "+") printError(ERRO_SINTATICO_MSG, lc);
        if(!validVar(tokens[6])) printError(ERRO_LEXICO_MSG, lc);
    }else if(tokens.size()  == 4){
        if(!validVar(tokens[1].substr(0, tokens[1].size()-1))) printError(ERRO_LEXICO_MSG, lc);
        if(tokens[1].back() != ',') printError(ERRO_SINTATICO_MSG, lc);
        if(!validVar(tokens[2])) printError(ERRO_LEXICO_MSG, lc);
    }else{
        printError(ERRO_SINTATICO_MSG, lc);
    }
}