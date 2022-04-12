#include <iostream>
#include <string>
#include <map>

using namespace std;

extern int yylex();
extern char *yytext;
extern int yyleng;

enum Token{
    INT,
    FLOAT,
    NAME,
    MUL,
    DIV,
    MOD,
    PLUS,
    MINUS,
    ASSIGN,
    EQUAL,
    NOTEQUAL,
    LOWER,
    UPPER,
    ELOWER,
    EUPPER,
    AND,
    OR,
    LRB,
    RRB,
    CEND,
    END
};

double number_value = 0;
string string_value = "";
map<string, double> table;

Token curr_token = CEND;

void error(const string text);

void beginTranslate();

double primExpr(bool getToken);
double foExpr(bool getToken);
double soExpr(bool getToken);

bool bprimExpr(bool getToken);
bool bfoExpr(bool getToken);

int main(int argc, char *argv[]){
    int lex;

    while((lex = yylex()) != 256){
        printf("%d - %s\n", lex, yytext);
    }

    return 0;
}

// Use it for error printing
void error(const string text){
    printf("[ERROR]: %s\n", text.c_str());
}

// Main point to start translation
void beginTranslate(){
    /*

    Here we have 3 situation^
    1) int x; or int x = 1;
        Same variants, that send us to primExpr
    2) int main() or another functions
        This situathion need new processor, like primExpr, so it handle function
        body and execute it.
    3) #include<someone.h>
        Includes should registrates by # char or by full signature (#include), than need new handler,
        that process inclusion.

    So at the end, we need 2 new fucntions-processors
    */
}

// Major expressions, like -num, num, name, (
double primExpr(bool getToken){
    if(getToken){
        printf("Here 1 got token, but i can do it right now\n");
        //get token here...
    }

    switch(curr_token){
        case INT:
        case FLOAT: {
            double v = number_value;
            printf("Here 1 got token, but i can do it right now\n");
            return v;
        }
        case NAME: {
            double &v = table[string_value];
            
            printf("Here 1 got token, but i can do it right now\n");

            return v;
        }
        case MINUS:
            return -primExpr(true);
        case LRB:{
            double e = soExpr(true);

            if(curr_token != RRB)
                error("sintax error! missing ')'");
                return 1;
        }
    }
}

// Expressions, like mul, div, mod, 
double foExpr(bool getToken){
    double left = primExpr(getToken);

    while(true){
        switch(curr_token){
            case MUL:
                left *= primExpr(true);
            break;
            case DIV: {
                if(double d = primExpr(true)){
                    left /= d;
                    break;
                }
                
                error("divide by 0");
                return 1;
            }
            case MOD: {
                if(double d = (int)left % (int)primExpr(true)){
                    left = d;
                    break;
                }

                error("divide by 0");
                return 1;
            }
            break;
            default:
                return left;
        }
    }
}

double soExpr(bool getToken){
    double left = foExpr(getToken);

    while(true){
        switch(curr_token){
            case PLUS:
                left += foExpr(true);
            break;
            case MINUS:
                left -= foExpr(true);
            break;
            default:
                return left;
        }
    }
}

bool bprimExpr(bool getToken){
    double left = soExpr(getToken);

    switch(curr_token){
        case EQUAL:
            return left == soExpr(true);
        case LOWER:
            return left < soExpr(true);
        case UPPER:
            return left > soExpr(true);
        case ELOWER:
            return left <= soExpr(true);
        case EUPPER:
            return left >= soExpr(true);
        default:
            return left != 0;
    }
}

bool bfoExpr(bool getToken){
    bool left = bprimExpr(getToken);

    while(true){
        switch(curr_token){
            case AND:
                left = left && bprimExpr(true);
            case OR:
                left = left || bprimExpr(true);
            default:
                return left;
        }
    }
}
