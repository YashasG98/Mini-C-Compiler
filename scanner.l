%{
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include "definitions.h"
    yylType yylVal;
%}

DELIMITER [ \t]
WHITESPACES {DELIMITER}+
KEYWORD (if)|(else)|(while)|(for)|(do)|(int)|(short)|(long)|(float)|(double)|(void)|(main)
DECI [0-9]+
SEPARATOR \(|\)|\{|\}|,|;
BINARY_OPERATORS \+|-|\*|\/|%
UNARY_OPERATORS (\|)|(\&)|~
COMPARISON_OPERATORS (<)|(>)|(==)|(<=)|(>=)|(!=)
ASSIGNMENT_OPERATOR =
ALPHA [a-zA-Z]
IDENTIFIER {ALPHA}({ALPHA}|{DECI})*
REAL ({DECI}+)[.]({DECI}+)

%%
{WHITESPACES} {;}
\n {return NEWLINE;}
{ASSIGNMENT_OPERATOR} {
    yylVal.string = (char *)malloc(yyleng+1*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return ASSIGNMENT_OPERATOR;
}
{SEPARATOR} {
    yylVal.string = (char *)malloc(yyleng+1*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return SEPARATOR;
}
{BINARY_OPERATORS} {
    yylVal.string = (char *)malloc(yyleng+1*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return BINARY_OPERATORS;
}
{UNARY_OPERATORS} {
    yylVal.string = (char *)malloc(yyleng+1*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return UNARY_OPERATORS;
}
{COMPARISON_OPERATORS} {
    yylVal.string = (char *)malloc(yyleng+1*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return COMPARISON_OPERATORS;
}
{KEYWORD} {
    yylVal.string = (char *)malloc(yyleng+1*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return KEYWORD;
}
{IDENTIFIER} {
    yylVal.string = (char *)malloc(yyleng+1*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return IDENTIFIER;
}
{DECI} {
    yylVal.string = (char *)malloc(yyleng+1*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return DECIMAL;
}
{REAL} {
    yylVal.string = (char *)malloc(yyleng+1*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return REAL;
}
%%
int yywrap(void) {
    return 1;
}
