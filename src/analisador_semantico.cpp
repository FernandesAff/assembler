#include "analisador_semantico.hpp"

void dirAnalyzerSem(TD dir, vector<string> tokens, int lc){
    ofstream myfile;

    myfile.open (objName, ios::app);
    if(upCase(dir.nome) == "SPACE"){
        if(tokens.size() == 2){
            myfile << "0 ";
        }else if(tokens.size() == 3){
            myfile << tokens[1] << " ";
        }
    }else if(upCase(dir.nome) == "CONST"){
        if(tokens.size() == 3){
            myfile << tokens[1] << " ";
        }
    }

    myfile.close();
}

bool textAnalyzer(vector<string> token){
    return (upCase(token[0]).compare("SECTION") && upCase(token[1]).compare("TEXT") == 0 ? true : false);
}

void instAnalyzer(TI inst, vector<string> tokens, int lc){
    ofstream myfile;

    myfile.open (objName, ios::app);
    myfile << inst.codigo << " ";

    if(upCase(inst.nome) == "COPY"){
        vector<int> valores;
        valores = analyzeCopy(tokens, lc);

        myfile << valores[0] << " " << valores[1] << " ";
    }else if(upCase(inst.nome) == "STOP"){
        if(tokens.size() != 2) printError(ERRO_SINTATICO_MSG, lc);
    }else if(upCase(inst.nome) == "ADD" || upCase(inst.nome) == "SUB" || upCase(inst.nome) == "MULT" 
            || upCase(inst.nome) == "DIV" || upCase(inst.nome) == "LOAD" || upCase(inst.nome) == "OUTPUT"){
        int valor;
        valor = analyzeAccOps(tokens, inst, lc);

        myfile << valor << " ";
    }else if(upCase(inst.nome) == "JMP" || upCase(inst.nome) == "JMPN" || upCase(inst.nome) == "JMPP" 
            || upCase(inst.nome) == "JMPZ"){
        int valor;
        valor = analyzeJmpOps(tokens, inst, lc);
        myfile << valor << " ";
    }else if(upCase(inst.nome) == "STORE" || upCase(inst.nome) == "INPUT"){
        int valor;
        valor = analyzeStoreOps(tokens, inst, lc);
        myfile << valor << " ";
    }

    myfile.close();
}

int analyzeExpression(string token1, string token2, string token3, int lc){
    if(!validVar(token1)) printError(ERRO_LEXICO_MSG, lc);
    if(token2 != "+") printError(ERRO_SINTATICO_MSG, lc);
    
    if(!varDeclared(token1)) {
        printError(ERRO_SEMANTICO_MSG, lc);
    }else{
        TS simbolo;
        inList(token1, tabSimbolos, simbolo);

        if(simbolo.cte){
            printError(ERRO_SEMANTICO_MSG, lc);
        }else if(isNumber(token3)) {
            if(stoi(token3) >= simbolo.tam){
                printError(ERRO_SEMANTICO_MSG, lc);
            }else{
                return simbolo.valor + stoi(token3);
            }
        }else{
            printError(ERRO_LEXICO_MSG, lc);
        }
    }
    return -1;
}

