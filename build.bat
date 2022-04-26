mkdir build ^
lex src/rules.l  -o build/lex.yy.c && ^
C:\\Program Files\\mingw-w64\\x86_64-8.1.0-posix-seh-rt_v6-rev0\\mingw64\\bin\\g++.exe ^ 
-fdiagnostics-color=always ^
-g src/main.cpp ^
build/lex.yy.c ^
-o build/main.exe