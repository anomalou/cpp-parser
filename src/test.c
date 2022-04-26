#include "lexem.h"
#include <stdio.h>

extern int yylex();
extern char *yytext;

int main(){
    int lexem_class;
    while (1) {
        lexem_class = yylex();
        switch (lexem_class) {
            case ENDF:
                printf("%s : %s", yytext, "ENDF\n");
                return 0;
            case ENDL:
                printf("%s : %s", yytext, "ENDL\n");
                break;
            case MAIN_SIG:
                printf("%s : %s", yytext, "MAIN_SIG\n");
                break;
            case FLBRACK:
                printf("%s : %s", yytext, "FLBRACK\n");
                break;
            case FRBRACK:
                printf("%s : %s", yytext, "FRBRACK\n");
                break;
            case CLBRACK:
                printf("%s : %s", yytext, "CLBRACK\n");
                break;
            case CRBRACK:
                printf("%s : %s", yytext, "CRBRACK\n");
                break;
            case INCLUDE_SIG:
                printf("%s : %s", yytext, "INCLUDE_SIG\n");
                break;
            case ILBRACK:
                printf("%s : %s", yytext, "ILBRACK\n");
                break;
            case IRBRACK:
                printf("%s : %s", yytext, "IRBRACK\n");
                break;
            case DOT_H:
                printf("%s : %s", yytext, "DOT_H\n");
                break;
            case ID:
                printf("%s : %s", yytext, "ID\n");
                break;
            case RETURN:
                printf("%s : %s", yytext, "RETURN\n");
                break;
            case NUM:
                printf("%s : %s", yytext, "NUM\n");
                break;
            case STR:
                printf("%s : %s", yytext, "STR\n");
                break;
            case DOT_COMMA:
                printf("%s : %s", yytext, "DOT_COMMA\n");
                break;
            case COMMA:
                printf("%s : %s", yytext, "COMMA\n");
                break;
            case TYPE:
                printf("%s : %s", yytext, "TYPE\n");
                break;
            case EQUALS:
                printf("%s : %s", yytext, "EQUALS\n");
                break;
            case SCANF:
                printf("%s : %s", yytext, "SCANF\n");
                break;
            case PRINTF:
                printf("%s : %s", yytext, "PRINTF\n");
                break;
            case IF:
                printf("%s : %s", yytext, "IF\n");
                break;
            case ELSE:
                printf("%s : %s", yytext, "ELSE\n");
                break;
            case MUL:
                printf("%s : %s", yytext, "MUL\n");
                break;
            case DIV:
                printf("%s : %s", yytext, "DIV\n");
                break;
            case RDIV:
                printf("%s : %s", yytext, "RDIV\n");
                break;
            case PLUS:
                printf("%s : %s", yytext, "PLUS\n");
                break;
            case MINUS:
                printf("%s : %s", yytext, "MINUS\n");
                break;
            case LOG_LEFT:
                printf("%s : %s", yytext, "LOG_LEFT\n");
                break;
            case LOG_RIGHT:
                printf("%s : %s", yytext, "LOG_RIGHT\n");
                break;
            case LOG_E_LEFT:
                printf("%s : %s", yytext, "LOG_E_LEFT\n");
                break;
            case LOG_E_RIGHT:
                printf("%s : %s", yytext, "LOG_E_RIGHT\n");
                break;
            case LOG_EQUAL:
                printf("%s : %s", yytext, "LOG_EQUAL\n");
                break;
            case LOG_NOT_EQUAL:
                printf("%s : %s", yytext, "LOG_NOT_EQUAL\n");
                break;
        }
    }

    return 0;
}