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
    extern int assign_op_choice;
    extern int rel_op_choice;
    extern int equality_op_choice;
    extern int unary_op_choice;
    extern int add_op_choice;
    extern int mul_op_choice;
    extern int shift_op_choice;

    typedef struct Stack {
        char value[100];
        int label_value;
    } icg_stack;

    icg_stack icg_symbol_stack[100], icg_label_stack[100];

    int icg_symbol_stack_top = -1;
    int icg_label_stack_top = -1;

    void icg_push_symbol_stack(char *s) {
        if (icg_label_stack_top == 100) return;
        strcpy(icg_symbol_stack[++icg_symbol_stack_top].value,s);
    }

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

    int temp_count = 0, label_count = 0;
    char temp[5];

    void gen_constant_expn() {
        snprintf (temp, 5, "t%d", temp_count++);
        printf ("%s = %s\n", temp, current_value);
        icg_push_symbol_stack(temp);
    }

    void gen_expn() {
        snprintf (temp, 5, "t%d", temp_count++);
        printf ("%s = %s %s %s\n", temp, icg_symbol_stack[icg_symbol_stack_top-2].value, icg_symbol_stack[icg_symbol_stack_top].value, icg_symbol_stack[icg_symbol_stack_top-1].value);
        icg_symbol_stack_top -= 3;
        icg_push_symbol_stack(temp);
    }

    void gen_assignment_expn(int assign_op_choice) {
        if (assign_op_choice) {
            snprintf (temp, 5, "t%d", temp_count++);
            switch (assign_op_choice) {
                case 1: printf ("%s = %s + %s\n", temp, icg_symbol_stack[icg_symbol_stack_top-2].value, icg_symbol_stack[icg_symbol_stack_top-1].value); break;
                case 2: printf ("%s = %s - %s\n", temp, icg_symbol_stack[icg_symbol_stack_top-2].value, icg_symbol_stack[icg_symbol_stack_top-1].value); break;
                case 3: printf ("%s = %s * %s\n", temp, icg_symbol_stack[icg_symbol_stack_top-2].value, icg_symbol_stack[icg_symbol_stack_top-1].value); break;
                case 4: printf ("%s = %s / %s\n", temp, icg_symbol_stack[icg_symbol_stack_top-2].value, icg_symbol_stack[icg_symbol_stack_top-1].value); break;
                case 5: printf ("%s = %s %% %s\n", temp, icg_symbol_stack[icg_symbol_stack_top-2].value, icg_symbol_stack[icg_symbol_stack_top-1].value); break;
                case 6: printf ("%s = %s << %s\n", temp, icg_symbol_stack[icg_symbol_stack_top-2].value, icg_symbol_stack[icg_symbol_stack_top-1].value); break;
                case 7: printf ("%s = %s >> %s\n", temp, icg_symbol_stack[icg_symbol_stack_top-2].value, icg_symbol_stack[icg_symbol_stack_top-1].value); break;
            }
            icg_symbol_stack_top -= 2;
            icg_push_symbol_stack(temp);
            icg_push_symbol_stack("=");
        } 
        printf ("%s = %s\n", icg_symbol_stack[icg_symbol_stack_top-2].value, icg_symbol_stack[icg_symbol_stack_top-1].value);
        icg_symbol_stack_top -= 3;
    }

    void gen_inc_expn() {
        icg_symbol_stack_top--;
        icg_push_symbol_stack("1");
        icg_push_symbol_stack("+=");
        gen_assignment_expn(1);  
    }

    void gen_dec_expn() {
        icg_symbol_stack_top--;
        icg_push_symbol_stack("1");
        icg_push_symbol_stack("-=");
        gen_assignment_expn(2);
    }

    void gen_unary_expn() {
        printf ("%s = %s %s\n", icg_symbol_stack[icg_symbol_stack_top-1].value, icg_symbol_stack[icg_symbol_stack_top].value, icg_symbol_stack[icg_symbol_stack_top-1].value);
        icg_symbol_stack_top -= 2;
    }

    void gen_if_statement() {
        snprintf (temp, 5, "L%d", label_count);
        printf ("IF NOT %s GOTO %s\n", icg_symbol_stack[icg_symbol_stack_top].value, temp);
        icg_label_stack[++icg_label_stack_top].label_value = label_count++;
        icg_symbol_stack_top--;
    }

    void gen_if_block() {
        snprintf (temp, 5, "L%d", label_count);
        printf ("GOTO %s\n", temp);
        snprintf (temp, 5, "L%d", icg_label_stack[icg_label_stack_top].label_value);
        printf ("%s:\n", temp);
        icg_label_stack_top--;
        icg_label_stack[++icg_label_stack_top].label_value = label_count++;
    }

    void gen_else_block() {
        snprintf (temp, 5, "L%d", icg_label_stack[icg_label_stack_top].label_value);
        printf ("%s:\n", temp);
        icg_label_stack_top--;
    }

    void start_while_block() {
        snprintf (temp, 5, "L%d", label_count);
        printf ("%s:\n", temp);
        icg_label_stack[++icg_label_stack_top].label_value = label_count++;
    }

    void gen_while_block() {
        snprintf (temp, 5, "L%d", icg_label_stack[icg_label_stack_top-1].label_value);
        printf ("GOTO %s\n", temp);
        snprintf (temp, 5, "L%d", icg_label_stack[icg_label_stack_top].label_value);
        printf ("%s:\n", temp);
        icg_label_stack_top -= 2;
    }

    void start_function_block() {
        printf ("func begin %s\n", current_scope);
    }

    void end_function_block() {
        printf ("func end\n");
    }

    void function_call_end() {
        printf ("refparam result\n");
        icg_push_symbol_stack("result");
        printf ("call %s, %d\n", current_function, no_of_args);
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
        start_function_block();
    } 
    '(' argsList ')' statements {end_function_block(); printf ("\n"); } 
    | VOID IDENTIFIER {
        strcpy (current_scope, current_identifier);
        strcpy (current_return_type, "void");
        insert_into_function_table (current_identifier, current_return_type, current_line_no);
    }
    '(' argsList ')' statements {end_function_block(); printf ("\n");} ;

