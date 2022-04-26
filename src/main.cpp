#include <iostream>
#include "lexem.h"
#include <string.h>

#pragma region Enums

#pragma endregion

#pragma region FunctionsDeclaration

extern int yylex();
extern char *yytext;
extern int yyleng;
extern FILE *yyin;

void getNextToken(bool skipEndl);

bool program(bool bGetNextToken);
bool includesPart(bool bGetNextToken);
bool mainPart(bool bGetNextToken);
bool include(bool bGetNextToken);
bool mainBody(bool bGetNextToken);
bool term(bool bGetNextToken);
bool text(bool bGetNextToken);
bool createVar(bool bGetNextToken);
bool setVar(bool bGetNextToken);
bool iocmd(bool bGetNextToken);
bool logBlock(bool bGetNextToken);
bool expr(bool bGetNextToken);
bool subExpr(bool bGetNextToken);
bool rSubExpr(bool bGetNextToken);
bool rExpr(bool bGetNextToken);
bool logExpr(bool bGetNextToken);
bool rLogExpr(bool bGetNextToken);
bool ifBody(bool bGetNextToken);

#pragma endregion

using namespace std;

string sourceCodePath;

enum Token currentLexem = ENDF;

int lineNumber = 1;

bool debug = false;

//here need error if it was found

int main(int argc, char *argv[]){

    if(argc < 1){
        cout << "Please use parser like this: parser <path to source code>" << endl;
        return -1;
    }

    yyin = fopen(argv[1], "r");

    if(argc > 2)
        if(strcmp(argv[2], "-debug") == 0)
            debug = true;

    if(!program(true)){
        printf("ERROR! Unexpected character at %d line:\nCode: %d\nError value: %s", lineNumber, currentLexem, yytext);
        return -1;
    }

    cout << "Source code correct!" << endl;

    return 0;
}

void getNextToken(bool skipEndl){
    enum Token token;

    do{
        token = (enum Token)yylex();
        if(token == ENDL)
            lineNumber++;
    }while(token < ENDF || (token == ENDL && skipEndl));

    currentLexem = token;

    if(debug)
        printf("Lexem: >%s<\n", yytext);
}

bool program(bool bGetNextToken){
    if(includesPart(bGetNextToken) && mainPart(false))
        return true;

    return false;
}

bool includesPart(bool bGetNextToken){
    if(include(bGetNextToken)){
        includesPart(true);
        return true;
    }
    else
        return false;
}

bool mainPart(bool bGetNextToken){
    if(bGetNextToken)
        getNextToken(true);

    if(currentLexem == MAIN_SIG){
        getNextToken(true);
        if(currentLexem == FLBRACK){
            getNextToken(true);
            if(mainBody(false)){
                getNextToken(true);
                if(currentLexem == FRBRACK)
                    return true;
            }
        }
    }

    return false;
}

bool include(bool bGetNextToken){
    if(bGetNextToken)
        getNextToken(false);

    if(currentLexem == INCLUDE_SIG){
        getNextToken(false);
        if(currentLexem == LOG_LEFT){
            getNextToken(false);
            if(currentLexem == ID){
                getNextToken(false);
                if(currentLexem == DOT_H){
                    getNextToken(false);
                    if(currentLexem == LOG_RIGHT){
                        getNextToken(false);
                        if(currentLexem == ENDL)
                            return true;
                    }
                }
            }
        }
    }

    return false;
}

bool mainBody(bool bGetNextToken){
    text(bGetNextToken);

    if(currentLexem == RETURN){
        getNextToken(false);
        if(currentLexem == NUM){
            getNextToken(false);
            if(currentLexem == DOT_COMMA){
                return true;
            }
        }
    }

    return false;
}

bool term(bool bGetNextToken){
    if(bGetNextToken)
        getNextToken(false);
    
    switch(currentLexem){
        case ID:
        case NUM:
            return true;
        default:
            return false;
    }
}

bool text(bool bGetNextToken){
    if(bGetNextToken)
        getNextToken(true);

    bool result = false;

    switch(currentLexem){
        case TYPE:
            result = createVar(false);
        break;
        case ID:
            result = setVar(false);
        break;
        case SCANF:
        case PRINTF:
            result = iocmd(false);
        break;
        case IF:
            result = logBlock(false);
        break;
    }

    if(result){
        text(true);
        return true;
    }else
        return false;
}

