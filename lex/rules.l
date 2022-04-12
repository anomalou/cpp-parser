%{
    enum Lexem{
        END = 256,
        INT,
        FLOAT,
        NAME,
        SPACE,
        ENDL,
    };
%}

DIGIT [0-9]
CHAR [a-zA-Z]

%%

\s {return SPACE;}
[\0\n] {return END;}
; {return ENDL;}
{CHAR}({CHAR}|{DIGIT})* {return NAME;}
{DIGIT}+[.,]{DIGIT}+ {return FLOAT;}
{DIGIT}+ {return INT;}


%%

int yywrap(void){
    return 1;
}