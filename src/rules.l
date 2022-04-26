%{
    #include "lexem.h"
%}

DIGIT [0-9]
CHAR [a-zA-Z]
<<<<<<< Updated upstream
SPACE " "*
STRING \".*\"
%%
{SPACE} {}
int{SPACE}main{SPACE}\(\) {return MAIN_SIG;}
#include {return INCLUDE_SIG;}
return {return RETURN;}
"int"|"float"|"void" {return TYPE;}
"scanf"\(\) {return SCANF;}
"printf" {return PRINTF;}
"if" {return IF;}
"else" {return ELSE;}
=======
SPACE \s+
STRING \"*\"
%%

{SPACE} {return SPACE;}
"int main()" {return MAIN_SIG;}
#include {return INCLUDE_SIG;}
return {return RETURN;}
"int"|"float" {return TYPE;}
scanf {return SCANF;}
printf {return PRINTF;}
if {return IF;}
else {return ELSE;}
>>>>>>> Stashed changes
<<EOF>> {return ENDF;} //todo https://stackoverflow.com/questions/22811320/flex-bison-not-terminating-on-eof
\n {return ENDL;} //todo &*
\{ {return FLBRACK;}
\} {return FRBRACK;}
\( {return CLBRACK;}
\) {return CRBRACK;}
.h {return DOT_H;}
{CHAR}({CHAR}|{DIGIT})* {return ID;}
{DIGIT}+.{DIGIT} {return NUM;}
{DIGIT}+ {return NUM;} //todo float?
\"({CHAR}|{DIGIT})*\" {return STR;}
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