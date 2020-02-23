%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <limits.h>
    #include <math.h>
    #include <string.h>
    void yyerror(char *s);
    #include "y.tab.h"
    int line_count = 0;

    // Hash function
    int hash(char *str){
        unsigned int hash = 5381;
        int c;
        while (c=*str++)
            hash = ((hash<<5)+hash)+c;
        return hash%1001;
    }

    // Constant Table Definitions

    typedef struct constantTable{
        char name[100];
        char type[100];
        int line_no;
        int length;
        int integer_value;
        double double_value;
        char *string_value;
        char char_value;
    } constantTable;

    constantTable cTable[1001];

    int lookup_constant_table(char *str){
        int value = hash(str);
        if (cTable[value].length == 0) return 0;
        else if(strcmp(cTable[value].name,str) == 0) return 1;
        else {
            for (int i=value+1;i!=value; i=(i+1)%1001){
                if (strcmp(cTable[i].name,str) == 0) 
                    return 1;
            }
            return 0;
        }
    }

    void insert_into_constant_table(char *value, char *type, int type_code, int line_no){
        if(lookup_constant_table(value)) return;
        else {
            int hash_value = hash(value);
            if(cTable[hash_value].length == 0){
                strcpy(cTable[hash_value].name, value);
                strcpy(cTable[hash_value].type, type);
                cTable[hash_value].length = strlen(value);
                cTable[hash_value].line_no = line_no;
                switch (type_code)
                {
                    case INTEGER_CONSTANT: cTable[hash_value].integer_value = atoi(value); 
                                           cTable[hash_value].double_value = INFINITY;
                                           break;
                    case REAL_CONSTANT: cTable[hash_value].double_value = strtof(value,NULL); 
                                        cTable[hash_value].integer_value = INT_MAX;
                                        break;
                    // case STRING_CONSTANT:
                    //     cTable[hash_value].string_value = (char *)malloc(strlen(value)*sizeof(char)); 
                    //     strcpy(cTable[hash_value].string_value,value); 
                    //     break;
                    default: break;
                }
                return;
            }
            int pos = 0;

            for (int i = hash_value + 1 ; i!=hash_value ; i = (i+1)%1001) {
                if(cTable[i].length == 0){
                    pos = i;
                    break;
                }
            }

            strcpy(cTable[pos].name, value);
            strcpy(cTable[pos].type, type);
            cTable[pos].length = strlen(value);
            cTable[pos].line_no = line_no;
            switch (type_code)
            {
                case INTEGER_CONSTANT: cTable[pos].integer_value = atoi(value); break;
                case REAL_CONSTANT: cTable[pos].double_value = strtof(value,NULL); break;
                // case STRING:
                //     cTable[pos].string_value = (char *)malloc(strlen(value)*sizeof(char));      
                //     strcpy(cTable[pos].string_value,value); break;
                default: break;
            }
        }
    }

    void print_constant_table(){
        for(int i=0;i<1001;i++){
            if(cTable[i].length == 0) continue;
            else {
                if(cTable[i].integer_value != INT_MAX){
                    printf ("  %d\t\t%s\t%d\n", cTable[i].line_no, cTable[i].type, cTable[i].integer_value);
                } else if (cTable[i].double_value != INFINITY){
                    printf ("  %d\t\t%s\t\t%lf\n", cTable[i].line_no, cTable[i].type, cTable[i].double_value);
                } else if (cTable[i].string_value != NULL){
                    printf ("  %d\t\t%s\t%s\n", cTable[i].line_no, cTable[i].type, cTable[i].string_value);
                }
            }
        }    
    }

    char current_identifier[35];
    char current_scope[35];
    char current_data_type[20];
    char current_value[20];
    int current_line_no;
%}

WHITESPACES [ \t]+
ALPHA [a-zA-Z]
DECI [0-9]+
IDENTIFIER ({ALPHA}|[_])({ALPHA}|{DECI}|(_))*
REAL ({DECI})[.]({DECI})
RELATIONAL_OPERATORS (<)|(>)|(<=)|(>=)
EQUALITY_OPERATORS (==)|(!=)
ASSIGNMENT_OPERATORS "="|"+="|"-="|"*="|"/="|"%="|"<<="|">>="
INCREMENT_OPERATOR "++"
DECREMENT_OPERATOR "--"
UNARY_OPERATORS "&"|"~"|"!"
ADD_OP "+"|"-"
MUL_OP "*"|"/"|"%"
PRE_PROCESSOR_DIRECTIVE (#define[ \t]*([a-zA-Z0-9]+)[ \t]([a-zA-Z0-9]+))|(#include[ \t]*<{ALPHA}*.h>)|(#include[ \t]*"{ALPHA}*.h")

%%

{WHITESPACES} ;
[,;{}():] return *yytext;
{PRE_PROCESSOR_DIRECTIVE} {return PRE_PROCESSOR_DIRECTIVE;}
[-+]?{DECI} {
    insert_into_constant_table(yytext,"INTEGER CONSTANT",INTEGER_CONSTANT,line_count+1);
    strcpy(current_value, yytext);
    return INTEGER_CONSTANT;
}
[-+]?{REAL} {
    insert_into_constant_table(yytext,"REAL CONSTANT",REAL_CONSTANT,line_count+1);
    return REAL_CONSTANT;
}
{EQUALITY_OPERATORS} {return EQUALITY_OP;}
{RELATIONAL_OPERATORS} {return REL_OP;}
{ASSIGNMENT_OPERATORS} {return ASSIGN_OP;}
{INCREMENT_OPERATOR} {return INCREMENT_OPERATOR;}
{DECREMENT_OPERATOR} {return DECREMENT_OPERATOR;}
{UNARY_OPERATORS} {return UNARY_OP;}
{ADD_OP} {return ADD_OP;}
{MUL_OP} {return MUL_OP;}

"&&" {return LOG_AND;}
"||" {return LOG_OR;}
"main" {return MAIN;}
"int" {
    strcpy(current_data_type,yytext);
    return INT;
}
"char" {
    strcpy(current_data_type,yytext);
    return CHAR;
}
"double" {
    strcpy(current_data_type,yytext);
    return DOUBLE;
}
"float" {
    strcpy(current_data_type,yytext);
    return FLOAT;
}
"if" {return IF;}
"else" {return ELSE;}
"for" {return FOR;}
"while" {return WHILE;}
"do" {return DO;}
"return" {return RETURN;}
"break" {return BREAK;}
"switch" {return SWITCH;}
"case" {return CASE;}
"default" {return DEFAULT;}

{IDENTIFIER} {
    strcpy(current_identifier,yytext); 
    current_line_no = line_count + 1;
    return IDENTIFIER;
}
[\n] {++line_count;}

%%
int yywrap(void) {return 1;}