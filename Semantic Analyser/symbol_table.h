/*
    Authors     - Shashwatha Mitra G B (171CO144)
                  Yashas G (171CO154)
                  Prajwal S Belgavi (171CO229)

    Date        - 23/02/2020
    Description - Hash Table definitions
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#define TABLE_SIZE 1001

int hash(char *str)
{
    unsigned int hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;
    return hash % TABLE_SIZE;
}

typedef struct symbolStack {
    char symbol_name[100];
    char data_type[100];
    char scope[100];    
    int opening_boundary_line_no;
    int isArray;
    int arraySize;
    int line_no;
} symbolStack;

int stack_top = -1;

symbolStack stk[TABLE_SIZE];

void push_symbol(char *symbol, char *data_type,
                 char *scope, int line_no,
                 int opening_boundary_line_no,
                 int isArray) {

    stack_top++;
    if (stack_top != (TABLE_SIZE-1)) {
        strcpy(stk[stack_top].symbol_name, symbol);
        strcpy(stk[stack_top].data_type, data_type);
        strcpy(stk[stack_top].scope, scope);
        stk[stack_top].opening_boundary_line_no = opening_boundary_line_no;
        stk[stack_top].line_no = line_no;
        stk[stack_top].isArray = isArray;
    } else {
        printf ("Symbol Stack full\n");
        return;
    }
}

void update_array_size(char *arraySize) {
    stk[stack_top].arraySize = atoi(arraySize);
}

/*
    
    The following section contains the defintion for the symbol table
    The symbol table is a hash table of fixed size (as defined by TABLE_SIZE)
    The table contains the following entires: 
    Symbol Table(symbol_name, data_type, scope, opening_boundary, closing_boundary, line_of_defintion)
    The symbol table is updated on receipt of an Identifier that is not a function.

*/

typedef struct symbolTable
{
    char symbol_name[100];
    char data_type[100];
    char scope[100];
    int opening_boundary_line_no;
    int closing_boundary_line_no;
    int isArray;
    int arraySize;
    int length;
    int line_no;
} symbolTable;

symbolTable sTable[TABLE_SIZE];

/*

    A standard lookup function to check if identifier is already in the table
    params: identifier and current scope
    output: 0 if not found
            1 if found

*/
int lookup_symbol_table(char *str, char *current_scope)
{
    int value = hash(str);
    if (sTable[value].length == 0)
    {
        return 0;
    }
    else if (strcmp(sTable[value].symbol_name, str) == 0)
    {
        if (strcmp(sTable[value].scope, current_scope) == 0)
            return 1;
        for (int i = value + 1; i != value; i = (i + 1) % TABLE_SIZE)
        {
            if (strcmp(sTable[i].symbol_name, str) == 0) {
                if (strcmp(sTable[i].scope, current_scope) == 0){
                    return 1;
                }
                return 0;
            }
        }
        return 0;
    }
}

/*

    A function to insert an element to the symbol table
    params: symbol, data_type, scope, line_no, and opening_boundary
    output: void, inserts element into the table at the hash value of symbol

*/
void insert_into_symbol_table(char *symbol, char *data_type,
                              char *scope, int line_no,
                              int opening_boundary_line_no, 
                              int isArray, int arraySize)
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
            sTable[value].isArray = isArray;
            sTable[value].arraySize = arraySize;
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
        sTable[pos].isArray = isArray;
        sTable[pos].arraySize = arraySize;
    }
}

char *data_type_of_symbol(char *symbol, char *scope){
    for (int i=0;i<TABLE_SIZE;i++){
        if ((strcmp(sTable[i].symbol_name, symbol)==0) && (strcmp(sTable[i].scope, scope)==0)){
            return sTable[i].data_type;
        }
    }
}

/*

    A function to define the boundaries of an identifier
    params: scope, last opening brace, closing brace
    output: void, defines the boundary of the identifier declared from the last opening brace

*/
void insert_into_symbol_table_closing_line(char *scope,
                                           int opening_boundary_line_no,
                                           int closing_boundary_line_no)
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

