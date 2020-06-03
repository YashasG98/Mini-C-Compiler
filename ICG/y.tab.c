/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

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

#line 244 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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

/* Copy the second part of user declarations.  */

#line 371 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
# define YYCOPY_NEEDED 1
#endif


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   252

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  132
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  233

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      39,    40,     2,     2,    41,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    45,    44,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    46,     2,    47,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    42,     2,    43,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   196,   196,   198,   199,   201,   202,   203,   205,   205,
     212,   212,   219,   219,   221,   224,   229,   229,   230,   230,
     231,   231,   233,   234,   238,   239,   238,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   268,   273,   277,   268,
     282,   282,   284,   298,   313,   314,   316,   317,   319,   319,
     321,   323,   323,   325,   326,   328,   329,   331,   331,   332,
     334,   334,   343,   345,   346,   348,   353,   348,   354,   356,
     357,   360,   361,   362,   364,   364,   364,   371,   371,   371,
     379,   379,   379,   386,   386,   389,   390,   398,   399,   420,
     422,   423,   433,   434,   444,   445,   458,   459,   474,   475,
     491,   492,   508,   509,   526,   527,   527,   528,   528,   529,
     539,   540,   541,   543,   559,   560,   561,   562,   563,   566,
     566,   576,   577,   578,   579,   581,   581,   585,   585,   589,
     590,   591,   592
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MAIN", "INT", "CHAR", "FLOAT", "DOUBLE",
  "IDENTIFIER", "PRE_PROCESSOR_DIRECTIVE", "REAL_CONSTANT",
  "INTEGER_CONSTANT", "STRING_CONSTANT", "CHAR_CONSTANT", "IF", "ELSE",
  "NOT_OP", "FOR", "WHILE", "DO", "LOG_AND", "LOG_OR", "EQUALITY_OP",
  "REL_OP", "SHIFT_OP", "ADD_OP", "MUL_OP", "ASSIGN_OP", "UNARY_OP",
  "RETURN", "BREAK", "DEFAULT", "CASE", "SWITCH", "INCREMENT_OPERATOR",
  "DECREMENT_OPERATOR", "PRINTF", "SCANF", "VOID", "'('", "')'", "','",
  "'{'", "'}'", "';'", "':'", "'['", "']'", "$accept", "program",
  "pre_processor_section", "global_decl", "global_fn_decl", "$@1", "$@2",
  "argsList", "args", "main_fn", "$@3", "$@4", "$@5",
  "user_defined_fn_decl", "compound_statement", "$@6", "$@7", "statements",
  "function_call", "$@8", "$@9", "$@10", "fn_args", "fn_arg",
  "io_statements", "printf_statement", "printf_args", "scanf_statement",
  "scanf_args", "local_decl", "statement_list", "expn_statement", "$@11",
  "return_statement", "$@12", "break_statement", "labelled_statement",
  "selection_statement", "$@13", "$@14", "else_block",
  "looping_constructs", "while_loop", "@15", "$@16", "do_while_loop",
  "$@17", "$@18", "for_loop", "@19", "$@20", "expn1", "expn",
  "assignment_expn", "cond_exp", "logical_or_expn", "logical_and_expn",
  "equality_expn", "relational_expn", "shift_expn", "additive_expn",
  "multiplicative_expn", "unary_expn", "@21", "@22", "postfix_expn",
  "primary_expn", "variable_decl", "$@23", "var_list", "array_init",
  "$@24", "array_index", "data_type", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,    40,
      41,    44,   123,   125,    59,    58,    91,    93
};
# endif

#define YYPACT_NINF -186

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-186)))

