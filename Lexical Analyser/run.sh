# !/bin/bash

lex scanner.l
cc -Wall -c lex.yy.c
cc -Wall driver_code.c lex.yy.o
./a.out < $1
rm lex.yy.o lex.yy.c a.out