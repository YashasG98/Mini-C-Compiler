%{
    void yyerror(char *s);
    #include "y.tab.h"
    #include "constant_table.h"
    int line_count = 1;

    char current_identifier[35];
    char current_scope[35];
    char current_data_type[20];
    char current_value[20];
    int current_line_no;
    int current_opening_brace_line_no;
    int current_closing_brace_line_no;
%}

%x COMMENT

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
STRING_CONSTANT \"(.)*\"
PRE_PROCESSOR_DIRECTIVE (#define[ \t]*([a-zA-Z0-9]+)[ \t]([a-zA-Z0-9]+))|(#include[ \t]*<{ALPHA}*.h>)|(#include[ \t]*"{ALPHA}*.h")
SINGLE_LINE_COMMENT "//"(.)*

%%

{WHITESPACES} ;
[,;():] return *yytext;
"{" {
    current_opening_brace_line_no = line_count;
    return *yytext;
}
"}" {
    current_closing_brace_line_no = line_count;
    return *yytext;
}
{PRE_PROCESSOR_DIRECTIVE} {return PRE_PROCESSOR_DIRECTIVE;}
{SINGLE_LINE_COMMENT} ;
[-+]?{DECI} {
    insert_into_constant_table(yytext,"INTEGER CONSTANT",line_count);
    strcpy(current_value, yytext);
    return INTEGER_CONSTANT;
}
[-+]?{REAL} {
    insert_into_constant_table(yytext,"REAL CONSTANT",line_count);
    return REAL_CONSTANT;
}
[<<]|[>>] {return SHIFT_OP;}
{EQUALITY_OPERATORS} {return EQUALITY_OP;}
{RELATIONAL_OPERATORS} {return REL_OP;}
{ASSIGNMENT_OPERATORS} {return ASSIGN_OP;}
{INCREMENT_OPERATOR} {return INCREMENT_OPERATOR;}
{DECREMENT_OPERATOR} {return DECREMENT_OPERATOR;}
{UNARY_OPERATORS} {return UNARY_OP;}
{ADD_OP} {return ADD_OP;}
{MUL_OP} {return MUL_OP;}
{STRING_CONSTANT} {
    insert_into_constant_table (yytext, "STRING_CONSTANT", line_count);
    return STRING_CONSTANT;
}
(\'{ALPHA}\')|(\'(\\)[a-z]\') {
    insert_into_constant_table(yytext, "CHAR_CONSTANT",line_count); 
    return CHAR_CONSTANT;
}
\'(.)(.)(.)+\' {yyerror ("Illegal character constant"); return 0;} 
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
"printf" {return PRINTF;}
"scanf" {return SCANF;}
"void" {return VOID;}

{IDENTIFIER} {
    strcpy(current_identifier,yytext); 
    return IDENTIFIER;
}
[\n] {
    line_count++;
    current_line_no = line_count;
}

"/*" { BEGIN COMMENT; }
<COMMENT>. ; 
<COMMENT>\n {line_count++;}
<COMMENT>"/*" {printf ("warning: beginning nested comment on line %d", line_count);}
<COMMENT>"*/" { BEGIN INITIAL; }
<COMMENT><<EOF>> { yyerror("Comment left unclosed"); return 0;}
"*/".* {yyerror("Unopened comment closed wrongly"); return 0;}
{DECI}+[.]?({ALPHA}|{DECI})* {yyerror("Illegal Identifier"); return 0;}

(.?) {
    if (yytext[0] == '#') yyerror("Incomplete Pre-processor-directive");
    else if (yytext[0] == '"') yyerror ("Unclosed string");
    else yyerror (NULL);
    return 0;   
}

%%
int yywrap(void) {return 1;}