argsList : args | ;

args : data_type IDENTIFIER  {
            insert_into_function_table_arg_list(current_scope, current_data_type, current_identifier);
        }
     | args ',' data_type IDENTIFIER {
            insert_into_function_table_arg_list(current_scope, current_data_type, current_identifier);
        }
     ;

main_fn : data_type MAIN {strcpy(current_scope, "main"); start_function_block();} '(' ')' statements {end_function_block(); printf ("\n");}
        | MAIN {strcpy(current_scope, "main"); start_function_block(); } '(' ')' statements {end_function_block(); printf ("\n");}          
        | VOID MAIN {strcpy (current_scope, "main"); start_function_block();} '(' ')' statements {end_function_block(); printf ("\n");};

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
        stack_top--;
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
} ')' {
    function_call_end();
    no_of_args = 0;
} ';'

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
    printf ("refparam %s\n", current_identifier);
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
    printf ("refparam %s\n", current_identifier);
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
               | { isExpn = false; } ';' ;

return_statement : RETURN { isReturn = true; } expn_statement 
{
    if ((strcmp(current_return_type, "void") == 0) && isReturn && isExpn) {
        yyerror("Void function returning a value");
    } else if (isReturn && !isExpn && current_return_type[0]!='v') {
        yyerror("Non-void function returning a void value");
    }
    if (current_return_type[0] != 'v') {
        printf ("return %s\n", icg_symbol_stack[icg_symbol_stack_top].value);
        icg_symbol_stack_top--;    
    } else {
        printf ("return\n");
    }

};

break_statement : BREAK ';' ;

labelled_statement : CASE primary_expn ':' statements 
                   | DEFAULT ':' statements ;

selection_statement : IF '(' expn ')' {
                        if ($3 < 0) {
                            yyerror ("Invalid IF check");
                        } 
                        gen_if_statement();
                    } statements {gen_if_block();} else_block
                    | SWITCH '(' expn ')' statements ;
                
else_block : ELSE statements {gen_else_block();}
           | {gen_else_block(); };

// looping constructs
looping_constructs : while_loop 
                   | do_while_loop 
                   | for_loop;

while_loop : WHILE '(' {start_while_block(); } cond_exp {
                if ($3 < 0) {
                    yyerror ("Invalid WHILE check");
                }
                gen_if_statement();
            } ')' statements {gen_while_block();};

do_while_loop : {start_while_block();} DO statements WHILE '(' cond_exp {
    if ($5 < 0) {
        yyerror ("Invalid DO-WHILE check");
    } 
    gen_if_statement();
    gen_while_block();
} ')' ';' ;