#define YYTABLE_NINF -126

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -186,     6,     8,  -186,  -186,    20,  -186,  -186,  -186,  -186,
    -186,    12,  -186,  -186,  -186,    25,   -20,  -186,  -186,    44,
    -186,    -7,  -186,  -186,  -186,  -186,   146,  -186,  -186,   205,
    -186,  -186,     0,    11,    22,    19,    39,    40,    50,    45,
      -5,  -186,     5,  -186,    43,    52,    57,    77,  -186,    90,
      60,    62,    59,  -186,    -5,   205,   205,    21,  -186,   205,
     205,   205,   205,   205,   205,   205,   205,  -186,  -186,   213,
      66,   170,    71,    74,  -186,    72,    74,    46,  -186,  -186,
    -186,   205,    11,  -186,    22,    19,    39,    40,    50,  -186,
    -186,    67,  -186,  -186,  -186,    76,    84,    89,    91,  -186,
      85,    61,   146,    92,    94,    95,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,   116,  -186,   105,   170,   109,   112,   147,   170,
     121,  -186,  -186,   115,  -186,   126,   205,   205,  -186,    58,
    -186,   170,   122,   205,   154,   157,  -186,   170,   127,  -186,
     170,    74,  -186,  -186,   170,  -186,   162,    34,   129,   105,
     205,  -186,  -186,   170,    47,    49,   133,    74,   158,  -186,
    -186,   167,  -186,  -186,  -186,   136,  -186,  -186,  -186,  -186,
     170,   135,   205,   205,   108,  -186,   213,   150,  -186,   151,
     178,   170,   205,   152,  -186,  -186,    54,  -186,    63,  -186,
     153,  -186,   205,  -186,  -186,  -186,  -186,   170,   149,   205,
     164,   205,  -186,  -186,   166,   175,   176,  -186,  -186,  -186,
    -186,  -186,   171,  -186,   170,  -186,   205,   183,  -186,   179,
    -186,   170,  -186
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     5,     1,     4,     0,    18,   129,   130,   132,
     131,     0,     7,    23,     6,     0,     0,    20,    10,     2,
      16,   113,   115,   114,   116,   117,     0,   105,   107,     0,
     124,    87,    89,    90,    92,    94,    96,    98,   100,   102,
     104,   110,   119,   123,     0,     0,     0,     0,    22,     0,
       0,     0,     0,   113,   109,     0,     0,     0,    85,     0,
       0,     0,     0,     0,     0,     0,     0,   111,   112,     0,
       0,    77,     0,    13,     8,     0,    13,     0,   106,   108,
     118,     0,    91,   102,    93,    95,    97,    99,   101,   103,
      88,   113,   121,   122,   120,   113,     0,     0,     0,    60,
       0,     0,     0,     0,     0,     0,    24,    59,    27,    19,
      35,    34,    44,    45,    29,    32,    33,    31,    30,    28,
      71,    72,     0,    73,    57,    77,     0,    12,     0,    77,
       0,   127,   128,     0,    86,     0,     0,    84,    74,     0,
      62,    77,     0,     0,     0,     0,    54,    77,     0,    21,
      77,     0,    14,    17,    77,   126,    40,     0,     0,    83,
       0,    61,    64,    77,     0,     0,     0,    56,     0,    58,
      11,     0,     9,    43,    37,    41,    65,    80,    75,    63,
      77,     0,     0,     0,    25,    53,     0,     0,    15,     0,
       0,    77,    84,     0,    68,    47,     0,    49,     0,    52,
       0,    55,     0,    38,    42,    66,    81,    77,     0,     0,
       0,     0,    26,    78,     0,    70,     0,    76,    46,    48,
      50,    51,     0,    39,    77,    67,    84,     0,    69,     0,
      79,    77,    82
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -186,  -186,  -186,  -186,   203,  -186,  -186,   118,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,  -186,  -107,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,    93,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,  -185,   -29,   -14,  -157,  -186,   169,   174,   168,   173,
     180,   172,   -51,  -186,  -186,   204,   140,    64,  -186,  -186,
     177,  -186,  -186,    -3
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     5,    12,    51,    46,   126,   127,    13,
      50,    16,    45,    19,   108,   146,   200,   109,   110,   135,
     189,   214,   174,   175,   111,   112,   196,   113,   198,   167,
     184,   114,   148,   115,   139,   116,   117,   118,   191,   215,
     225,   119,   120,   160,   193,   121,   122,   222,   123,   192,
     216,   158,   124,    58,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    55,    56,    40,    41,    14,    70,    42,
      43,    52,   133,   128
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      57,    30,    15,   178,    78,    79,     3,   206,    83,    83,
      83,    83,    83,    83,    89,    17,    49,     4,   149,    44,
      18,    59,   153,     6,     7,     8,     9,    10,    20,    67,
      68,    60,    -8,    21,   162,    22,    23,    24,    25,  -125,
     168,   229,    62,   170,    61,   213,    69,   172,     7,     8,
       9,    10,    90,    26,   131,    92,   179,   132,    11,    27,
      28,    80,    81,    63,    29,    64,    53,   134,    22,    23,
      24,    25,    66,   194,   176,    81,    65,   201,     7,     8,
       9,    10,    47,    71,   205,    18,    26,   180,    81,   181,
     182,    72,    27,    28,   208,   209,    73,    29,    74,    75,
     217,    76,   107,   210,   211,    77,   141,   157,   159,    83,
      94,   125,   129,  -125,   164,   -36,    95,   228,    22,    23,
      24,    25,    96,   136,   232,    97,    98,   -77,   137,   140,
     138,   143,   199,   144,   145,   147,    26,    99,   100,   101,
     102,   103,    27,    28,   104,   105,    81,    29,   171,   150,
     106,    83,   107,   151,    53,   152,    22,    23,    24,    25,
     221,   154,   155,   159,   186,   156,   165,   163,   197,   166,
     173,   169,    30,   177,   183,   188,   187,   190,    95,   195,
      22,    23,    24,    25,    96,    29,   204,    97,    98,   202,
     224,   203,   207,   218,   130,   219,   212,   159,    26,    99,
     100,   101,   102,   103,    27,    28,   104,   105,   220,    29,
     223,   227,   106,    53,   107,    22,    23,    24,    25,   231,
     226,    91,    48,    22,    23,    24,    25,   230,    82,    85,
      54,   185,   161,    26,    84,    86,    88,     0,     0,    27,
      28,    26,   142,    87,    29,     0,    93,    27,    28,     0,
       0,     0,    29
};

