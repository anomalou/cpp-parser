#include <iostream>

#pragma region Enums

enum Token{
    ENDF = 256,

};

#pragma endregion

#pragma region FunctionsDeclaration

bool program(bool bGetNextLexem);
bool includesPart(bool bGetNextLexem);
bool mainPart(bool bGetNextLexem);
bool include(bool bGetNextLexem);
bool main(bool bGetNextLexem);
bool mainBody(bool bGetNextLexem);
bool term(bool bGetNextLexem);
bool text(bool bGetNextLexem);
bool createVar(bool bGetNextLexem);
bool setVar(bool bGetNextLexem);
bool callFunc(bool bGetNextLexem);
bool logBlock(bool bGetNextLexem);
bool expr(bool bGetNextLexem);
bool rExpr(bool bGetNextLexem);
bool params(bool bGetNextLexem);
bool param(bool bGetNextLexem);
bool logExpr(bool bGetNextLexem);
bool rLogExpr(bool bGetNextLexem);
bool program(bool bGetNextLexem);
bool ifBody(bool bGetNextLexem);
bool sign(bool bGetNextLexem);
bool logSign(bool bGetNextLexem);

#pragma endregion

using namespace std;

string sourceCodePath;

enum Token currentLexem = ENDF;

int main(int argc, char *argv[]){


    if(argc < 1){
        cout << "Please use parser like this: parser <path to source code>" << endl;
        return -1;
    }

    

    cout << "Source code correct!" << endl;

    return 0;
}

bool program(bool bGetNextLexem){

}

bool includesPart(bool bGetNextLexem){

}

bool mainPart(bool bGetNextLexem){

}

bool include(bool bGetNextLexem){

}

bool main(bool bGetNextLexem){

}

bool mainBody(bool bGetNextLexem){

}

bool term(bool bGetNextLexem){

}

bool text(bool bGetNextLexem){

}

bool createVar(bool bGetNextLexem){

}

bool setVar(bool bGetNextLexem){

}

bool callFunc(bool bGetNextLexem){

}

bool logBlock(bool bGetNextLexem){

}

bool expr(bool bGetNextLexem){

}

bool rExpr(bool bGetNextLexem){

}

bool params(bool bGetNextLexem){

}

bool param(bool bGetNextLexem){

}

bool logExpr(bool bGetNextLexem){

}

bool rLogExpr(bool bGetNextLexem){

}

bool program(bool bGetNextLexem){

}

bool ifBody(bool bGetNextLexem){

}

bool sign(bool bGetNextLexem){

}

bool logSign(bool bGetNextLexem){

}