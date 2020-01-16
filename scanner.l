%{
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include "definitions.h"
    yylType yylVal;
%}

DELIMITER [ \t]
WHITESPACES {DELIMITER}+
KEYWORD (auto)|(break)|(case)|(char)|(const)|(continue)|(default)|(do)|(double)|(else)|(enum)|(extern)|(float)|(for)|(goto)|(if)|(int)|(long)|(register)|(return)|(short)|(signed)|(sizeof)|(static)|(sturct)|(switch)|(typedef)|(union)|(unsigned)|(void)|(volatile)|(while)|(printf)|(scanf)|(main)
DECI [0-9]+
SEPARATOR \(|\)|\{|\}|,|;
BINARY_OPERATORS \+|-|\*|\/|%
UNARY_OPERATORS (\|)|(\&)|~
COMPARISON_OPERATORS (<)|(>)|(==)|(<=)|(>=)|(!=)
ASSIGNMENT_OPERATOR =
ALPHA [a-zA-Z]
IDENTIFIER {ALPHA}({ALPHA}|{DECI})*
REAL ({DECI}+)[.]({DECI}+)
STRING ({ALPHA}|{WHITESPACES}|{SEPARATOR}|{DECI}|{BINARY_OPERATORS}|{UNARY_OPERATORS}|{COMPARISON_OPERATORS}|{ASSIGNMENT_OPERATOR}|~|!|@|#|$|%|^|&|\\|\/)
STRING_CONSTANT \"{STRING}*\"
ADDRESS_OPERATOR &
PREPROCESSOR_DIRECTIVE (#define[ \t]([a-zA-Z0-9]+)[ \t]([a-zA-Z0-9]+))|(#include[ \t]<{ALPHA}*.h>)|#undef|#ifndef|#ifdef|#if|#else|#elif|#endif|#error|#pragma
SINGLE_LINE_COMMENT [/][/]([\"]|{STRING})*
MULTI_LINE_COMMENT [\/][\*]({STRING}|[\n])*[\*][\/]
%%
{WHITESPACES} {;}
\n {return NEWLINE;}
{ASSIGNMENT_OPERATOR} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return ASSIGNMENT_OPERATOR;
}
{SEPARATOR} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return SEPARATOR;
}
{BINARY_OPERATORS} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return BINARY_OPERATORS;
}
{UNARY_OPERATORS} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return UNARY_OPERATORS;
}
{COMPARISON_OPERATORS} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return COMPARISON_OPERATORS;
}
{KEYWORD} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return KEYWORD;
}
{IDENTIFIER} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return IDENTIFIER;
}
{DECI} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return DECIMAL;
}
{REAL} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return REAL;
}
{PREPROCESSOR_DIRECTIVE} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return PREPROCESSOR_DIRECTIVE;
}
{STRING_CONSTANT} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return STRING;
}
{SINGLE_LINE_COMMENT} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return SLC;
}
{MULTI_LINE_COMMENT} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return MLC;
}
%%
int yywrap(void) {
    return 1;
}
