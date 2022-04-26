lex lex/rules.l; \
mkdir build; \
g++ \
-fdiagnostics-color=always \
-g main.cpp \
lex.yy.c \
-o build/main 