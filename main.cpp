#include <iostream>

#pragma region Enums

enum Token{
    ENDF = 256,
    ENDL,
    MAIN_SIG,
    FLBRACK,
    FRBRACK,
    CLBRACK,
    CRBRACK,
    INCLUDE_SIG,
    ILBRACK,
    IRBRACK,
    DOT_H,
    ID,
    RETURN,
    NUM,
    STR,
    DOT_COMMA,
    COMMA,
    TYPE, 
    EQUALS,
    SCANF,
    PRINTF,
    IF,
    ELSE,


};

#pragma endregion

#pragma region FunctionsDeclaration

extern int yylex();
extern char *yytext;
extern int yyleng;

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
bool rExpr(bool bGetNextToken);
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

    if(!program(true)){
        //cout error
        return -1;
    }

    cout << "Source code correct!" << endl;

    return 0;
}

void getNextToken(bool skipEndl){
    int token;

    do{
        token = yylex();
    }while(token < ENDF || (token == ENDL && skipEndl));

    currentLexem = (enum Token)token;
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
        if(currentLexem == ILBRACK){
            getNextToken(false);
            if(currentLexem == ID){
                getNextToken(false);
                if(currentLexem == DOT_H){
                    getNextToken(false);
                    if(currentLexem == IRBRACK){
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
    if(text(true)){
        getNextToken(true);
        if(currentLexem == RETURN){
            getNextToken(false);
            if(currentLexem == NUM){
                getNextToken(false);
                if(currentLexem == DOT_COMMA){
                    return true;
                }
            }
        }
    }

    return true;
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
        getNextToken(false);

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

    if(currentLexem == SCANF){
        getNextToken(false);
        if(currentLexem == CLBRACK){
            getNextToken(false);
            if(currentLexem == STR){
                getNextToken(false);
                if(currentLexem == COMMA){
                    getNextToken(false);
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
                getNextToken(false);// danger
                if(currentLexem == CRBRACK){
                    getNextToken(false);
                    if(ifBody(false)){
                        getNextToken(false);
                        if(currentLexem == ELSE){
                            getNextToken(false);
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