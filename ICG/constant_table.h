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

int chash(char *str)
{
    unsigned int hash = 7381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;
    return hash % TABLE_SIZE;
}

/*
    
    The following section contains the defintion for the constant table
    The symbol table is a hash table of fixed size (as defined by TABLE_SIZE)
    The table contains the following entires: 
    Constant Table(value, type_of_constant, line_of_defintion)
    The constant table is updated on receipt of a constant anywhere in the code

*/
typedef struct constantTable
{
    char value[100];
    char type_of_constant[100];
    int line_no;
    int length;
} constantTable;

constantTable cTable[TABLE_SIZE];

/*

    A function to insert an element to the constant table
    params: value, type_of_constant, line_no
    output: void, inserts element into the table at the hash value of value

*/
void insert_into_constant_table(char *value, char *type_of_constant, int line_no)
{
    int hash_value = chash(value);
    if (cTable[hash_value].length == 0)
    {
        strcpy(cTable[hash_value].value, value);
        strcpy(cTable[hash_value].type_of_constant, type_of_constant);
        cTable[hash_value].length = strlen(value);
        cTable[hash_value].line_no = line_no;
        return;
    }
    int pos = 0;

    for (int i = hash_value + 1; i != hash_value; i = (i + 1) % TABLE_SIZE)
    {
        if (cTable[i].length == 0)
        {
            pos = i;
            break;
        }
    }

    strcpy(cTable[pos].value, value);
    strcpy(cTable[pos].type_of_constant, type_of_constant);
    cTable[pos].length = strlen(value);
    cTable[pos].line_no = line_no;
}

/*

    A utility function to print the contents of the constant table
    params: void
    output: void

*/
void print_constant_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (cTable[i].length == 0)
            continue;
        else
            printf("  %d\t\t|%s\t\t|%s\n", cTable[i].line_no, cTable[i].type_of_constant, cTable[i].value);
    }
}