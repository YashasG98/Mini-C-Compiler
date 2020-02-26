# gcc input.c
yacc -d parser.y
flex scanner.l
gcc -o parse lex.yy.c y.tab.h y.tab.c -ll -ly
./parse < input.c
rm lex.yy.c y.tab.h y.tab.c parse