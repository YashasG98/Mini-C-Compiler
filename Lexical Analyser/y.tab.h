#ifndef _Y_TAB_H
#define _Y_TAB_H

#define KEYWORD 300
#define ID 301
#define INT_NUM 302
#define FLOAT_NUM 303
#define STRING 304
#define OPERATOR 305
#define SINGLE_COMM 306
#define MULTI_COMM 307
#define PRE_PROC_DIREC 308

int yylex(void);
typedef union{
    char *string;
    int integer;
} yylType;

#endif