vector<int> analyzeCopy(vector<string> tokens, int lc){
    vector<int> params;
    int param1 = -1;
    int param2 = -1;
    if(tokens.size() == 6){
        if(tokens[2] == "+"){
            param1 = analyzeExpression(tokens[1], tokens[2], tokens[3].substr(0, tokens[3].size()-1), lc);
            if(tokens[3].back() != ',') printError(ERRO_SINTATICO_MSG, lc);
            if(!validVar(tokens[4])) printError(ERRO_LEXICO_MSG, lc);
            if(!varDeclared(tokens[4])) printError(ERRO_SEMANTICO_MSG, lc);
            else{
                TS simbolo;
                inList(tokens[1].substr(0, tokens[1].size()-1), tabSimbolos, simbolo);
                param2 = simbolo.valor;
            }
        }else if(tokens[3] == "+"){
            if(!validVar(tokens[1].substr(0, tokens[1].size()-1))) printError(ERRO_LEXICO_MSG, lc);
            if(!varDeclared(tokens[1].substr(0, tokens[1].size()-1))) printError(ERRO_SEMANTICO_MSG, lc);
            else{
                TS simbolo;
                inList(tokens[1].substr(0, tokens[1].size()-1), tabSimbolos, simbolo);
                if(simbolo.cte) printError(ERRO_SEMANTICO_MSG, lc);
                else param1 = simbolo.valor;
            }
            if(tokens[1].back() != ',') printError(ERRO_SINTATICO_MSG, lc);
            param2 = analyzeExpression(tokens[2], tokens[3], tokens[4], lc);
        }else{
            printError(ERRO_SINTATICO_MSG, lc);
        }
    }else if(tokens.size() == 8){
        param1 = analyzeExpression(tokens[1], tokens[2], tokens[3].substr(0, tokens[3].size()-1), lc);
        if(tokens[3].back() != ',') printError(ERRO_SINTATICO_MSG, lc);
        param2 = analyzeExpression(tokens[4], tokens[5], tokens[6], lc);
    }else if(tokens.size()  == 4){
        if(!validVar(tokens[1].substr(0, tokens[1].size()-1))) printError(ERRO_LEXICO_MSG, lc);
        if(!varDeclared(tokens[1].substr(0, tokens[1].size()-1))) printError(ERRO_SEMANTICO_MSG, lc);
        else{
            TS simbolo;
            inList(tokens[1].substr(0, tokens[1].size()-1), tabSimbolos, simbolo);
            if(simbolo.cte) printError(ERRO_SEMANTICO_MSG, lc);
            else param1 = simbolo.valor;
        }
        if(tokens[1].back() != ',') printError(ERRO_SINTATICO_MSG, lc);
        if(!validVar(tokens[2])) printError(ERRO_LEXICO_MSG, lc);
        if(!varDeclared(tokens[2])) printError(ERRO_SEMANTICO_MSG, lc);
        else{
            TS simbolo;
            inList(tokens[2], tabSimbolos, simbolo);
            param2 = simbolo.valor;
        }
    }else{
        printError(ERRO_SINTATICO_MSG, lc);
    }

    params.push_back(param1);
    params.push_back(param2);

    return params;
}

int analyzeAccOps(vector<string> tokens, TI inst, int lc){
    int param = -1;
    if(tokens.size() - 4 == inst.operandos){
        param = analyzeExpression(tokens[1], tokens[2], tokens[3], lc);
    }else if(tokens.size() - 2  == inst.operandos){
        if(!validVar(tokens[1])) printError(ERRO_LEXICO_MSG, lc);
        if(!varDeclared(tokens[1])) printError(ERRO_SEMANTICO_MSG, lc);
        else{
            TS simbolo;
            inList(tokens[1], tabSimbolos, simbolo);
            if(upCase(inst.nome) == "DIV" && simbolo.cte && simbolo.valorCte == "0"){
                printError(ERRO_SEMANTICO_MSG, lc);
            }else{
                param = simbolo.valor;
            }
        }
    }else{
        printError(ERRO_SINTATICO_MSG, lc);
    }
    return param;
}

int analyzeJmpOps(vector<string> tokens, TI inst, int lc){
    int param = -1;
    if(tokens.size() - 2  == inst.operandos){
        if(!validVar(tokens[1])) printError(ERRO_LEXICO_MSG, lc);
        if(!labelDeclared(tokens[1])) printError(ERRO_SEMANTICO_MSG, lc);
        else{
            TS simbolo;
            inList(tokens[1], tabSimbolos, simbolo);
            if(simbolo.valor >= dado){
                printError(ERRO_SEMANTICO_MSG, lc);
            }else{
                param = simbolo.valor;
            }
        }
    }else{
        printError(ERRO_SINTATICO_MSG, lc);
    }
    return param;
}

int analyzeStoreOps(vector<string> tokens, TI inst, int lc){
    int param = -1;
    if(tokens.size() - 4 == inst.operandos){
        param = analyzeExpression(tokens[1], tokens[2], tokens[3], lc);
    }else if(tokens.size() - 2  == inst.operandos){
        if(!validVar(tokens[1])) printError(ERRO_LEXICO_MSG, lc);
        if(!varDeclared(tokens[1])) printError(ERRO_SEMANTICO_MSG, lc);
        else{
            TS simbolo;
            inList(tokens[1], tabSimbolos, simbolo);
            if(simbolo.cte) printError(ERRO_SEMANTICO_MSG, lc);
            else{
                param = simbolo.valor;
            }
        }
    }else{
        printError(ERRO_SINTATICO_MSG, lc);
    }
    return param;
}

bool varDeclared(string token){
    return inList(token, tabSimbolos);
}

bool sectionText(TS simbolo){
    if(dado != -1 && simbolo.valor < dado){
        return true;
    }else if(dado != -1 && simbolo.valor >= dado){
        return false;
    }else{
        return true;
    }
}

bool labelDeclared(string token){
    TS simbolo;
    bool declared;

    declared = inList(token, tabSimbolos, simbolo);
    declared = declared && simbolo.isLabel;

    return declared;
}