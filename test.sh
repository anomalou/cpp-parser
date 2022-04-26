lex lex/rules.l; \
gcc lex.yy.c && \
# echo "\n===light test===\n" && \
# ./a.out < tests/lightTest.c; \
echo "\n===major test===\n" &&\
./a.out < tests/majorTestNoComments.c; 
# echo "\n===major test===\n" && \
# ./a.out < tests/majorTest.c; 