#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "definitions.h"

typedef struct symbolTable{
    char name[100];
    char type[100];
    int length;
} symbolTable;

typedef struct constantTable{
    char name[100];
    char type[100];
    int length;
    int integer_value;
    double double_value;
    char *string_value;
} constantTable;

symbolTable sTable[1001];
constantTable cTable[1001];

int hash(char *str){
    unsigned int hash = 5381;
    int c;
    while (c=*str++)
        hash = ((hash<<5)+hash)+c;
    return hash%1001;
}

int lookup_symbol_table(char *str){
    int value = hash(str);
    if (sTable[value].length == 0) return 0;
    else if(strcmp(sTable[value].name,str) == 0) return 1;
    else {
        for (int i=value+1;i!=value; i=(i+1)%1001){
            if (strcmp(sTable[i].name,str) == 0) 
                return 1;
        }
        return 0;
    }
}

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

void insert_into_symbol_table(char *symbol, char *type){
    if(lookup_symbol_table(symbol)) return;
    else {
        int value = hash(symbol);
        if(sTable[value].length == 0){
            strcpy(sTable[value].name, symbol);
            strcpy(sTable[value].type, type);
            sTable[value].length = strlen(symbol);
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
        strcpy(sTable[pos].type,type);
        sTable[pos].length = strlen(symbol);
    }
}

void insert_into_constant_table(char *value, char *type, int type_code){
    if(lookup_symbol_table(value)) return;
    else {
        int hash_value = hash(value);
        if(cTable[hash_value].length == 0){
            strcpy(cTable[hash_value].name, value);
            strcpy(cTable[hash_value].type, type);
            cTable[hash_value].length = strlen(value);
            switch (type_code)
            {
                case DECIMAL: cTable[hash_value].integer_value = atoi(value); break;
                case REAL: cTable[hash_value].double_value = strtof(value,NULL); break;
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
        switch (type_code)
        {
            case DECIMAL: cTable[pos].integer_value = atoi(value); break;
            case REAL: cTable[pos].double_value = strtof(value,NULL); break;
            default: break;
        }
    }
}

void print_symbol_table(){
    for(int i=0;i<1001;i++){
        if(sTable[i].length == 0) continue;
        printf("%s\t-\t%s\n",sTable[i].name, sTable[i].type);
    }
}

void print_constant_table(){
    for(int i=0;i<1001;i++){
        if(cTable[i].length == 0) continue;
        else {
            if(cTable[i].integer_value != INT_MAX){
                printf ("%s\t-\t%s\t-\t%d\n",cTable[i].name, cTable[i].type, cTable[i].integer_value);
            } else if (cTable[i].double_value != INFINITY){
                printf ("%s\t-\t%s\t\t-\t%0.3f\n",cTable[i].name, cTable[i].type, cTable[i].double_value);
            } 
        }
    }
}
extern yylType yylVal;
int main(){
    int s;
    for(int i=0;i<1001;i++){
        cTable[i].integer_value = INT_MAX;
        cTable[i].double_value = INFINITY;
        cTable[i].string_value = NULL;
    }

    printf ("================================================\n");
    while ((s=yylex())){
        switch (s)
        {
            case KEYWORD: 
                printf("%s\t-\tKEYWORD\n",yylVal.string); 
                insert_into_symbol_table(yylVal.string,"KEYWORD");
                break;
            case IDENTIFIER: 
                printf("%s\t-\tIDENTIFIER\n",yylVal.string); 
                insert_into_symbol_table(yylVal.string,"IDENTIFIER");
                break;
            case SEPARATOR: 
                printf("%s\t-\tSEPARATOR\n",yylVal.string); 
                break;
            case BINARY_OPERATORS: 
                printf("%s\t-\tBINARY OPERATOR\n",yylVal.string); 
                break;
            case UNARY_OPERATORS: 
                printf("%s\t-\tUNARY OPERATOR\n",yylVal.string); 
                break;
            case COMPARISON_OPERATORS: 
                printf("%s\t-\tCOMPARISON OPERATOR\n",yylVal.string); 
                break;
            case ASSIGNMENT_OPERATOR: 
                printf("%s\t-\tASSIGNMENT OPERATOR\n",yylVal.string); 
                break;
            case DECIMAL: 
                printf("%s\t-\tDECIMAL CONSTANT\n",yylVal.string); 
                insert_into_constant_table(yylVal.string,"INTEGER CONSTANT", DECIMAL);
                break;
            case REAL: 
                printf("%s\t-\tREAL CONSTANT\n",yylVal.string); 
                insert_into_constant_table(yylVal.string,"REAL CONSTANT", REAL);
                break;
            default: break;
        }
    }
    printf ("=====================================================\n");
    printf("\n\nSYMBOL TABLE\n\n");
    print_symbol_table();
    printf("\n\n");
    printf ("=====================================================\n");
    printf("\n\nCONSTANT TABLE \n\n");
    print_constant_table();
}