#include <iostream>
#include "lexem.h"
#include <string.h>
#include "structures/btree.h"

#pragma region Enums

typedef enum {
    PROG,
    INC_PART,
    MAIN,
    INC,
    MAIN_BODY,
    TERM,
    TEXT,
    CVAR,
    SVAR,
    IO,
    LOG,
    EXPR,
    REXPR,
    LOG_EXPR,
    RLOG_EXPR,
    LOG_BODY
}Part;

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

btree<Part>* tree;

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
        printf("ERROR! Unexpected character at %d line:\nCode: %d\nError value: %s\n", lineNumber, currentLexem, yytext);
        tree->printTree();
        
        return -1;
    }

    tree->printTree();

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
        printf("Lexem: (%s) - %d\n", yytext, token);
}

bool program(bool bGetNextToken){

    tree = new btree<Part>(PROG);
    entry<Part>* cIterator = tree->getIterator();

    tree->addToken(cIterator, INC_PART);
    bool incResult = includesPart(bGetNextToken);
    tree->addToken(cIterator, MAIN);
    bool mainResult = mainPart(false);

    if(incResult && mainResult){
        cIterator->setStatus(true);
        return true;
    }

    return false;
}

bool includesPart(bool bGetNextToken){
    entry<Part>* cIterator = tree->getIterator();

    tree->addToken(cIterator, INC);
    if(include(bGetNextToken)){
        tree->addToken(cIterator, INC_PART);
        includesPart(true);

        cIterator->setStatus(true);
        return true;
    }
    else
        return false;
}

