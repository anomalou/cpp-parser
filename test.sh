mkdir build; \
lex -o src/lex.yy.c src/rules.l && \
gcc src/lex.yy.c src/test.c && \
# echo "\n===light test===\n" && \
# ./a.out < tests/lightTest.c; \
echo "\n===major test===\n" &&\
./a.out < tests/majorTestNoComments.c; 
# echo "\n===major test===\n" && \
# ./a.out < tests/majorTest.c;