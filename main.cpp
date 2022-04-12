#include <iostream>
#include <string>

using namespace std;

extern int yylex();
extern char *yytext;
extern int yyleng;

double number_value = 0;
string string_value = "";

int main(int argc, char *argv[]){
    int lex;

    while((lex = yylex()) != 256){
        printf("%d - %s\n", lex, yytext);
    }

    return 0;
}