/*

    A utility function to print the contents of the symbol table
    params: void
    output: void

*/
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

/*
    
    The following section contains the defintion for the function table
    The symbol table is a hash table of fixed size (as defined by TABLE_SIZE)
    The table contains the following entires: 
    Function Table(fn_name, return_type, line_of_defintion, no of arguements, arguement list)
    The symbol table is updated on receipt of an Identifier that is not a function.

*/
typedef struct functionTable
{
    char name[40];
    char return_type[20];
    symbolTable arg_list[20];
    int no_of_args;
    int line_no;
    int length;
} functionTable;

functionTable fTable[TABLE_SIZE];

/*

    A standard lookup function to check if function name is already in the table
    params: function name
    output: 0 if not found
            1 if found

*/
int lookup_function_table(char *str)
{
    int value = hash(str);
    if (fTable[value].length == 0)
        return 0;
    else if (strcmp(fTable[value].name, str) == 0)
        return 1;
    else
    {
        for (int i = value + 1; i != value; i = (i + 1) % TABLE_SIZE)
        {
            if (strcmp(fTable[i].name, str) == 0)
                return 1;
        }
        return 0;
    }
}

/*

    A function to insert an element to the function table
    params: name, return_type, line_no
    output: void, inserts element into the table at the hash value of name

*/
void insert_into_function_table(char *name, char *return_type, int line_no)
{
    if (lookup_function_table(name))
        return;
    else
    {
        int value = hash(name);
        if (fTable[value].length == 0)
        {
            strcpy(fTable[value].name, name);
            strcpy(fTable[value].return_type, return_type);
            fTable[value].length = strlen(name);
            fTable[value].line_no = line_no;
            fTable[value].no_of_args = 0;
            return;
        }
        int pos = 0;

        for (int i = value + 1; i != value; i = (i + 1) % TABLE_SIZE)
        {
            if (fTable[i].length == 0)
            {
                pos = i;
                break;
            }
        }

        strcpy(fTable[pos].name, name);
        strcpy(fTable[pos].return_type, return_type);
        fTable[pos].line_no = line_no;
        fTable[pos].length = strlen(name);
        fTable[pos].no_of_args = 0;
    }
}

/*

    A function to maintain the arguements for a function
    params: name, data_type of arguement, identifier
    output: void, inserts element into the arguement list based on value of no_of_args

*/
void insert_into_function_table_arg_list(char *function_name, char *data_type, char *identifier)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (strcmp(fTable[i].name, function_name) == 0)
        {
            int j = fTable[i].no_of_args++;
            strcpy(fTable[i].arg_list[j].symbol_name, identifier);
            strcpy(fTable[i].arg_list[j].data_type, data_type);
            strcpy(fTable[i].arg_list[j].scope, function_name);
            fTable[i].arg_list[j].length = strlen(identifier);
            return;
        }
    }
}

int lookup_arg_list(char *function, char *symbol, char *data_type) {
    for (int i=0;i<TABLE_SIZE;i++){
        if (strcmp(fTable[i].name, function) == 0) {
            for (int j=0;j<fTable[i].no_of_args;j++){
                if (strcmp(fTable[i].arg_list[j].symbol_name, symbol) == 0) {
                    if (strcmp(fTable[i].arg_list[j].data_type, data_type) == 0) {
                        return 2;
                    } 
                    return 1;
                }
            }
            return 0;
        }
    }
}

int compare_no_of_args(char *function, int no_of_args) {
    int value = hash(function);
    return (fTable[value].no_of_args == no_of_args);
}

/*

    A utility function to print the contents of the function table
    params: void
    output: void

*/
void print_function_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (fTable[i].length == 0)
            continue;
        else
        {
            printf("  %s\t%s\t%d\t%d\t", fTable[i].name, fTable[i].return_type, 
                                         fTable[i].line_no, fTable[i].no_of_args);
            for (int j = 0; j < fTable[i].no_of_args; j++)
            {
                printf("%s %s, ", fTable[i].arg_list[j].data_type, fTable[i].arg_list[j].symbol_name);
            }
            printf("\n");
        }
    }
}