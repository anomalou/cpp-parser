%{
    enum Lexem{
        END = 256,
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
        RP,
		INCLUDE,
		MAIN,
		IF, 
		ELSE,
		PRINTF,
		SCANF,
		RETURN
    };
%}

DIGIT [0-9]
CHAR [a-zA-Z]

%%
#include<{CHAR}+> {return INCLUDE;}
main {return MAIN;}
if {return IF;}
else {return ELSE;}
printf {return PRINTF;}
scanf {return SCANF;}
return {return RETURN;}

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