%{
    #include<stdio.h>
    #include<string.h>
    #define TABLE_SIZE 1001
        
    int flag = 0;
    int yylex();
    void yyerror();
    extern int line_no;

    int hash(char *str){
        unsigned int hash = 7381;
        int c;
        while(c = *str++)
            hash = ((hash<<5)+hash) + c;
        return hash % TABLE_SIZE;
    }

    typedef struct symbolTable{
        char symbol_name[100];
        char data_type[100];
        char scope[100];
        int opening_boundary_line_no;
        int closing_boundary_line_no;
        int isArray;
        int arraySize;
        int length;
        int line_no;
    }symbolTable;

    symbolTable sTable[TABLE_SIZE];

    int lookup_symbol_table(char *str, char *current_scope){
        int value = hash(str);
        if(sTable[value].length == 0)
            return 0;
        else if(strcmp(sTable[value].symbol_name, str) == 0){
            if(strcmp(sTable[value].scope, current_scope) == 0)
                return 1;
            return 0;
        }else{
            for(int i = value+1;i!=value;i = (i+1)%TABLE_SIZE){
                if(strcmp(sTable[i].symbol_name, str) == 0)
                    return 1;
            }
            return 0;
        }
    }

    void insert_into_symbol_table(char *symbol, char *data_type, char *scope, int line_no, int opening_boundary_line_no){
        if(lookup_symbol_table(symbol, scope))
            return;
        int value = hash(symbol);
        if(sTable[value].length == 0){
            strcpy(sTable[value].symbol_name, symbol);
            strcpy(sTable[value].data_type, data_type);
            strcpy(sTable[value].scope, scope);
            sTable[value].opening_boundary_line_no = opening_boundary_line_no;
            sTable[value].line_no = line_no;
            sTable[value].length = strlen(symbol);
            sTable[value].isArray = 0;
            sTable[value].arraySize = 0;
            return;
        }
        int pos = 0;
        for(int i = value + 1;i!=value;i = (i+1)%TABLE_SIZE){
            if(sTable[i].length == 0){
                pos = i;
                break;
            }
        }
        strcpy(sTable[value].symbol_name, symbol);
        strcpy(sTable[value].data_type, data_type);
        strcpy(sTable[value].scope, scope);
        sTable[value].opening_boundary_line_no = opening_boundary_line_no;
        sTable[value].line_no = line_no;
        sTable[value].length = strlen(symbol);
        sTable[value].isArray = 0;
        sTable[value].arraySize = 0;
    }

    void insert_into_symbol_table_closing_line(char *scope,int opening_boundary_line_no,int closing_boundary_line_no)
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            if ((strcmp(sTable[i].scope, scope) == 0) 
                && sTable[i].opening_boundary_line_no == opening_boundary_line_no)
            {
                sTable[i].closing_boundary_line_no = closing_boundary_line_no;
            }
        }
    }

    void insert_into_symbol_table_array_identifier (char *symbol, char *data_type, char *scope, int line_no, int opening_boundary_line_no)
    {
        if (lookup_symbol_table(symbol, scope))
            return;
        else
        {
            int value = hash(symbol);
            if (sTable[value].length == 0)
            {
                strcpy(sTable[value].symbol_name, symbol);
                strcpy(sTable[value].data_type, data_type);
                strcpy(sTable[value].scope, scope);
                sTable[value].length = strlen(symbol);
                sTable[value].line_no = line_no;
                sTable[value].opening_boundary_line_no = opening_boundary_line_no;
                sTable[value].isArray = 1;
                return;
            }
            int pos = 0;

            for (int i = value + 1; i != value; i = (i + 1) % TABLE_SIZE)
            {
                if (sTable[i].length == 0)
                {
                    pos = i;
                    break;
                }
            }

            strcpy(sTable[pos].symbol_name, symbol);
            strcpy(sTable[pos].data_type, data_type);
            strcpy(sTable[pos].scope, scope);
            sTable[pos].line_no = line_no;
            sTable[pos].length = strlen(symbol);
            sTable[pos].opening_boundary_line_no = opening_boundary_line_no;
            sTable[pos].isArray = 1;
        }
    }

    void insert_into_symbol_table_array_size(char *identifier, char *array_size)
    {
        for (int i=0;i<1001;i++){
            if ((strcmp(sTable[i].symbol_name, identifier) == 0)
                                    && sTable[i].isArray == 1){
                sTable[i].arraySize = atoi(array_size);
                return;
            }
        }
    }

    void print_symbol_table()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            if (sTable[i].length == 0)
                continue;
            if (sTable[i].isArray){
                printf("  %s\t\t%s\t%s\t%d-%d\t%d\tYES\t%d\n", sTable[i].symbol_name, sTable[i].data_type, 
                                                    sTable[i].scope,
                                                    sTable[i].opening_boundary_line_no,
                                                    sTable[i].closing_boundary_line_no,
                                                    sTable[i].line_no,
                                                    sTable[i].arraySize);    
            } else {
                printf("  %s\t\t%s\t%s\t%d-%d\t%d\tNO\t\n", sTable[i].symbol_name, sTable[i].data_type, 
                                                sTable[i].scope,
                                                sTable[i].opening_boundary_line_no,
                                                sTable[i].closing_boundary_line_no,
                                                sTable[i].line_no);

            }
        }
    }
%}

%token PRE_PROC_DIRECTIVE
%token INT
%token FLOAT
%token CHAR
%token DOUBLE
%token MAIN
%token PRINTF
%token FOR
%token RETURN
%token IF
%token INTEGER_CONSTANT
%token FLOAT_CONSTANT
%token ARITH_OP
%token RELAT_OP
%token STRING_CONSTANT
%token IDENTIFIER
%start program

%%

program:                PRE_PROC_DIRECTIVE main_func;
main_func:              data_type MAIN '(' ')' '{' statements RETURN expn ';' '}';
statements:             decl_statement statements|looping_statement statements|selection_statement statements|print_statement statements|;
print_statement:        PRINTF '(' STRING_CONSTANT ')' ';';
selection_statement:    if_block;
if_block:               IF '(' expn RELAT_OP expn ')' if_body;
if_body:                '{' statements '}';
looping_statement:      for_loop;
for_loop:               FOR '(' initialization ';' exit_condition ';' updation ')' for_body;
initialization:         var_decl var_list|;
exit_condition:         expn RELAT_OP expn|;
updation:               IDENTIFIER '=' expn|;
for_body:               '{' statements '}';
decl_statement:         data_type var_decl var_list ';';
var_list:               ',' var_decl var_list |;
var_decl:               IDENTIFIER '=' expn|IDENTIFIER;
expn:                   expn ARITH_OP operand|operand;
operand:                IDENTIFIER|FLOAT_CONSTANT|INTEGER_CONSTANT;
data_type:              INT|FLOAT|CHAR|DOUBLE;

%%

void main(){
    yyparse();
    if(flag==0)
        printf("Valid program.\n");
     printf ("\n\t\tSYMBOL TABLE \n\n");
        printf ("  Symbol\tType\tScope\tBound\tLine No\tArray?\tArray_size\n");
        print_symbol_table();
        printf("\n\t\tCONSTANT TABLE \n\n");
        printf("  Line No\tType of Constant\tConstant\n");
    print_constant_table();
}

void yyerror(){
    flag = 1;
    printf("Invalid program. Error at line number %d.\n",line_no);
}