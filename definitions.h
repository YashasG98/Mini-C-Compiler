#ifndef _Y_TAB_H

#define _Y_TAB_H

#define KEYWORD 300
#define IDENTIFIER 301
#define SEPARATOR 302
#define BINARY_OPERATORS 303
#define UNARY_OPERATORS 304
#define COMPARISON_OPERATORS 305
#define ASSIGNMENT_OPERATOR 306
#define DECIMAL 307
#define REAL 308
#define NEWLINE 309

typedef union {
    char *string;
} yylType;

#endif