for_loop : FOR '(' expn1 ';' {start_while_block(); } expn1 {
    if ($5 < 0) {
        yyerror ("Invalid FOR check");
    }
    gen_if_statement();
}';' expn1 ')' statements {gen_while_block();}

expn1 : expn | ;

// Expression hierarchy
expn : assignment_expn { $$ = $1; }
     | expn ',' assignment_expn { 
        if (($1 == $3) && ($1 != -1)){
            $$ = $1;
        } else {
            yyerror ("Invalid Expression");
        }
     } ;

assignment_expn : cond_exp { $$ = $1; }
                | unary_expn ASSIGN_OP assignment_expn {
                    if (($1 == $3) && ($1 != -1)) {
                        $$ = $1;
                    } else if ($1 != $3){
                        yyerror ("Type Mismatch");
                    } else if ($1 == -1) {
                        yyerror ("Invalid String Assignment");
                    }
                    switch (assign_op_choice) {
                        case 0: icg_push_symbol_stack("="); break;
                        case 1: icg_push_symbol_stack("+="); break;
                        case 2: icg_push_symbol_stack("-="); break;
                        case 3: icg_push_symbol_stack("*="); break;
                        case 4: icg_push_symbol_stack("/="); break;
                        case 5: icg_push_symbol_stack("%="); break;
                        case 6: icg_push_symbol_stack("<<="); break;
                        case 7: icg_push_symbol_stack(">>="); break;
                    }
                    gen_assignment_expn(assign_op_choice);
                };

cond_exp : logical_or_expn { $$ = $1; } ;

logical_or_expn : logical_and_expn { $$ = $1; }
                | logical_or_expn LOG_OR logical_and_expn {
                    if (($1 == $3) && ($1 != -1)) {
                        $$ = $1;
                        icg_push_symbol_stack("||");
                        gen_expn();
                    } else {
                        yyerror ("Invalid Logical OR Expression");
                    }
                };

logical_and_expn : equality_expn { $$ = $1; }
                 | logical_and_expn LOG_AND equality_expn {
                    if (($1 == $3) && ($1 != -1)) {
                        $$ = $1;
                        icg_push_symbol_stack("&&");
                        gen_expn();
                    } else {
                        yyerror ("Invalid Logical AND Expression");
                    }
                 };

equality_expn : relational_expn { $$ = $1; }
              | equality_expn EQUALITY_OP relational_expn {
                    if (($1 == $3) && ($1 != -1)) {
                        $$ = $1;
                        switch (equality_op_choice) {
                            case 0: icg_push_symbol_stack ("=="); break;
                            case 1: icg_push_symbol_stack ("!="); break;
                        }
                        gen_expn();
                    } else {
                        yyerror ("Invalid Equality Expression");
                    }
              };

relational_expn : shift_expn { $$ = $1; }
                | relational_expn REL_OP shift_expn {
                    if (($1 == $3) && ($1 != -1)) {
                        $$ = $1;
                        switch (rel_op_choice) {
                            case 0: icg_push_symbol_stack("<"); break;
                            case 1: icg_push_symbol_stack(">"); break;
                            case 2: icg_push_symbol_stack("<="); break;
                            case 3: icg_push_symbol_stack(">="); break;
                        }
                        gen_expn();
                    } else {
                        yyerror ("Invalid Relational Expression");
                    }
                };

shift_expn : additive_expn { $$ = $1; }
            | shift_expn SHIFT_OP additive_expn {
                switch ($1 + $3) {
                    case 2 : $$ = 1; break;
                    case 1 : $$ = 0; break;
                    case 0 : ($1 == $3) ? $$ = 0 : yyerror ("Invalid String operations"); 
                                break;
                    case -1 :
                    case -2 : yyerror ("Invalid String operations"); 
                }
                switch (shift_op_choice) {
                    case 0: icg_push_symbol_stack("<<"); break;
                    case 1: icg_push_symbol_stack(">>"); break;
                }
                gen_expn();
            };

