#include <iostream>

#pragma region Enums

enum Token{
    ENDF = 256,
    ENDL,
    MAIN_SIG,
    FLBRACK,
    FRBRACK,
    INCLUDE_SIG,
    ILBRACK,
    IRBRACK,
    DOT_H,
    ID,
    RETURN,
    NUM,
    DOT_COMMA,

};

#pragma endregion

#pragma region FunctionsDeclaration

extern int yylex();
extern char *yytext;
extern int yyleng;

void getNextToken();

bool program(bool bGetNextToken);
bool includesPart(bool bGetNextToken);
bool mainPart(bool bGetNextToken);
bool include(bool bGetNextToken);
bool mainBody(bool bGetNextToken);
bool term(bool bGetNextToken);
bool text(bool bGetNextToken);
bool createVar(bool bGetNextToken);
bool setVar(bool bGetNextToken);
bool callFunc(bool bGetNextToken);
bool logBlock(bool bGetNextToken);
bool expr(bool bGetNextToken);
bool rExpr(bool bGetNextToken);
bool params(bool bGetNextToken);
bool param(bool bGetNextToken);
bool logExpr(bool bGetNextToken);
bool rLogExpr(bool bGetNextToken);
bool program(bool bGetNextToken);
bool ifBody(bool bGetNextToken);
bool sign(bool bGetNextToken);
bool logSign(bool bGetNextToken);

#pragma endregion

using namespace std;

string sourceCodePath;

enum Token currentLexem = ENDF;

//here need error if it was found

int main(int argc, char *argv[]){

    if(argc < 1){
        cout << "Please use parser like this: parser <path to source code>" << endl;
        return -1;
    }

    //read source code here

    if(!program){
        //cout error
        return -1;
    }

    cout << "Source code correct!" << endl;

    return 0;
}

void getNextToken(){
    int token;

    do{
        token = yylex();
    }while(token < ENDF);

    currentLexem = (enum Token)token;
}

bool program(bool bGetNextToken){
    if(!includesPart(bGetNextToken) || !mainPart(false))
        return false;

    return true;
}

bool includesPart(bool bGetNextToken){
    bool result = include(bGetNextToken);
    
    if(!result)
        return false;
    else
        return result || includesPart(bGetNextToken);
}

bool mainPart(bool bGetNextToken){
    if(bGetNextToken)
        getNextToken();
    
    switch(currentLexem){
        case MAIN_SIG:
            return mainPart(true);
        case FLBRACK:
            return mainBody(true) && mainPart(false);
        case FRBRACK:
            return true;
        case ENDL:
            return mainPart(true);
        default:
            return false;
    }
}

bool include(bool bGetNextToken){
    if(bGetNextToken)
        getNextToken();

    switch(currentLexem){
        case INCLUDE_SIG:
            return include(true);
        case ILBRACK:
            return include(true);
        case ID:
            return include(true);
        case DOT_H:
            return include(true);
        case IRBRACK:
            return include(true);
        case ENDL:
            return true;
        default:
            return false;
    }
}

bool mainBody(bool bGetNextToken){
    if(bGetNextToken)
        getNextToken();

    switch(currentLexem){
        case RETURN:
            return mainBody(true);
        case NUM:
            return mainBody(true);
        case DOT_COMMA:
            return true;
    }

    bool childResult = false;

    if(!(childResult = text(true)))
        return false;
    else
        return childResult && mainBody(false);
}

bool term(bool bGetNextToken){
    if(bGetNextToken)
        getNextToken();
    
    switch(currentLexem){
        case ID:
        case NUM:
            return true;
        default:
            return false;
    }
}

bool text(bool bGetNextToken){
    
}

bool createVar(bool bGetNextToken){

}

bool setVar(bool bGetNextToken){

}

bool callFunc(bool bGetNextToken){

}

bool logBlock(bool bGetNextToken){

}

bool expr(bool bGetNextToken){

}

bool rExpr(bool bGetNextToken){

}

bool params(bool bGetNextToken){

}

bool param(bool bGetNextToken){

}

bool logExpr(bool bGetNextToken){

}

bool rLogExpr(bool bGetNextToken){

}

bool program(bool bGetNextToken){

}

bool ifBody(bool bGetNextToken){

}

bool sign(bool bGetNextToken){

}

bool logSign(bool bGetNextToken){

}