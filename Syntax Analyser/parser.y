%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    void yyerror(const char *s);
    int yylex();

    extern char current_identifier[35];
    extern char current_scope[35];
    extern char current_data_type[20];
    extern char current_value[20];
    extern int current_line_no;
    
    // Hash function
    int hash(char *);

    // Symbol Table Defintions
    typedef struct symbolTable {
        char name[100];
        char type[100];
        char scope[100];
        char value[100];
        int length;
        int line_no;
    } symbolTable;

    symbolTable sTable[1001];

    int lookup_symbol_table(char *str){
        int value = hash(str);
        if (sTable[value].length == 0) return 0;
        else if(strcmp(sTable[value].name,str) == 0) {
            if (strcmp(sTable[value].scope, current_scope) == 0)
                return 1;
            return 0;
        }
        else {
            for (int i=value+1;i!=value; i=(i+1)%1001){
                if (strcmp(sTable[i].name,str) == 0) 
                    return 1;
            }
            return 0;
        }
    }

    void insert_into_symbol_table(char *symbol, char *type, char *scope, int line_no){
        if(lookup_symbol_table(symbol)) return;
        else {
            int value = hash(symbol);
            if(sTable[value].length == 0){
                strcpy(sTable[value].name, symbol);
                strcpy(sTable[value].type, type);
                strcpy(sTable[value].scope, scope);
                sTable[value].length = strlen(symbol);
                sTable[value].line_no = line_no;
                return;
            }
            int pos = 0;

            for (int i = value + 1 ; i!=value ; i = (i+1)%1001) {
                if(sTable[i].length == 0){
                    pos = i;
                    break;
                }
            }

            strcpy(sTable[pos].name,symbol);
            strcpy(sTable[pos].type, type);
            strcpy(sTable[pos].scope, scope);
            sTable[pos].line_no = line_no;
            sTable[pos].length = strlen(symbol);
        }
    }

    void insert_into_symbol_table_value(char *identifier, char *value, char *scope){
        for(int i=0;i<1001;i++){
            if ((strcmp(sTable[i].name, identifier) == 0) 
                    && (strcmp (sTable[i].scope, scope) == 0)){
                strcpy(sTable[i].value,value);
                return;
            }
        }
    }

    void print_symbol_table(){
        for(int i=0;i<1001;i++){
            if(sTable[i].length == 0) continue;
            printf("  %s\t\t%s\t%s\t%s\t%d\n",sTable[i].name, sTable[i].type, sTable[i].scope, sTable[i].value, sTable[i].line_no);
        }
    }

    // Function Table Definitions
    typedef struct functionTable {
        char name[40];
        char return_type[20];
        symbolTable arg_list[20];
        int no_of_args;
        int line_no;
        int length;
    } functionTable;

    functionTable fTable[1001];

    int lookup_function_table(char *str){
        int value = hash(str);
        if (fTable[value].length == 0) return 0;
        else if (strcmp(fTable[value].name,str) == 0) return 1;
        else {
            for (int i=value+1;i!=value; i=(i+1)%1001){
                if (strcmp(fTable[i].name,str) == 0) 
                    return 1;
            } 
            return 0;
        }
    }

    void insert_into_function_table(char *symbol, char *return_type, int line_no){
        if(lookup_function_table(symbol)) return;
        else {
            int value = hash(symbol);
            if(fTable[value].length == 0){
                strcpy(fTable[value].name, symbol);
                strcpy(fTable[value].return_type, return_type);
                fTable[value].length = strlen(symbol);
                fTable[value].line_no = line_no;
                fTable[value].no_of_args = 0;
                return;
            }
            int pos = 0;

            for (int i = value + 1 ; i!=value ; i = (i+1)%1001) {
                if(fTable[i].length == 0){
                    pos = i;
                    break;
                }
            }

            strcpy(fTable[pos].name,symbol);
            strcpy(fTable[pos].return_type, return_type);
            fTable[pos].line_no = line_no;
            fTable[pos].length = strlen(symbol);
            fTable[pos].no_of_args = 0;
        }
    }

    void insert_into_function_table_arg_list(char *function_name, char *data_type, char *identifier){
        for(int i=0;i<1001;i++){
            if(strcmp(fTable[i].name,function_name) == 0){
                int j = fTable[i].no_of_args++;
                strcpy(fTable[i].arg_list[j].name,identifier);
                strcpy(fTable[i].arg_list[j].type,data_type);
                strcpy(fTable[i].arg_list[j].scope,function_name);
                fTable[i].arg_list[j].length = strlen(identifier);
                return;
            }
        }
    }

    void print_function_table(){
        for (int i=0;i<1001;i++){
            if(fTable[i].length == 0) continue;
            else {
                printf ("  %s\t%s\t%d\t%d\t",fTable[i].name, fTable[i].return_type, fTable[i].line_no, fTable[i].no_of_args);
                for(int j=0;j<fTable[i].no_of_args;j++){
                    printf("%s %s, ",fTable[i].arg_list[j].type, fTable[i].arg_list[j].name);
                }
                printf("\n");
            }
        }
    }

    // TODO LIST:
    // printf, scanf
    // Error stuff

%}

%define parse.lac full
%define parse.error verbose

%token MAIN INT CHAR FLOAT DOUBLE
%token IDENTIFIER PRE_PROCESSOR_DIRECTIVE 
%token REAL_CONSTANT INTEGER_CONSTANT STRING_CONSTANT CHAR_CONSTANT
%token IF ELSE NOT_OP FOR WHILE DO LOG_AND LOG_OR EQUALITY_OP REL_OP SHIFT_OP
%token ADD_OP MUL_OP ASSIGN_OP UNARY_OP RETURN BREAK DEFAULT CASE SWITCH
%token INCREMENT_OPERATOR DECREMENT_OPERATOR PRINTF SCANF
%start program

