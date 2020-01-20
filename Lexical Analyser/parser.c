#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
extern yylType yylval;
int main(){
    int s;

    while(s=yylex()){
        switch(s){
            case '\n':
                printf("\n");
                break;
            case '(':
                printf("(\t- Opening Bracket\n");
                break;
            case ')':
                printf(")\t- Closing Bracket\n");
                break;
            case '{':
                printf("{\t- Opening Braces\n");
                break;
            case '}':
                printf("}\t- Closing Braces\n");
                break;
            case ';':
                printf(";\t- Semicolon Delimiter\n");
                break;
            case ',':
                printf(",\t- Comma Delimiter\n");
                break;
            case PRE_PROC_DIREC : 
                printf("%s\t- Pre-processing Directive",yylval.string);
                break;
            case OPERATOR : 
                printf("%s\t- Operator\n",yylval.string);
                break;
            case KEYWORD:
                printf("%s\t- Keyword\n",yylval.string);
                break;
            case ID:
                printf("%s\t- Identifier\n",yylval.string);
                free(yylval.string);
                break;
            case INT_NUM:
                printf("%d\t- Integer Literal\n",yylval.integer);
                break;
            case FLOAT_NUM:
                printf("%s\t- Floating Point Literal\n",yylval.string);
                break;
            case SINGLE_COMM:
                printf("%s\t- Single Line Comment\n",yylval.string);
                free(yylval.string);
                break;
            case MULTI_COMM:
                printf("%s\t- Multi Line Comment\n",yylval.string);
                free(yylval.string);
                break;
            case STRING : 
                printf("%s\t- String\n",yylval.string);
                break;
            default:
                ;
        }
    }
    return 0;
}