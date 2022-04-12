%{
    enum Lexem{
        INCLUDE = 256,
		MAIN,
		IF, 
		ELSE,
		PRINTF,
		SCANF,
		RETURN,
        INIT_INT,
        INIT_INT_E,
        END,
        INT,
        FLOAT,
        NAME,
        SPACE,
        ENDL,
		DOUBLE_QUOTE,
		PERCENT,
		COMMA,
        PLUS,
        MINUS,
        MULTIPLICATIOIN,
        DIVISION,
		LT,
		LE,
		GT,
		GE,
        LB,
        RB,
        LP,
        RP
    };
%}

DIGIT [0-9]
CHAR [a-zA-Z]
WHITESPACE [ \n\t\r]+ 

%%
#include<{CHAR}+> {return INCLUDE;}
main {return MAIN;}
if {return IF;}
else {return ELSE;}
printf {return PRINTF;}
scanf {return SCANF;}
return {return RETURN;}

int{WHITESPACE}{CHAR}({CHAR}|{DIGIT})* {return INIT_INT;}
int{WHITESPACE}{CHAR}({CHAR}|{DIGIT})*{WHITESPACE}={DIGIT}+ {return INIT_INT_E;}

[\0\n] {return END;}
; {return ENDL;}
{CHAR}({CHAR}|{DIGIT})* {return NAME;}
{DIGIT}+[.|,]{DIGIT}+ {return FLOAT;}
{DIGIT}+ {return INT;}
\" {return DOUBLE_QUOTE;}
\%{CHAR} {return PERCENT;}
, {return COMMA;}
\+ {return PLUS;} 
\- {return MINUS;} 
\* {return MULTIPLICATIOIN;} 
\/ {return DIVISION;} 
\< {return LT;} 
\<\= {return LE;} 
\> {return GT;} 
\>\= {return GE;} 
\{ {return LB;}
\} {return RB;}
\( {return LB;}
\) {return RB;}

%%

int yywrap(void){
    return 1;
}