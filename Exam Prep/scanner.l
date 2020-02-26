%{
    #include "y.tab.h"
    #include <string.h>
    #define TABLE_SIZE 1001

    int line_no = 1;
    
    int chash(char *str){
        unsigned int hash = 7381;
        int c;
        while(c = *str++)
            hash = ((hash<<5)+hash) + c;
        return hash % TABLE_SIZE;
    }

    typedef struct constantTable{
        char value[100];
        char type_of_constant[100];
        int line_no;
        int length;
    }constantTable;

    constantTable cTable[TABLE_SIZE];

    void insert_into_constant_table(char*value, char *type_of_constant, int line_no){
        int hash_value = chash(value);
        if(cTable[hash_value].length == 0){
            strcpy(cTable[hash_value].value, value);
            strcpy(cTable[hash_value].type_of_constant, type_of_constant);
            cTable[hash_value].length = strlen(value);
            cTable[hash_value].line_no = line_no;
            return;
        }
        int pos = 0;
        for(int i= hash_value + 1;i!=hash_value;i = (i+1)%TABLE_SIZE){
            if(cTable[i].length == 0){
                pos = i;
                break;
            }
        }
        strcpy(cTable[pos].value, value);
        strcpy(cTable[pos].type_of_constant, type_of_constant);
        cTable[pos].length = strlen(value);
        cTable[pos].line_no = line_no;
    }

    void print_constant_table(){
        for(int i=0;i< TABLE_SIZE;i++){
            if(cTable[i].length == 0)
                continue;
            else
                printf("%d\t\t%s\t%s\n",cTable[i].line_no, cTable[i].type_of_constant, cTable[i].value);
        }
    }
%}

TAB                 [\t]
WHITESPACES         {TAB}+
ALPHA               [A-Za-z]
INTEGER             [0-9]
IDENTIFIER          ({ALPHA}|[_])({ALPHA}|{INTEGER}|[_])*
FLOAT_CONSTANT      {INTEGER}*[.]{INTEGER}+
PRE_PROC_DIRECTIVE  #include[ \t]*<{ALPHA}*.h>
ARITH_OP            "+"|"-"|"*"|"/"|"%"
RELAT_OP            "=="|">="|"<="|">"|"<"
STRING_CONSTANT     ["](.)*["]

%%
[;,=(){}"]              {return *yytext;}
{WHITESPACES}           {;}
[\n]                    {line_no++;}
{PRE_PROC_DIRECTIVE}    {return PRE_PROC_DIRECTIVE;}
"int"                   {return INT;}
"float"                 {return FLOAT;}
"char"                  {return CHAR;}
"double"                {return DOUBLE;}
"main"                  {return MAIN;}
"printf"                {return PRINTF;}
"for"                   {return FOR;}
"return"                {return RETURN;}
"if"                    {return IF;}
{INTEGER}+              {insert_into_constant_table(yytext,"INTEGER CONSTANT",line_no);return INTEGER_CONSTANT;}
{FLOAT_CONSTANT}        {insert_into_constant_table(yytext,"FLOAT CONSTANT",line_no);return FLOAT_CONSTANT;}
{ARITH_OP}              {return ARITH_OP;}
{RELAT_OP}              {return RELAT_OP;}
{IDENTIFIER}            {return IDENTIFIER;}
{STRING_CONSTANT}       {insert_into_constant_table(yytext,"STRING CONSTANT",line_no);return STRING_CONSTANT;}

%%
