#include "analisador_sintatico.hpp"

void labelAnalyzer(string label, int lc, int pc, int* labelCounter){
    if (!validLabel(label)){
        printError(ERRO_LEXICO_MSG, lc);
    } else if(inList(label.substr(0, label.size()-1), tabSimbolos)){
        printError(ERRO_SEMANTICO_MSG, lc); //verificar se esse é o erro adequado
    } else if(sameLineLabel(*labelCounter)){
        printError(ERRO_SINTATICO_MSG, lc);
    } else{
        tabSimbolos.push_back(novoSimbolo(label.substr(0, label.size()-1), pc, false, 1, "", true));
    }
    labelCounter++;
}

bool sameLineLabel(int labelCounter){
    return (labelCounter > 0 ?  true : false);
}

int dirAnalyzer(TD dir, vector<string> tokens, int lc, int *text, int *data){
    int increment = 0;
    if(upCase(dir.nome) == "SECTION"){
        if(tokens.size() == 3){
            if(upCase(tokens[1]) == "TEXT"){
                if(*text != -1) printError(ERRO_SEMANTICO_MSG, lc);
                else{
                    *text = 0;
                }
            }else if(upCase(tokens[1]) == "DATA"){
                if(*data != -1) printError(ERRO_SEMANTICO_MSG, lc);
                else{
                    *data = 0;
                }
            }else{
                printError(ERRO_SINTATICO_MSG, lc);
            }
        }else {
            printError(ERRO_SINTATICO_MSG, lc);
        }
    }else if(upCase(dir.nome) == "SPACE"){
        if(tokens.size() == 2){
            increment++;
            tabSimbolos.back().tam = 1;
            tabSimbolos.back().isLabel = false;
        }else if(tokens.size() == 3){
            if(isNumber(tokens[1])){
                increment += stoi(tokens[1]);
                tabSimbolos.back().tam = stoi(tokens[1]);
                tabSimbolos.back().isLabel = false;
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
                tabSimbolos.back().cte = true;
                tabSimbolos.back().valorCte = tokens[1];
                tabSimbolos.back().isLabel = false;
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