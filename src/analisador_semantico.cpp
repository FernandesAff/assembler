#include "analisador_semantico.hpp"

void instAnalyzerSem(TI inst, vector<string> tokens, int lc){

}

void dirAnalyzerSem(TD dir, vector<string> tokens, int lc){

}

bool textAnalyzer(vector<string> token){
    return (upCase(token[0]).compare("SECTION") && upCase(token[1]).compare("TEXT") == 0 ? true : false);
}