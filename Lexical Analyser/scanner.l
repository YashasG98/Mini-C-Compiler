%{
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include "definitions.h"
    yylType yylVal;
    int line_count = 0;
%}
%x COMMENT

DELIMITER [ \t]
WHITESPACES {DELIMITER}+
KEYWORD (auto)|(break)|(case)|(char)|(const)|(continue)|(default)|(do)|(double)|(else)|(enum)|(extern)|(float)|(for)|(goto)|(if)|(int)|(long)|(register)|(return)|(short)|(signed)|(sizeof)|(static)|(sturct)|(switch)|(typedef)|(union)|(unsigned)|(void)|(volatile)|(while)
DECI [0-9]+
SEPARATOR \(|\)|\{|\}|\[|\]
ARITH_OPERATORS \+|-|\*|\/|%|"++"|"--"
RELATIONAL_OPERATORS (<)|(>)|(==)|(<=)|(>=)|(!=)
BITWISE_OPERATORS [\&]|[\|]|[\^]|[\~]|(<<)|(>>)
LOGICAL_OPERATORS &&|[|][|]|!
ASSIGNMENT_OPERATORS "="|"+="|"-="|"*="|"/="|"%="|"<<="|">>="|"&="|"^="|"|="
ALPHA [a-zA-Z]
IDENTIFIER ({ALPHA}|[_])({ALPHA}|{DECI}|(_))*
REAL ({DECI}+)[.]({DECI}+)
STRING .*
STRING_CONSTANT \"(.)*\"
PREPROCESSOR_DIRECTIVE (#define[ \t]*([a-zA-Z0-9]+)[ \t]([a-zA-Z0-9]+))|(#include[ \t]*<{ALPHA}*.h>)|(#include[ \t]*"{ALPHA}*.h")|#undef|#ifndef|#ifdef|#if|#else|#elif|#endif|#error|#pragma
SINGLE_LINE_COMMENT [/][/]([\"]|{STRING})*

%%
{WHITESPACES} {;}
\n {++line_count;}
{ASSIGNMENT_OPERATORS} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return ASSIGNMENT_OPERATORS;
}
{SEPARATOR} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return SEPARATOR;
}
;   {return (int)';';}
,   {return (int)',';}
{ARITH_OPERATORS} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return ARITH_OPERATORS;
}
{RELATIONAL_OPERATORS} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return RELATIONAL_OPERATORS;
}
{LOGICAL_OPERATORS} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return LOGICAL_OPERATORS;
}
{BITWISE_OPERATORS} {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return BITWISE_OPERATORS;
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
{DECI}[\.]{DECI}[\.](.)*    {
      printf ("ERROR: Illegal floating point constant at line %d\n​ ",line_count+1);return 0;  
}
[\'](.)[\']     {
    yylVal.string = (char *)malloc((yyleng+1)*sizeof(char));
    strncpy(yylVal.string,yytext,yyleng+1);
    yylVal.string[yyleng+1]='\0';
    return CHARACTER_CONSTANT;
}
[\'](.)(.)+[\']     {
    printf ("ERROR: Illegal character constant at line %d\n​ ",line_count+1);return 0;
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
"/*" {
    BEGIN COMMENT;
    printf("\"%s", yytext);
}
<COMMENT>. {printf ("%s",yytext);}
<COMMENT>\n { printf("\n"); ++line_count; }
<COMMENT>"/*" { printf ("%s[WARNING: Beginning nested comment]", yytext); }
<COMMENT>"*/" { BEGIN INITIAL; printf("%s\"\t- MULTI LINE COMMENT\n",yytext); }
<COMMENT><<EOF>> {printf ("ERROR: Comment not closed at line %d\n​ ",line_count+1);return 0;}
.*"*/".* { printf ("\nERROR: Closing Comment wrongly at line %d\n", line_count); }
{DECI}+[.]?({ALPHA}|{DECI})+ {
    printf ("ERROR: Illegal Identifier at %d line\n", line_count+1);
}
(.?) {
        if(yytext[0]=='#')
        {
        printf("​ ERROR: Pre-Processor directive at line no.%d\n​ ",line_count+1);
        }
        else if(yytext[0]=='/')
        {
        printf("​ ERROR: Comment not closed at line no.%d\n​ ",line_count);
        }
        else if(yytext[0]=='"')
        {
        printf(" ERROR: Incomplete string at line no.%d\n",line_count+2);
        }
        else
        {
        printf(" ERROR at line no. %d\n",line_count);
        }
        return 0;
    }
%%
int yywrap(void) {
    return 1;
}
