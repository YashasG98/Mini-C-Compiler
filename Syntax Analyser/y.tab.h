/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    MAIN = 258,
    INT = 259,
    CHAR = 260,
    FLOAT = 261,
    DOUBLE = 262,
    IDENTIFIER = 263,
    PRE_PROCESSOR_DIRECTIVE = 264,
    REAL_CONSTANT = 265,
    INTEGER_CONSTANT = 266,
    STRING_CONSTANT = 267,
    CHAR_CONSTANT = 268,
    IF = 269,
    ELSE = 270,
    NOT_OP = 271,
    FOR = 272,
    WHILE = 273,
    DO = 274,
    LOG_AND = 275,
    LOG_OR = 276,
    EQUALITY_OP = 277,
    REL_OP = 278,
    SHIFT_OP = 279,
    ADD_OP = 280,
    MUL_OP = 281,
    ASSIGN_OP = 282,
    UNARY_OP = 283,
    RETURN = 284,
    BREAK = 285,
    DEFAULT = 286,
    CASE = 287,
    SWITCH = 288,
    INCREMENT_OPERATOR = 289,
    DECREMENT_OPERATOR = 290,
    PRINTF = 291,
    SCANF = 292,
    VOID = 293
  };
#endif
/* Tokens.  */
#define MAIN 258
#define INT 259
#define CHAR 260
#define FLOAT 261
#define DOUBLE 262
#define IDENTIFIER 263
#define PRE_PROCESSOR_DIRECTIVE 264
#define REAL_CONSTANT 265
#define INTEGER_CONSTANT 266
#define STRING_CONSTANT 267
#define CHAR_CONSTANT 268
#define IF 269
#define ELSE 270
#define NOT_OP 271
#define FOR 272
#define WHILE 273
#define DO 274
#define LOG_AND 275
#define LOG_OR 276
#define EQUALITY_OP 277
#define REL_OP 278
#define SHIFT_OP 279
#define ADD_OP 280
#define MUL_OP 281
#define ASSIGN_OP 282
#define UNARY_OP 283
#define RETURN 284
#define BREAK 285
#define DEFAULT 286
#define CASE 287
#define SWITCH 288
#define INCREMENT_OPERATOR 289
#define DECREMENT_OPERATOR 290
#define PRINTF 291
#define SCANF 292
#define VOID 293

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
