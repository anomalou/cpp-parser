%{
    enum Lexem{
        ENDF = 256, 
        ENDL, // end of line
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
        MUL, 
        DIV, 
        RDIV, 
        PLUS, 
        MINUS, 
        LOG_LEFT, 
        LOG_RIGHT, 
        LOG_E_LEFT, 
        LOG_E_RIGHT, 
        LOG_EQUAL, 
        LOG_NOT_EQUAL
    };
%}

DIGIT [0-9]
CHAR [a-zA-Z]
SPACE \s
%%
int main() {return MAIN_SIG;}
#include {return INCLUDE_SIG;}
return {return RETURN;}
[int|float] {return TYPE;}
scanf {return SCANF;}
printf {return PRINTF;}
if {return IF;}
else {return ELSE;}
<<EOF>> {yyterminate(); return 0;} //todo https://stackoverflow.com/questions/22811320/flex-bison-not-terminating-on-eof
\n {return ENDL;} //todo
\{ {return FLBRACK;}
\} {return FRBRACK;}
\( {return CLBRACK;}
\) {return CRBRACK;}
\< {return ILBRACK;}
\> {return IRBRACK;}
.h {return DOT_H;}
{CHAR}({CHAR}|{DIGIT})* {return ID;}
{DIGIT}+ {return NUM;} //todo
\"*\" {return STR;}
; {return DOT_COMMA;}
, {return COMMA;}
\= {return EQUALS;}
\* {return MUL;}
\/ {return DIV;}
\% {return RDIV;}
\+ {return PLUS;}
\- {return MINUS;}
\< {return LOG_LEFT;}
\> {return LOG_RIGHT;}
\<\= {return LOG_E_LEFT;}
\>\= {return LOG_E_RIGHT;}
\=\= {return LOG_EQUAL;}
\!\= {return LOG_NOT_EQUAL;}
%%

int yywrap(void){
    return 1;
}