#ifndef _Y_TAB_H

#define _Y_TAB_H

#define KEYWORD 300
#define IDENTIFIER 301
#define SEPARATOR 302
#define ARITH_OPERATORS 303
#define LOGICAL_OPERATORS 304
#define BITWISE_OPERATORS 313
#define RELATIONAL_OPERATORS 305
#define ASSIGNMENT_OPERATORS 306
#define DECIMAL 307
#define REAL 308
#define STRING 309
#define NEWLINE 310
#define PREPROCESSOR_DIRECTIVE 311
#define SLC 312

typedef union {
    char *string;
} yylType;

#endif