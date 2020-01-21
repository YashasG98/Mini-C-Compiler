DELIM ([ \t])
WHITESPACES ({DELIM}+)
POSI_DECI ([1-9])
DECI (0|{POSI_DECI})
DECIMAL (0|{POSI_DECI}{DECI}*)
LOWER ([a-z])
LETTER ({LOWER}|[:upper:]|_)
IDENTIFIER ({LETTER}({LETTER}|{DECI})*)
OPERATOR "+"|"-"|"*"|"/"|"%"|"++"|"--"|"=="|"!="|">"|"<"|">="|"<="|"&&"|"||"|"!"|"&"|"|"|"^"|"~"|"<<"|">>"|"="|"+="|"-="|"*="|"/="|"%="|"<<="|">>="|"&="|"^="|"|="

%{
#include <string.h>
#include <stdlib.h>
#include "y.tab.h" // tokens are defined
int line_count = 0; 
yylType yylval;
%}
%option noyywrap
%%

\n              {++line_count;return (int)'\n';}
{WHITESPACES}   {;}
[/][/](.)*      {
                    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
                    strncpy(yylval.string, yytext, yyleng + 1);
                    return SINGLE_COMM;
                }   
[/][*]((.)|[\n])*[*][/]      {
                    for(int i=0;i<yyleng;i++)
                        if(yytext[i]=='\n')
                            ++line_count;
                    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
                    strncpy(yylval.string, yytext, yyleng + 1);
                    return MULTI_COMM;
                }
{DECIMAL}+[.]?{LETTER}+ {
                    printf("​ ERROR: Illegal Identifier at line no.%d\n​ ",line_count);
                }
auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while    {
                    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
                    strncpy(yylval.string, yytext, yyleng + 1);return KEYWORD;
                }
(#include[ ]*([<]){LETTER}*[.][h]([>]))|((#include[ ]*(["]){LETTER}*[.][h](["])))       {
                                                yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
                                                strncpy(yylval.string, yytext, yyleng + 1);
                                                return PRE_PROC_DIREC;
                                            }
#define[ ]*(.)*     {
                        yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
                        strncpy(yylval.string, yytext, yyleng + 1);
                        return PRE_PROC_DIREC;
                    }
["](.)*["]      {
                    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
                    strncpy(yylval.string, yytext, yyleng + 1);
                    return STRING;
                }
{DECIMAL}+[.]{DECI}+    {
                    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
                    strncpy(yylval.string, yytext, yyleng + 1);
                    return FLOAT_NUM;
                }
\(              {return (int)'(';}
\)              {return (int)')';}
\{              {return (int)'{';}
\}              {return (int)'}';}
\[              {return (int)'[';}
\]              {return (int)']';}
;               {return (int)';';}
,               {return (int)',';}
{OPERATOR}      {   
                    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
                    strncpy(yylval.string, yytext, yyleng + 1);
                    return OPERATOR;
                }                
{IDENTIFIER}    {
                    yylval.string=(char *)malloc((yyleng+1)*(sizeof(char)));
                    strncpy(yylval.string, yytext, yyleng + 1);
                    return ID;
                }
{DECIMAL}       {
                    yylval.integer = atoi(yytext);
                    return INT_NUM;
                }
(.?) {
        if(yytext[0]=='#')
        {
        printf("​ ERROR: Pre-Processor directive at line no.%d\n​ ",line_count);
        }
        else if(yytext[0]=='/')
        {
        printf("​ ERROR: Comment not closed at line no.%d\n​ ",line_count);
        }
        else if(yytext[0]=='"')
        {
        printf(" ERROR: Incomplete string at line no.%d\n",line_count+1);
        }
        else
        {
        printf(" ERROR at line no. %d\n",line_count);
        }
        return 0;
    }

%%