additive_expn : multiplicative_expn { $$ = $1; }
              | additive_expn ADD_OP multiplicative_expn {
                    switch ($1 + $3) {
                        case 2 : $$ = 1; break;
                        case 1 : $$ = 0; break;
                        case 0 : ($1 == $3) ? $$ = 0 : yyerror ("Invalid String operations"); 
                                    break;
                        case -1 :
                        case -2 : yyerror ("Invalid String operations"); 
                    }
                    switch (add_op_choice) {
                        case 0: icg_push_symbol_stack ("+"); break;
                        case 1: icg_push_symbol_stack ("-"); break;
                    }
                    gen_expn();
              };

multiplicative_expn : unary_expn { $$ = $1; }
                    | multiplicative_expn MUL_OP unary_expn { 
                        switch ($1 + $3) {
                            case 2 : $$ = 1; break;
                            case 1 : $$ = 0; break;
                            case 0 : ($1 == $3) ? $$ = 0 : yyerror ("Invalid String operations"); 
                                        break;
                            case -1 :
                            case -2 : yyerror ("Invalid String operations"); 
                        }
                        switch (mul_op_choice) {
                            case 0: icg_push_symbol_stack("*"); break;
                            case 1: icg_push_symbol_stack("/"); break;
                            case 2: icg_push_symbol_stack("%"); break;
                        }
                        gen_expn();
                    };

unary_expn : postfix_expn { $$ = $1; }
           | INCREMENT_OPERATOR {icg_push_symbol_stack("++"); gen_inc_expn();} unary_expn { $$ = $2; }
           | DECREMENT_OPERATOR {icg_push_symbol_stack("--"); gen_dec_expn();} unary_expn { $$ = $2; }
           | UNARY_OP postfix_expn { 
                $$ = $2;                 
                switch (unary_op_choice) {
                    case 0: icg_push_symbol_stack("&"); break;
                    case 1: icg_push_symbol_stack("~"); break; 
                    case 2: icg_push_symbol_stack("!"); break;
                }
                gen_unary_expn();
            };

postfix_expn : primary_expn { $$ = $1; }
             | postfix_expn INCREMENT_OPERATOR {icg_push_symbol_stack ("++"); $$ = $1; gen_inc_expn();}
             | postfix_expn DECREMENT_OPERATOR {icg_push_symbol_stack ("--"); $$ = $1; gen_dec_expn();};

primary_expn : IDENTIFIER   { 
        push_symbol(current_identifier, current_data_type, current_scope, current_line_no, current_opening_brace_line_no, 0); 
        icg_push_symbol_stack (current_identifier);
        char *symbol_data_type = (char *)calloc(20,sizeof(char));
        symbol_data_type = data_type_of_symbol(current_identifier, current_scope);
        if (symbol_data_type != NULL) {
            if ((strcmp(symbol_data_type, "int")==0) || (strcmp(symbol_data_type, "char")==0)){
                $$ = 1;
            } 
            else if ((strcmp(symbol_data_type, "float")==0) || (strcmp(symbol_data_type, "double")==0)) {
                $$ = 0;
            } else {
                $$ = -1;
            }
        }
    }  
             | INTEGER_CONSTANT { $$ = 1; gen_constant_expn(); }
             | REAL_CONSTANT { $$ = 0; gen_constant_expn(); }
             | STRING_CONSTANT { $$ = -1; }
             | CHAR_CONSTANT { $$ = 1; gen_constant_expn(); }
             | '(' expn ')' { $$ = $2; };

// Variable Declaration
variable_decl : data_type var_list {
    while (stack_top != -1){
        symbolStack sym = stk[stack_top];
        if (sym.opening_boundary_line_no < peek()) { break; }
        insert_into_symbol_table(sym.symbol_name, sym.data_type, sym.scope, sym.line_no, sym.opening_boundary_line_no, sym.isArray, sym.arraySize);
        stack_top--;
        icg_symbol_stack_top--;
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
        printf ("\n\t\t\t\t\t\tSYMBOL TABLE \n");
        printf ("  Symbol\t|    Type\t|    Scope\t|    Bound\t|    Line No\t|    Array?\t|    Array_size\n");
        print_symbol_table();
        printf ("\n");
        printf ("\n\t\t\t\tFUNCTION TABLE \n");
        printf ("  Name\t\t|    Return\t|    Line\t|    Args\t|    ArgList\n");
        print_function_table();
        printf ("\n");
        printf("\n\t\t\tCONSTANT TABLE \n");
        printf("  Line No\t|    Type of Constant\t\t|    Constant\n");
        print_constant_table();
    } 
    return 0;
}