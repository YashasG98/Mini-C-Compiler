# !/bin/bash

lex $1
cc -Wall -c lex.yy.c
cc -Wall driver_code.c lex.yy.o
./a.out < test_cases/test5.c
rm lex.yy.o lex.yy.c a.out