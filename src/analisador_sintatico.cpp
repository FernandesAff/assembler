#include "analisador_sintatico.hpp"

void printError(string msgErro, int line){
    cout << RED << "Linha " << line << ":" << msgErro << endl;
}

bool labelAnalyzer(string label, int lc, int pc, int* labelCounter){
    if (!validLabel(label)){
        printError(ERRO_LEXICO_MSG, lc);
        return false;
    } else if(inList(label, tabSimbolos)){
        printError(ERRO_SEMANTICO_MSG, lc); //verificar se esse é o erro adequado
        return false;
    } else if(sameLineLabel(*labelCounter)){
        printError(ERRO_SINTATICO_MSG, lc);
        *labelCounter++;
        return false;
    } else{
        tabSimbolos.push_back(novoSimbolo(label, pc));
        return true;
    }
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