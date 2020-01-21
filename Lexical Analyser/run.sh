flex lex.l
cc -Wall -c lex.yy.c
cc -Wall parser.c lex.yy.o
./a.out < test_cases/test_3.c
rm a.out lex.yy.c lex.yy.o