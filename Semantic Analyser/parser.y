%{
    #include <stdbool.h>
    #include "symbol_table.h"
    void yyerror(const char *s);
    void error(const char *s, int line_no);
    int yylex();

    extern char current_identifier[35];
    extern char current_scope[35];
    extern char current_data_type[20];
    extern char current_value[20];
    extern int current_opening_brace_line_no;
    extern int current_closing_brace_line_no;
    extern int current_line_no;
    extern int lex_error;
    
    bool isExpn = false;
    bool isReturn = false;
    int no_of_args = 0;
    char current_return_type[20];
    char current_function[35];

    // Stack
    int stack[100];
    int top = -1;

    void push(int x){
        if (top == 100){
            return;
        } else {
            stack[++top] = x;
        }
    }

    int pop(){
        if (top == -1){
            return -1;
        } else {
            return stack[top--];
        }
    }

    int peek(){
        if (top == -1){
            return -1;
        } else {
            return stack[top];
        }
    }

%}

%define parse.lac full
%define parse.error verbose

%token MAIN INT CHAR FLOAT DOUBLE
%token IDENTIFIER PRE_PROCESSOR_DIRECTIVE 
%token REAL_CONSTANT INTEGER_CONSTANT STRING_CONSTANT CHAR_CONSTANT
%token IF ELSE NOT_OP FOR WHILE DO LOG_AND LOG_OR EQUALITY_OP REL_OP SHIFT_OP
%token ADD_OP MUL_OP ASSIGN_OP UNARY_OP RETURN BREAK DEFAULT CASE SWITCH
%token INCREMENT_OPERATOR DECREMENT_OPERATOR PRINTF SCANF VOID
%start program

%expect 1

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
        strcpy(current_return_type, current_data_type);
        insert_into_function_table (current_identifier, current_return_type, current_line_no);
    } 
    '(' argsList ')' statements 
    | VOID IDENTIFIER {
        strcpy (current_scope, current_identifier);
        strcpy (current_return_type, "void");
        insert_into_function_table (current_identifier, current_return_type, current_line_no);
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
        | VOID MAIN {strcpy (current_scope, "main");} '(' ')' statements ;

user_defined_fn_decl : user_defined_fn_decl global_fn_decl 
                     | ;

// Statements defn

compound_statement : '{' { push(current_opening_brace_line_no); }
local_decl statement_list {
    while (stack_top != -1) {
        symbolStack sym = stk[stack_top];
        if (lookup_arg_list(current_scope, sym.symbol_name, sym.data_type) == 2) {
            stack_top--;
            continue;
        }
        if (lookup_symbol_table(sym.symbol_name, sym.scope) == 0) {
            error ("Undeclared Variable", sym.line_no);
        }
    }
} '}' {
    if (peek() != -1) {
        int opening_boundary_line_no = pop();
        insert_into_symbol_table_closing_line(current_scope, opening_boundary_line_no, current_closing_brace_line_no); 
    }
};

statements : compound_statement {isReturn = false; isExpn = false;} 
           | looping_constructs 
           | expn_statement  
           | selection_statement 
           | labelled_statement 
           | return_statement
           | break_statement  
           | io_statements
           | function_call ;

function_call : IDENTIFIER {
    strcpy (current_function, current_identifier);
    if (lookup_function_table(current_identifier) == 0) {
        yyerror("Use of undeclared function");
    }
} '(' fn_args {
    if (!compare_no_of_args(current_function, no_of_args)) {
        yyerror("Mismatch in number of arguments");
    }
    no_of_args = 0;
} ')' ';'

fn_args : | fn_arg ;

fn_arg : fn_arg ',' IDENTIFIER 
{
    no_of_args++;
    char *symbol_data_type = (char *)calloc(20,sizeof(char));
    if (lookup_symbol_table(current_identifier, current_scope) == 0){
        yyerror("Undeclared Variable used in function call");
    } else {
        symbol_data_type = data_type_of_symbol(current_identifier, current_scope);
    }
    switch(lookup_arg_list(current_function, current_identifier, symbol_data_type)) {
        case 0: yyerror ("Wrong arguments passed to the function"); break;
        case 1: yyerror ("Passing wrong type of argument"); break;
    }
} | IDENTIFIER {
    no_of_args++;
    char *symbol_data_type = (char *)calloc(20,sizeof(char));
    if (lookup_symbol_table(current_identifier, current_scope) == 0){
        yyerror("Undeclared Variable used in function call");
    } else {
        symbol_data_type = data_type_of_symbol(current_identifier, current_scope);
    }
    switch(lookup_arg_list(current_function, current_identifier, symbol_data_type)) {
        case 0: yyerror ("Wrong arguments passed to the function"); break;
        case 1: yyerror ("Passing wrong type of argument"); break;
    }
} ;

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

expn_statement : expn { isExpn = true; }';' 
               | {} ';' ;

return_statement : RETURN { isReturn = true; } expn_statement 
{
    if ((strcmp(current_return_type, "void") == 0) && isReturn && isExpn) {
        yyerror("Void function returning a value");
    }
};

break_statement : BREAK ';' ;

labelled_statement : CASE primary_expn ':' statements 
                   | DEFAULT ':' statements ;

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
        push_symbol(current_identifier, current_data_type, current_scope, current_line_no, current_opening_brace_line_no, 0); 
    }  
             | INTEGER_CONSTANT 
             | REAL_CONSTANT 
             | STRING_CONSTANT 
             | CHAR_CONSTANT 
             | '(' expn ')' ;

// Variable Declaration
variable_decl : data_type var_list {
    while (stack_top != -1){
        symbolStack sym = stk[stack_top];
        if (sym.opening_boundary_line_no < peek()) { break; }
        insert_into_symbol_table(sym.symbol_name, sym.data_type, sym.scope, sym.line_no, sym.opening_boundary_line_no, sym.isArray, sym.arraySize);
        stack_top--;
    }
} ';' ;

var_list : var_list ',' assignment_expn 
         | var_list ',' array_init
         | array_init 
         | assignment_expn ;

array_init : IDENTIFIER {
    push_symbol(current_identifier, current_data_type, current_scope,current_line_no, current_opening_brace_line_no, 1);  
} '[' array_index ']' ;

array_index : IDENTIFIER | INTEGER_CONSTANT {
    update_array_size(current_value);
};

data_type : INT 
          | CHAR 
          | DOUBLE 
          | FLOAT ;

%%

void print_constant_table();

void yyerror(const char *s) {
    printf ("ERROR: %s at line %d\n", s, current_line_no);
    exit(1);
}
void error (const char *s, int line_no){
    printf ("ERROR: %s at line %d\n", s, line_no);
    exit(1);
}

int main(){
    int n = yyparse();
    if (!n){
        printf("\nSUCCESS\n");
        printf ("\n=================================================\n");
        printf ("\n\t\tSYMBOL TABLE \n\n");
        printf ("  Symbol\tType\tScope\tBound\tLine No\tArray?\tArray_size\n");
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