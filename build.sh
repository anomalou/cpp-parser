mkdir build; \
lex src/rules.l -o build/lex.yy.c && \
g++ \
-fdiagnostics-color=always \
-g src/main.cpp \
build/lex.yy.c \
-o build/main 