bool mainPart(bool bGetNextToken){
    entry<Part>* cIterator = tree->getIterator();

    if(bGetNextToken)
        getNextToken(true);

    if(currentLexem == MAIN_SIG){
        getNextToken(true);
        if(currentLexem == FLBRACK){
            getNextToken(true);
            tree->addToken(cIterator, MAIN_BODY);
            if(mainBody(false)){
                getNextToken(true);
                if(currentLexem == FRBRACK){
                    cIterator->setStatus(true);   
                    return true;
                }
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
                        if(currentLexem == ENDL){
                            tree->getIterator()->setStatus(true);
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool mainBody(bool bGetNextToken){
    entry<Part>* cIterator = tree->getIterator();

    tree->addToken(cIterator, TEXT);
    text(bGetNextToken);

    if(currentLexem == RETURN){
        getNextToken(false);
        if(currentLexem == NUM){
            getNextToken(false);
            if(currentLexem == DOT_COMMA){
                cIterator->setStatus(true);
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
            tree->getIterator()->setStatus(true);
            return true;
        default:
            return false;
    }
}

bool text(bool bGetNextToken){
    entry<Part>* cIterator = tree->getIterator();

    if(bGetNextToken)
        getNextToken(true);

    bool result = false;

    switch(currentLexem){
        case TYPE:
            tree->addToken(cIterator, CVAR);
            result = createVar(false);
        break;
        case ID:
            tree->addToken(cIterator, SVAR);
            result = setVar(false);
        break;
        case SCANF:
        case PRINTF:
            tree->addToken(cIterator, IO);
            result = iocmd(false);
        break;
        case IF:
            tree->addToken(cIterator, LOG);
            result = logBlock(false);
        break;
    }

    if(result){
        tree->addToken(cIterator, TEXT);
        text(true);
        cIterator->setStatus(true);
        return true;
    }else
        return false;
}

bool createVar(bool bGetNextToken){
    entry<Part>* cIterator = tree->getIterator();

    if(bGetNextToken)
        getNextToken(false);

    if(currentLexem == TYPE){
        getNextToken(false);
        if(currentLexem == ID){
            getNextToken(false);
            if(currentLexem == DOT_COMMA){
                cIterator->setStatus(true);
                return true;
            }else if(currentLexem == EQUALS){
                getNextToken(false);
                tree->addToken(cIterator, EXPR);
                if(expr(false)){
                    if(currentLexem == DOT_COMMA){
                        cIterator->setStatus(true);
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool setVar(bool bGetNextToken){
    entry<Part>* cIterator = tree->getIterator();

    if(bGetNextToken)
        getNextToken(false);

    if(currentLexem == ID){
        getNextToken(false);
        if(currentLexem == EQUALS){
            getNextToken(false);
            tree->addToken(cIterator, EXPR);
            if(expr(false)){
                if(currentLexem == DOT_COMMA){
                    cIterator->setStatus(true);
                    return true;
                }
            }
        }
    }

    return false;
}

bool iocmd(bool bGetNextToken){
    entry<Part>* cIterator = tree->getIterator();

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

                    tree->addToken(cIterator, TERM);

                    if(term(false)){
                        getNextToken(false);
                        if(currentLexem == CRBRACK){
                            getNextToken(false);
                            if(currentLexem == DOT_COMMA){
                                cIterator->setStatus(true);
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
    entry<Part>* cIterator = tree->getIterator();

    if(bGetNextToken)
        getNextToken(false);

    if(currentLexem == IF){
        getNextToken(false);
        if(currentLexem == CLBRACK){
            getNextToken(false);

            tree->addToken(cIterator, LOG_EXPR);

            if(logExpr(false)){
                // getNextToken(false);// danger
                if(currentLexem == CRBRACK){
                    getNextToken(true);

                    tree->addToken(cIterator, LOG_BODY);

                    if(ifBody(false)){
                        getNextToken(true);
                        if(currentLexem == ELSE){
                            getNextToken(true);

                            tree->addToken(cIterator, LOG_BODY);

                            if(ifBody(false)){
                                cIterator->setStatus(true);
                                return true;
                            }
                        }
                        cIterator->setStatus(true);
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool expr(bool bGetNextToken){
    entry<Part>* cIterator = tree->getIterator();

    tree->addToken(cIterator, TERM);
    if(term(bGetNextToken)){
        tree->addToken(cIterator, REXPR);
        if(rExpr(true)){
            cIterator->setStatus(true);
            return true;
        }
    }

    return false;
}

bool rExpr(bool bGetNextToken){
    entry<Part>* cIterator = tree->getIterator();

    if(bGetNextToken)
        getNextToken(false);

    bool result = false;

    switch(currentLexem){
        case PLUS:
        case MINUS:
        case MUL:
        case DIV:
        case RDIV:
            tree->addToken(cIterator, TERM);
            result = term(true);
        break;
        case DOT_COMMA:
            cIterator->setStatus(true);
            return true;
        break;
    }

    //here also as in rSubExpr

    if(result){
        tree->addToken(cIterator, REXPR);
        rExpr(true);
        cIterator->setStatus(true);
        return true;
    }else{
        return false;
    }
}

bool logExpr(bool bGetNextToken){
    entry<Part>* cIterator = tree->getIterator();

    tree->addToken(cIterator, TERM);

    if(term(bGetNextToken)){
        tree->addToken(cIterator, RLOG_EXPR);

        if(rLogExpr(true)){
            cIterator->setStatus(true);
            return true;
        }
    }

    return false;
}

bool rLogExpr(bool bGetNextToken){
    entry<Part>* cIterator = tree->getIterator();

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
            tree->addToken(cIterator, TERM);
            result = term(true);
    }

    if(result){
        tree->addToken(cIterator, RLOG_EXPR);
        rLogExpr(true);
        cIterator->setStatus(true);
        return true;
    }else   
        return false;
}

bool ifBody(bool bGetNextToken){
    entry<Part>* cIterator = tree->getIterator();

    if(bGetNextToken)
        getNextToken(false);

    cIterator->setStatus(true);

    switch(currentLexem){
        case TYPE:
            tree->addToken(cIterator, CVAR);
            return createVar(false);
        case ID:
            tree->addToken(cIterator, SVAR);
            return setVar(false);
        case SCANF:
        case PRINTF:
            tree->addToken(cIterator, IO);
            return iocmd(false);
    }

    return false;
}