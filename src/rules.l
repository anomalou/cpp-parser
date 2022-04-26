%{
    #include "lexem.h"
%}

DIGIT [0-9]
CHAR [a-zA-Z]
SPACE \s+
STRING \".*\"
%%

main {return MAIN_SIG;}
#include {return INCLUDE_SIG;}
return {return RETURN;}
"int"|"float"|"void" {return TYPE;}
scanf\(\) {return SCANF;}
printf {return PRINTF;}
if {return IF;}
else {return ELSE;}
<<EOF>> {return ENDF;} //todo https://stackoverflow.com/questions/22811320/flex-bison-not-terminating-on-eof
\n {return ENDL;} //todo &*
\{ {return FLBRACK;}
\} {return FRBRACK;}
\( {return CLBRACK;}
\) {return CRBRACK;}
\< {return ILBRACK;}
\> {return IRBRACK;}
.h {return DOT_H;}
{CHAR}({CHAR}|{DIGIT})* {return ID;}
{DIGIT}+ {return NUM;} //todo float?
{STRING} {return STR;}
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