bool createVar(bool bGetNextToken){
    if(bGetNextToken)
        getNextToken(false);

    if(currentLexem == TYPE){
        getNextToken(false);
        if(currentLexem == ID){
            getNextToken(false);
            if(currentLexem == DOT_COMMA){
                return true;
            }else if(currentLexem == EQUALS){
                getNextToken(false);
                if(expr(false)){
                    if(currentLexem == DOT_COMMA){
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool setVar(bool bGetNextToken){
    if(bGetNextToken)
        getNextToken(false);

    if(currentLexem == ID){
        getNextToken(false);
        if(currentLexem == EQUALS){
            getNextToken(false);
            if(expr(false)){
                if(currentLexem == DOT_COMMA){
                    return true;
                }
            }
        }
    }

    return false;
}

bool iocmd(bool bGetNextToken){
    if(bGetNextToken)
        getNextToken(false);

    if(currentLexem == SCANF || currentLexem == PRINTF){
        getNextToken(false);
        if(currentLexem == CLBRACK){
            getNextToken(false);
            if(currentLexem == STR){
                getNextToken(false);
                if(currentLexem == COMMA){
                    getNextToken(false);
                    if(currentLexem == VAR_ADDRESS){
                        getNextToken(false);
                    }
                    if(term(false)){
                        getNextToken(false);
                        if(currentLexem == CRBRACK){
                            getNextToken(false);
                            if(currentLexem == DOT_COMMA){
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool logBlock(bool bGetNextToken){
    if(bGetNextToken)
        getNextToken(false);

    if(currentLexem == IF){
        getNextToken(false);
        if(currentLexem == CLBRACK){
            getNextToken(false);
            if(logExpr(false)){
                // getNextToken(false);// danger
                if(currentLexem == CRBRACK){
                    getNextToken(true);
                    if(ifBody(false)){
                        getNextToken(true);
                        if(currentLexem == ELSE){
                            getNextToken(true);
                            if(ifBody(false))
                                return true;
                        }
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool expr(bool bGetNextToken){
    if(subExpr(bGetNextToken)){
        if(rExpr(bGetNextToken)){
            return true;
        }
    }

    return false;
}

bool subExpr(bool bGetNextToken){
    if(term(bGetNextToken)){
        if(rSubExpr(true)){
            return true;
        }
    }

    return false;
}

bool rSubExpr(bool bGetNextToken){
    if(bGetNextToken)
        getNextToken(false);

    bool result = false;

    switch(currentLexem){
        case MUL:
        case DIV:
        case RDIV:
            result = term(bGetNextToken);
        break;
    }

    // need debug here because idk how to get EPSILON
    // it is return always error

    if(result){
        rSubExpr(true);
        return true;
    }else{
        return false;
    }
}

bool rExpr(bool bGetNextToken){
    if(bGetNextToken)
        getNextToken(false);

    bool result = false;

    switch(currentLexem){
        case PLUS:
        case MINUS:
            result = subExpr(bGetNextToken);
        break;
    }

    //here also as in rSubExpr

    if(result){
        rExpr(true);
        return true;
    }else{
        return false;
    }
}

bool logExpr(bool bGetNextToken){
    if(term(bGetNextToken)){
        if(rLogExpr(true)){
            return true;
        }
    }

    return false;
}

bool rLogExpr(bool bGetNextToken){
    if(bGetNextToken)
        getNextToken(false);

    bool result = false;

    switch(currentLexem){
        case LOG_LEFT:
        case LOG_RIGHT:
        case LOG_E_LEFT:
        case LOG_E_RIGHT:
        case LOG_EQUAL:
        case LOG_NOT_EQUAL:
            result = term(true);
    }

    if(result){
        rLogExpr(true);
        return true;
    }else   
        return false;
}

bool ifBody(bool bGetNextToken){
    if(bGetNextToken)
        getNextToken(false);

    switch(currentLexem){
        case TYPE:
            return createVar(false);
        case ID:
            return setVar(false);
        case SCANF:
        case PRINTF:
            return iocmd(false);
    }

    return false;
}