static const yytype_int16 yycheck[] =
{
      29,    15,     5,   160,    55,    56,     0,   192,    59,    60,
      61,    62,    63,    64,    65,     3,    19,     9,   125,    39,
       8,    21,   129,     3,     4,     5,     6,     7,     3,    34,
      35,    20,    39,     8,   141,    10,    11,    12,    13,    46,
     147,   226,    23,   150,    22,   202,    41,   154,     4,     5,
       6,     7,    66,    28,     8,    69,   163,    11,    38,    34,
      35,    40,    41,    24,    39,    25,     8,    81,    10,    11,
      12,    13,    27,   180,    40,    41,    26,   184,     4,     5,
       6,     7,    38,    40,   191,     8,    28,    40,    41,    40,
      41,    39,    34,    35,    40,    41,    39,    39,     8,    39,
     207,    39,    44,    40,    41,    46,    45,   136,   137,   160,
      44,    40,    40,    46,   143,    39,     8,   224,    10,    11,
      12,    13,    14,    39,   231,    17,    18,    19,    39,    44,
      39,    39,   183,    39,    39,    19,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    41,    39,   151,    40,
      42,   202,    44,    41,     8,     8,    10,    11,    12,    13,
     211,    40,    47,   192,   167,    39,    12,    45,   182,    12,
       8,    44,   186,    44,    41,     8,    18,    41,     8,    44,
      10,    11,    12,    13,    14,    39,     8,    17,    18,    39,
      15,    40,    40,    44,    76,   209,    43,   226,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    44,    39,
      44,    40,    42,     8,    44,    10,    11,    12,    13,    40,
      44,     8,    19,    10,    11,    12,    13,    44,    59,    61,
      26,   167,   139,    28,    60,    62,    64,    -1,    -1,    34,
      35,    28,   102,    63,    39,    -1,    69,    34,    35,    -1,
      -1,    -1,    39
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    49,    50,     0,     9,    51,     3,     4,     5,     6,
       7,    38,    52,    57,   115,   121,    59,     3,     8,    61,
       3,     8,    10,    11,    12,    13,    28,    34,    35,    39,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     113,   114,   117,   118,    39,    60,    54,    38,    52,   121,
      58,    53,   119,     8,   113,   111,   112,   100,   101,    21,
      20,    22,    23,    24,    25,    26,    27,    34,    35,    41,
     116,    40,    39,    39,     8,    39,    39,    46,   110,   110,
      40,    41,   104,   110,   105,   106,   107,   108,   109,   110,
     101,     8,   101,   118,    44,     8,    14,    17,    18,    29,
      30,    31,    32,    33,    36,    37,    42,    44,    62,    65,
      66,    72,    73,    75,    79,    81,    83,    84,    85,    89,
      90,    93,    94,    96,   100,    40,    55,    56,   121,    40,
      55,     8,    11,   120,   101,    67,    39,    39,    39,    82,
      44,    45,   114,    39,    39,    39,    63,    19,    80,    65,
      40,    41,     8,    65,    40,    47,    39,   100,    99,   100,
      91,    79,    65,    45,   100,    12,    12,    77,    65,    44,
      65,   121,    65,     8,    70,    71,    40,    44,   102,    65,
      40,    40,    41,    41,    78,   115,   121,    18,     8,    68,
      41,    86,    97,    92,    65,    44,    74,   101,    76,   110,
      64,    65,    39,    40,     8,    65,    99,    40,    40,    41,
      40,    41,    43,   102,    69,    87,    98,    65,    44,   101,
      44,   110,    95,    44,    15,    88,    44,    40,    65,    99,
      44,    40,    65
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    51,    53,    52,
      54,    52,    55,    55,    56,    56,    58,    57,    59,    57,
      60,    57,    61,    61,    63,    64,    62,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    67,    68,    69,    66,
      70,    70,    71,    71,    72,    72,    73,    73,    74,    74,
      75,    76,    76,    77,    77,    78,    78,    80,    79,    79,
      82,    81,    83,    84,    84,    86,    87,    85,    85,    88,
      88,    89,    89,    89,    91,    92,    90,    94,    95,    93,
      97,    98,    96,    99,    99,   100,   100,   101,   101,   102,
     103,   103,   104,   104,   105,   105,   106,   106,   107,   107,
     108,   108,   109,   109,   110,   111,   110,   112,   110,   110,
     113,   113,   113,   114,   114,   114,   114,   114,   114,   116,
     115,   117,   117,   117,   117,   119,   118,   120,   120,   121,
     121,   121,   121
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     0,     2,     0,     2,     2,     0,     7,
       0,     7,     1,     0,     2,     4,     0,     6,     0,     5,
       0,     6,     2,     0,     0,     0,     6,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     0,     0,     8,
       0,     1,     3,     1,     1,     1,     7,     5,     3,     1,
       7,     3,     1,     2,     0,     2,     0,     0,     3,     1,
       0,     3,     2,     4,     3,     0,     0,     8,     5,     2,
       0,     1,     1,     1,     0,     0,     7,     0,     0,     9,
       0,     0,    11,     1,     0,     1,     3,     1,     3,     1,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     0,     3,     0,     3,     2,
       1,     2,     2,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     3,     1,     1,     0,     5,     1,     1,     1,
       1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      YY_LAC_DISCARD ("YYBACKUP");                              \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return 1 if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYSIZE_T *yycapacity, YYSIZE_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yytype_int16 **yybottom,
                      yytype_int16 *yybottom_no_free,
                      yytype_int16 **yytop, yytype_int16 *yytop_empty)
{
  YYSIZE_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYSIZE_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYSIZE_T yyalloc = 2 * yysize_new;
      yytype_int16 *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        (yytype_int16*) YYSTACK_ALLOC (yyalloc * sizeof *yybottom_new);
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                         \
do {                                                             \
  if (!yy_lac_established)                                       \
    {                                                            \
      YYDPRINTF ((stderr,                                        \
                  "LAC: initial context established for %s\n",   \
                  yytname[yytoken]));                            \
      yy_lac_established = 1;                                    \
      {                                                          \
        int yy_lac_status =                                      \
          yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken); \
        if (yy_lac_status == 2)                                  \
          goto yyexhaustedlab;                                   \
        if (yy_lac_status == 1)                                  \
          goto yyerrlab;                                         \
      }                                                          \
    }                                                            \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      if (yydebug)                                                       \
        YYFPRINTF (stderr, "LAC: initial context discarded due to "      \
                   Event "\n");                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return 2 if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yytype_int16 *yyesa, yytype_int16 **yyes,
        YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  yytype_int16 *yyes_prev = yyssp;
  yytype_int16 *yyesp = yyes_prev;
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yytname[yytoken]));
  if (yytoken == YYUNDEFTOK)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          yyrule = yydefact[*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      {
        YYSIZE_T yylen = yyr2[yyrule];
        YYDPRINTF ((stderr, " R%d", yyrule - 1));
        if (yyesp != yyes_prev)
          {
            YYSIZE_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yylen -= yysize;
                yyesp = yyes_prev;
              }
          }
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      {
        int yystate;
        {
          int yylhs = yyr1[yyrule] - YYNTOKENS;
          yystate = yypgoto[yylhs] + *yyesp;
          if (yystate < 0 || YYLAST < yystate
              || yycheck[yystate] != *yyesp)
            yystate = yydefgoto[yylhs];
          else
            yystate = yytable[yystate];
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            *yyesp = yystate;
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return 2;
              }
            *++yyesp = yystate;
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store or if
   yy_lac returned 2.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyesa, yytype_int16 **yyes,
                YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          int yyx;

          for (yyx = 0; yyx < YYNTOKENS; ++yyx)
            if (yyx != YYTERROR && yyx != YYUNDEFTOK)
              {
                {
                  int yy_lac_status = yy_lac (yyesa, yyes, yyes_capacity,
                                              yyssp, yyx);
                  if (yy_lac_status == 2)
                    return 2;
                  if (yy_lac_status == 1)
                    continue;
                }
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
# if YYDEBUG
      else if (yydebug)
        YYFPRINTF (stderr, "No expected tokens.\n");
# endif
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

    yytype_int16 yyesa[20];
    yytype_int16 *yyes;
    YYSIZE_T yyes_capacity;

  int yy_lac_established = 0;
  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  yyes = yyesa;
  yyes_capacity = sizeof yyesa / sizeof *yyes;
  if (YYMAXDEPTH < yyes_capacity)
    yyes_capacity = YYMAXDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      YY_LAC_ESTABLISH;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  YY_LAC_DISCARD ("shift");

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
          case 5:
#line 201 "parser.y" /* yacc.c:1646  */
    { strcpy(current_scope, "global"); }
#line 1870 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 205 "parser.y" /* yacc.c:1646  */
    { 
        strcpy(current_scope, current_identifier);
        strcpy(current_return_type, current_data_type);
        insert_into_function_table (current_identifier, current_return_type, current_line_no);
        start_function_block();
    }
#line 1881 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 211 "parser.y" /* yacc.c:1646  */
    {end_function_block(); printf ("\n"); }
#line 1887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 212 "parser.y" /* yacc.c:1646  */
    {
        strcpy (current_scope, current_identifier);
        strcpy (current_return_type, "void");
        insert_into_function_table (current_identifier, current_return_type, current_line_no);
    }
#line 1897 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 217 "parser.y" /* yacc.c:1646  */
    {end_function_block(); printf ("\n");}
#line 1903 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 221 "parser.y" /* yacc.c:1646  */
    {
            insert_into_function_table_arg_list(current_scope, current_data_type, current_identifier);
        }
#line 1911 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 224 "parser.y" /* yacc.c:1646  */
    {
            insert_into_function_table_arg_list(current_scope, current_data_type, current_identifier);
        }
#line 1919 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 229 "parser.y" /* yacc.c:1646  */
    {strcpy(current_scope, "main"); start_function_block();}
#line 1925 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 229 "parser.y" /* yacc.c:1646  */
    {end_function_block(); printf ("\n");}
#line 1931 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 230 "parser.y" /* yacc.c:1646  */
    {strcpy(current_scope, "main"); start_function_block(); }
#line 1937 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 230 "parser.y" /* yacc.c:1646  */
    {end_function_block(); printf ("\n");}
#line 1943 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 231 "parser.y" /* yacc.c:1646  */
    {strcpy (current_scope, "main"); start_function_block();}
#line 1949 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 231 "parser.y" /* yacc.c:1646  */
    {end_function_block(); printf ("\n");}
#line 1955 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 238 "parser.y" /* yacc.c:1646  */
    { push(current_opening_brace_line_no); }
#line 1961 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 239 "parser.y" /* yacc.c:1646  */
    {
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
}
#line 1979 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 251 "parser.y" /* yacc.c:1646  */
    {
    if (peek() != -1) {
        int opening_boundary_line_no = pop();
        insert_into_symbol_table_closing_line(current_scope, opening_boundary_line_no, current_closing_brace_line_no); 
    }
}
#line 1990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 258 "parser.y" /* yacc.c:1646  */
    {isReturn = false; isExpn = false;}
#line 1996 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 268 "parser.y" /* yacc.c:1646  */
    {
    strcpy (current_function, current_identifier);
    if (lookup_function_table(current_identifier) == 0) {
        yyerror("Use of undeclared function");
    }
}
#line 2007 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 273 "parser.y" /* yacc.c:1646  */
    {
    if (!compare_no_of_args(current_function, no_of_args)) {
        yyerror("Mismatch in number of arguments");
    }
}
#line 2017 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 277 "parser.y" /* yacc.c:1646  */
    {
    function_call_end();
    no_of_args = 0;
}
#line 2026 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 285 "parser.y" /* yacc.c:1646  */
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
}
#line 2045 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 298 "parser.y" /* yacc.c:1646  */
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
}
#line 2064 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 331 "parser.y" /* yacc.c:1646  */
    { isExpn = true; }
#line 2070 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 334 "parser.y" /* yacc.c:1646  */
    { isReturn = true; }
#line 2076 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 335 "parser.y" /* yacc.c:1646  */
    {
    if ((strcmp(current_return_type, "void") == 0) && isReturn && isExpn) {
        yyerror("Void function returning a value");
    } else if (isReturn && !isExpn && current_return_type[0]!='v') {
        yyerror("Non-void function returning a void value");
    }
}
#line 2088 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 348 "parser.y" /* yacc.c:1646  */
    {
                        if ((yyvsp[-1]) < 0) {
                            yyerror ("Invalid IF check");
                        } 
                        gen_if_statement();
                    }
#line 2099 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 353 "parser.y" /* yacc.c:1646  */
    {gen_if_block();}
#line 2105 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 356 "parser.y" /* yacc.c:1646  */
    {gen_else_block();}
#line 2111 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 357 "parser.y" /* yacc.c:1646  */
    {gen_else_block(); }
#line 2117 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 364 "parser.y" /* yacc.c:1646  */
    {start_while_block(); }
#line 2123 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 364 "parser.y" /* yacc.c:1646  */
    {
                if ((yyvsp[-1]) < 0) {
                    yyerror ("Invalid WHILE check");
                }
                gen_if_statement();
            }
#line 2134 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 369 "parser.y" /* yacc.c:1646  */
    {gen_while_block();}
#line 2140 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 371 "parser.y" /* yacc.c:1646  */
    {start_while_block();}
#line 2146 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 371 "parser.y" /* yacc.c:1646  */
    {
    if ((yyvsp[-1]) < 0) {
        yyerror ("Invalid DO-WHILE check");
    } 
    gen_if_statement();
    gen_while_block();
}
#line 2158 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 379 "parser.y" /* yacc.c:1646  */
    {start_while_block(); }
#line 2164 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 379 "parser.y" /* yacc.c:1646  */
    {
    if ((yyvsp[-1]) < 0) {
        yyerror ("Invalid FOR check");
    }
    gen_if_statement();
}
#line 2175 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 384 "parser.y" /* yacc.c:1646  */
    {gen_while_block();}
#line 2181 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 389 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2187 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 390 "parser.y" /* yacc.c:1646  */
    { 
        if (((yyvsp[-2]) == (yyvsp[0])) && ((yyvsp[-2]) != -1)){
            (yyval) = (yyvsp[-2]);
        } else {
            yyerror ("Invalid Expression");
        }
     }
#line 2199 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 398 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2205 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 399 "parser.y" /* yacc.c:1646  */
    {
                    if (((yyvsp[-2]) == (yyvsp[0])) && ((yyvsp[-2]) != -1)) {
                        (yyval) = (yyvsp[-2]);
                    } else if ((yyvsp[-2]) != (yyvsp[0])){
                        yyerror ("Type Mismatch");
                    } else if ((yyvsp[-2]) == -1) {
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
                }
#line 2230 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 420 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2236 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 422 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2242 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 423 "parser.y" /* yacc.c:1646  */
    {
                    if (((yyvsp[-2]) == (yyvsp[0])) && ((yyvsp[-2]) != -1)) {
                        (yyval) = (yyvsp[-2]);
                        icg_push_symbol_stack("||");
                        gen_expn();
                    } else {
                        yyerror ("Invalid Logical OR Expression");
                    }
                }
#line 2256 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 433 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2262 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 434 "parser.y" /* yacc.c:1646  */
    {
                    if (((yyvsp[-2]) == (yyvsp[0])) && ((yyvsp[-2]) != -1)) {
                        (yyval) = (yyvsp[-2]);
                        icg_push_symbol_stack("&&");
                        gen_expn();
                    } else {
                        yyerror ("Invalid Logical AND Expression");
                    }
                 }
#line 2276 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 444 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2282 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 445 "parser.y" /* yacc.c:1646  */
    {
                    if (((yyvsp[-2]) == (yyvsp[0])) && ((yyvsp[-2]) != -1)) {
                        (yyval) = (yyvsp[-2]);
                        switch (equality_op_choice) {
                            case 0: icg_push_symbol_stack ("=="); break;
                            case 1: icg_push_symbol_stack ("!="); break;
                        }
                        gen_expn();
                    } else {
                        yyerror ("Invalid Equality Expression");
                    }
              }
#line 2299 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 458 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2305 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 459 "parser.y" /* yacc.c:1646  */
    {
                    if (((yyvsp[-2]) == (yyvsp[0])) && ((yyvsp[-2]) != -1)) {
                        (yyval) = (yyvsp[-2]);
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
                }
#line 2324 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 474 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2330 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 475 "parser.y" /* yacc.c:1646  */
    {
                switch ((yyvsp[-2]) + (yyvsp[0])) {
                    case 2 : (yyval) = 1; break;
                    case 1 : (yyval) = 0; break;
                    case 0 : ((yyvsp[-2]) == (yyvsp[0])) ? (yyval) = 0 : yyerror ("Invalid String operations"); 
                                break;
                    case -1 :
                    case -2 : yyerror ("Invalid String operations"); 
                }
                switch (shift_op_choice) {
                    case 0: icg_push_symbol_stack("<<"); break;
                    case 1: icg_push_symbol_stack(">>"); break;
                }
                gen_expn();
            }
#line 2350 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 491 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2356 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 492 "parser.y" /* yacc.c:1646  */
    {
                    switch ((yyvsp[-2]) + (yyvsp[0])) {
                        case 2 : (yyval) = 1; break;
                        case 1 : (yyval) = 0; break;
                        case 0 : ((yyvsp[-2]) == (yyvsp[0])) ? (yyval) = 0 : yyerror ("Invalid String operations"); 
                                    break;
                        case -1 :
                        case -2 : yyerror ("Invalid String operations"); 
                    }
                    switch (add_op_choice) {
                        case 0: icg_push_symbol_stack ("+"); break;
                        case 1: icg_push_symbol_stack ("-"); break;
                    }
                    gen_expn();
              }
#line 2376 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 508 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2382 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 509 "parser.y" /* yacc.c:1646  */
    { 
                        switch ((yyvsp[-2]) + (yyvsp[0])) {
                            case 2 : (yyval) = 1; break;
                            case 1 : (yyval) = 0; break;
                            case 0 : ((yyvsp[-2]) == (yyvsp[0])) ? (yyval) = 0 : yyerror ("Invalid String operations"); 
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
                    }
#line 2403 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 526 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2409 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 527 "parser.y" /* yacc.c:1646  */
    {icg_push_symbol_stack("++"); gen_inc_expn();}
#line 2415 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 527 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 2421 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 528 "parser.y" /* yacc.c:1646  */
    {icg_push_symbol_stack("--"); gen_dec_expn();}
#line 2427 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 528 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 2433 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 529 "parser.y" /* yacc.c:1646  */
    { 
                (yyval) = (yyvsp[0]);                 
                switch (unary_op_choice) {
                    case 0: icg_push_symbol_stack("&"); break;
                    case 1: icg_push_symbol_stack("~"); break; 
                    case 2: icg_push_symbol_stack("!"); break;
                }
                gen_unary_expn();
            }
#line 2447 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 539 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2453 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 540 "parser.y" /* yacc.c:1646  */
    {icg_push_symbol_stack ("++"); (yyval) = (yyvsp[-1]); gen_inc_expn();}
#line 2459 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 541 "parser.y" /* yacc.c:1646  */
    {icg_push_symbol_stack ("--"); (yyval) = (yyvsp[-1]); gen_dec_expn();}
#line 2465 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 543 "parser.y" /* yacc.c:1646  */
    { 
        push_symbol(current_identifier, current_data_type, current_scope, current_line_no, current_opening_brace_line_no, 0); 
        icg_push_symbol_stack (current_identifier);
        char *symbol_data_type = (char *)calloc(20,sizeof(char));
        symbol_data_type = data_type_of_symbol(current_identifier, current_scope);
        if (symbol_data_type != NULL) {
            if ((strcmp(symbol_data_type, "int")==0) || (strcmp(symbol_data_type, "char")==0)){
                (yyval) = 1;
            } 
            else if ((strcmp(symbol_data_type, "float")==0) || (strcmp(symbol_data_type, "double")==0)) {
                (yyval) = 0;
            } else {
                (yyval) = -1;
            }
        }
    }
#line 2486 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 559 "parser.y" /* yacc.c:1646  */
    { (yyval) = 1; gen_constant_expn(); }
#line 2492 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 560 "parser.y" /* yacc.c:1646  */
    { (yyval) = 0; gen_constant_expn(); }
#line 2498 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 561 "parser.y" /* yacc.c:1646  */
    { (yyval) = -1; }
#line 2504 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 562 "parser.y" /* yacc.c:1646  */
    { (yyval) = 1; gen_constant_expn(); }
#line 2510 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 563 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 2516 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 566 "parser.y" /* yacc.c:1646  */
    {
    while (stack_top != -1){
        symbolStack sym = stk[stack_top];
        if (sym.opening_boundary_line_no < peek()) { break; }
        insert_into_symbol_table(sym.symbol_name, sym.data_type, sym.scope, sym.line_no, sym.opening_boundary_line_no, sym.isArray, sym.arraySize);
        stack_top--;
        icg_symbol_stack_top--;
    }
}
#line 2530 "y.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 581 "parser.y" /* yacc.c:1646  */
    {
    push_symbol(current_identifier, current_data_type, current_scope,current_line_no, current_opening_brace_line_no, 1);  
}
#line 2538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 585 "parser.y" /* yacc.c:1646  */
    {
    update_array_size(current_value);
}
#line 2546 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2550 "y.tab.c" /* yacc.c:1646  */
        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
  }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyesa, &yyes, &yyes_capacity, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 594 "parser.y" /* yacc.c:1906  */


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
