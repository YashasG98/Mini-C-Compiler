# !/bin/bash

yacc -d parser.y
lex scanner.l
gcc lex.yy.c y.tab.c
./a.out < input.txt