%%

// program structure

program : pre_processor_section global_decl main_fn user_defined_fn_decl;

pre_processor_section : 
                      | pre_processor_section PRE_PROCESSOR_DIRECTIVE ;

global_decl : { strcpy(current_scope, "global"); }
            | global_decl variable_decl 
            | global_decl global_fn_decl ;

global_fn_decl : data_type IDENTIFIER { 
        strcpy(current_scope, current_identifier);
        insert_into_function_table (current_identifier, current_data_type, current_line_no);
    } 
    '(' argsList ')' statements ;

argsList : args | ;

args : data_type IDENTIFIER  {
            insert_into_function_table_arg_list(current_scope, current_data_type, current_identifier);
        }
     | args ',' data_type IDENTIFIER {
            insert_into_function_table_arg_list(current_scope, current_data_type, current_identifier);
        }
     ;

main_fn : data_type MAIN {strcpy(current_scope, "main");} '(' ')' statements 
        | MAIN {strcpy(current_scope, "main");} '(' ')' statements           

user_defined_fn_decl : user_defined_fn_decl global_fn_decl 
                     | ;

// Statements defn

compound_statement : '{' local_decl statement_list '}' ;

statements : compound_statement 
           | looping_constructs 
           | expn_statement 
           | selection_statement 
           | labelled_statement
           | return_statement
           | break_statement  
           | io_statements;

io_statements : printf_statement 
              | scanf_statement ;

printf_statement : PRINTF '(' STRING_CONSTANT ',' printf_args ')' ';' 
                 | PRINTF '(' STRING_CONSTANT ')' ';' ;

printf_args : printf_args ',' assignment_expn | assignment_expn ;

scanf_statement : SCANF '(' STRING_CONSTANT ',' scanf_args ')' ';'

scanf_args : scanf_args ',' unary_expn | unary_expn ;

local_decl : local_decl variable_decl 
           | ; 

statement_list : statement_list statements 
               | ;

expn_statement : expn ';' 
               | ';' ;

return_statement : RETURN expn_statement ;

break_statement : BREAK ';' ;

labelled_statement : CASE expn ':' statements 
                   | DEFAULT ':' statements ;

// if-else blocks (shift-reduce problem ide, check madu)
selection_statement : IF '(' expn ')' statements 
                    | IF '(' expn ')' statements ELSE statements ;
                    | SWITCH '(' expn ')' statements ;

// looping constructs
looping_constructs : while_loop 
                   | do_while_loop 
                   | for_loop;

while_loop : WHILE '(' cond_exp ')' statements ;

do_while_loop : DO statements WHILE '(' cond_exp ')' ';' ;

for_loop : FOR '(' expn1 ';' expn1 ';' expn1 ')' statements 

expn1 : expn | ;

// Expression hierarchy
expn : assignment_expn 
     | expn ',' assignment_expn ;

assignment_expn : cond_exp 
                | unary_expn ASSIGN_OP assignment_expn ;

cond_exp : logical_or_expn ;

logical_or_expn : logical_and_expn
                | logical_or_expn LOG_OR logical_and_expn ;

logical_and_expn : equality_expn
                 | logical_and_expn LOG_AND equality_expn ;

equality_expn : relational_expn 
              | equality_expn EQUALITY_OP relational_expn ;

relational_expn : shift_expn 
                | relational_expn REL_OP shift_expn ;

shift_expn : additive_expn 
           | shift_expn SHIFT_OP additive_expn ;

additive_expn : multiplicative_expn 
              | additive_expn ADD_OP multiplicative_expn ;

multiplicative_expn : unary_expn 
                    | multiplicative_expn MUL_OP unary_expn ;

unary_expn : postfix_expn 
           | INCREMENT_OPERATOR unary_expn 
           | DECREMENT_OPERATOR unary_expn 
           | UNARY_OP postfix_expn ;

postfix_expn : primary_expn 
             | postfix_expn INCREMENT_OPERATOR 
             | postfix_expn DECREMENT_OPERATOR ;

primary_expn : IDENTIFIER   { 
        insert_into_symbol_table(current_identifier, current_data_type, current_scope, current_line_no); 
    }  
             | INTEGER_CONSTANT {
        insert_into_symbol_table_value (current_identifier, current_value, current_scope);
    }
             | REAL_CONSTANT 
             | STRING_CONSTANT 
             | CHAR_CONSTANT 
             | '(' expn ')' ;

// Variable Declaration
variable_decl : data_type var_list ';' ;

var_list :  var_list ',' assignment_expn 
         | assignment_expn ;

data_type : INT 
          | CHAR 
          | DOUBLE 
          | FLOAT ;

%%

void print_constant_table();

void yyerror (const char *s){
    printf ("ERROR: %s\n", s);
}

int main(){
    int n = yyparse();
    if (!n){
        printf("\nSUCCESS\n");
        printf ("\n=================================================\n");
        printf ("\n\t\tSYMBOL TABLE \n\n");
        printf ("  Symbol\tType\tScope\tValue\tLine No\n");
        print_symbol_table();
        printf ("\n=================================================\n");
        printf ("\n");
        printf ("\n=================================================\n");
        printf ("\n\t\tFUNCTION TABLE \n\n");
        printf ("  Name\tReturn\tLine\tArgs\tArgList\n");
        print_function_table();
        printf ("\n=================================================\n");
        printf ("\n");
        printf ("\n=================================================\n");
        printf("\n\t\tCONSTANT TABLE \n\n");
        printf("  Line No\tType of Constant\tConstant\n");
        print_constant_table();
        printf ("\n=================================================\n");    
    } 
    return 0;
}