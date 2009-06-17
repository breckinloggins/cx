/* A Bison parser, made by GNU Bison 2.0.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_OR = 258,
     T_AND = 259,
     T_NOTEQUAL = 260,
     T_EQUAL = 261,
     T_GREATEREQUAL = 262,
     T_LESSEREQUAL = 263,
     T_GREATER = 264,
     T_LESSER = 265,
     T_MINUS = 266,
     T_PLUS = 267,
     T_SLASH = 268,
     T_STAR = 269,
     T_NOT = 270,
     T_NAMESPACE = 271,
     T_VAR = 272,
     T_IF = 273,
     T_ELSE = 274,
     T_WHILE = 275,
     T_FOR = 276,
     T_TO = 277,
     T_DO = 278,
     T_ASSIGNMENT = 279,
     T_LPAR = 280,
     T_RPAR = 281,
     T_LBRACK = 282,
     T_RBRACK = 283,
     T_SEMICOLON = 284,
     T_COLON = 285,
     T_COMMA = 286,
     T_DOT = 287,
     T_PRINT_INT = 288,
     T_PRINT_CHAR = 289,
     T_PRINT_BOOL = 290,
     T_PRINT_LINE = 291,
     T_BOGUS = 292,
     TYPE_IDENTIFIER = 293,
     IDENTIFIER = 294,
     INT_LITERAL = 295,
     BOOL_LITERAL = 296,
     CHAR_LITERAL = 297,
     DOUBLE_LITERAL = 298,
     FLOAT_LITERAL = 299
   };
#endif
#define T_OR 258
#define T_AND 259
#define T_NOTEQUAL 260
#define T_EQUAL 261
#define T_GREATEREQUAL 262
#define T_LESSEREQUAL 263
#define T_GREATER 264
#define T_LESSER 265
#define T_MINUS 266
#define T_PLUS 267
#define T_SLASH 268
#define T_STAR 269
#define T_NOT 270
#define T_NAMESPACE 271
#define T_VAR 272
#define T_IF 273
#define T_ELSE 274
#define T_WHILE 275
#define T_FOR 276
#define T_TO 277
#define T_DO 278
#define T_ASSIGNMENT 279
#define T_LPAR 280
#define T_RPAR 281
#define T_LBRACK 282
#define T_RBRACK 283
#define T_SEMICOLON 284
#define T_COLON 285
#define T_COMMA 286
#define T_DOT 287
#define T_PRINT_INT 288
#define T_PRINT_CHAR 289
#define T_PRINT_BOOL 290
#define T_PRINT_LINE 291
#define T_BOGUS 292
#define TYPE_IDENTIFIER 293
#define IDENTIFIER 294
#define INT_LITERAL 295
#define BOOL_LITERAL 296
#define CHAR_LITERAL 297
#define DOUBLE_LITERAL 298
#define FLOAT_LITERAL 299




/* Copy the first part of user declarations.  */
#line 1 "parser.y"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "base.h"
#include "parser.tab.h"
#include "ast/ast.h"
#include "symbol_table.h"

#define YYDEBUG 1

extern FILE *yyin;

static void yyerror(const char* msg);

AstNode* ast;
	


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 26 "parser.y"
typedef union YYSTYPE {
	char* lexeme;
	int integer;
	int boolean;
	double dbl;
	float flt;
	char character;
	int type;
	struct AstNode_tag* astnode;
} YYSTYPE;
/* Line 185 of yacc.c.  */
#line 195 "parser.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined (YYLTYPE) && ! defined (YYLTYPE_IS_DECLARED)
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 213 of yacc.c.  */
#line 219 "parser.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYLTYPE_IS_TRIVIAL) && YYLTYPE_IS_TRIVIAL \
             && defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   168

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  45
/* YYNRULES -- Number of rules. */
#define YYNRULES  90
/* YYNRULES -- Number of states. */
#define YYNSTATES  156

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     5,    13,    14,    16,    20,    23,    26,
      27,    31,    33,    34,    37,    38,    41,    52,    55,    56,
      59,    60,    64,    68,    69,    74,    76,    80,    81,    83,
      87,    89,    91,    93,    95,    97,    99,   101,   103,   105,
     107,   115,   121,   129,   131,   133,   135,   137,   142,   147,
     152,   156,   160,   166,   174,   176,   180,   182,   186,   188,
     192,   194,   197,   199,   201,   203,   207,   212,   213,   216,
     217,   221,   223,   225,   227,   229,   231,   233,   235,   237,
     239,   241,   243,   245,   247,   249,   251,   253,   255,   257,
     259
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      46,     0,    -1,    47,    -1,    16,    88,    27,    48,    53,
      59,    28,    -1,    -1,    49,    -1,    49,    29,    48,    -1,
      38,    50,    -1,    52,    51,    -1,    -1,    31,    52,    51,
      -1,    88,    -1,    -1,    55,    54,    -1,    -1,    55,    54,
      -1,    88,    30,    38,    25,    56,    26,    27,    48,    61,
      28,    -1,    88,    37,    -1,    -1,    58,    57,    -1,    -1,
      31,    58,    57,    -1,    88,    30,    38,    -1,    -1,    27,
      61,    28,    32,    -1,    62,    -1,    27,    61,    28,    -1,
      -1,    62,    -1,    62,    29,    61,    -1,    63,    -1,    64,
      -1,    29,    -1,    72,    -1,    66,    -1,    73,    -1,    74,
      -1,    80,    -1,    67,    -1,    65,    -1,    18,    25,    75,
      26,    63,    19,    64,    -1,    18,    25,    75,    26,    60,
      -1,    18,    25,    75,    26,    63,    19,    63,    -1,    68,
      -1,    69,    -1,    70,    -1,    71,    -1,    33,    25,    75,
      26,    -1,    34,    25,    75,    26,    -1,    35,    25,    75,
      26,    -1,    36,    25,    26,    -1,    88,    24,    75,    -1,
      20,    25,    75,    26,    60,    -1,    21,    25,    72,    22,
      75,    26,    60,    -1,    76,    -1,    76,    86,    76,    -1,
      77,    -1,    76,    84,    77,    -1,    78,    -1,    77,    85,
      78,    -1,    79,    -1,    87,    79,    -1,    88,    -1,    89,
      -1,    80,    -1,    25,    75,    26,    -1,    88,    25,    81,
      26,    -1,    -1,    83,    82,    -1,    -1,    31,    83,    82,
      -1,    75,    -1,    12,    -1,    11,    -1,     3,    -1,    14,
      -1,    13,    -1,     4,    -1,    10,    -1,     8,    -1,     9,
      -1,     7,    -1,     6,    -1,     5,    -1,    15,    -1,    39,
      -1,    40,    -1,    41,    -1,    42,    -1,    44,    -1,    43,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   138,   138,   149,   162,   163,   170,   183,   192,   202,
     203,   211,   215,   216,   226,   227,   235,   248,   252,   253,
     263,   264,   271,   280,   281,   285,   286,   290,   291,   298,
     310,   311,   312,   316,   317,   318,   319,   320,   321,   325,
     326,   337,   347,   358,   359,   360,   361,   365,   374,   383,
     392,   400,   410,   420,   430,   431,   442,   443,   456,   457,
     470,   471,   480,   481,   482,   483,   487,   497,   498,   508,
     509,   517,   526,   531,   536,   544,   549,   554,   562,   567,
     572,   577,   582,   587,   595,   599,   608,   614,   620,   626,
     632
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_OR", "T_AND", "T_NOTEQUAL", "T_EQUAL",
  "T_GREATEREQUAL", "T_LESSEREQUAL", "T_GREATER", "T_LESSER", "T_MINUS",
  "T_PLUS", "T_SLASH", "T_STAR", "T_NOT", "T_NAMESPACE", "T_VAR", "T_IF",
  "T_ELSE", "T_WHILE", "T_FOR", "T_TO", "T_DO", "T_ASSIGNMENT", "T_LPAR",
  "T_RPAR", "T_LBRACK", "T_RBRACK", "T_SEMICOLON", "T_COLON", "T_COMMA",
  "T_DOT", "T_PRINT_INT", "T_PRINT_CHAR", "T_PRINT_BOOL", "T_PRINT_LINE",
  "T_BOGUS", "TYPE_IDENTIFIER", "IDENTIFIER", "INT_LITERAL",
  "BOOL_LITERAL", "CHAR_LITERAL", "DOUBLE_LITERAL", "FLOAT_LITERAL",
  "$accept", "TranslationUnit", "NamespaceDecl", "VarDeclList", "VarDecl",
  "IdentifierList", "MultiIdentifier", "SingleIdentifier", "FunctionList",
  "MultiFunctionDecl", "FunctionDecl", "ParamList", "MultiParam",
  "SingleParam", "ProgramBody", "Statements", "StatementList", "Statement",
  "StatementMatched", "StatementUnmatched", "IfStatement",
  "IfStatementMatched", "PrintStatement", "PrintIntStatement",
  "PrintCharStatement", "PrintBoolStatement", "PrintLineStatement",
  "Assignment", "WhileStatement", "ForStatement", "Expression",
  "SimpleExpression", "Term", "NotFactor", "Factor", "Call",
  "CallParamList", "MultiCallParameter", "CallParameter", "AddOp", "MulOp",
  "RelOp", "NotOp", "Identifier", "Literal", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    45,    46,    47,    48,    48,    48,    49,    50,    51,
      51,    52,    53,    53,    54,    54,    55,    55,    56,    56,
      57,    57,    58,    59,    59,    60,    60,    61,    61,    61,
      62,    62,    62,    63,    63,    63,    63,    63,    63,    64,
      64,    65,    66,    67,    67,    67,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    75,    76,    76,    77,    77,
      78,    78,    79,    79,    79,    79,    80,    81,    81,    82,
      82,    83,    84,    84,    84,    85,    85,    85,    86,    86,
      86,    86,    86,    86,    87,    88,    89,    89,    89,    89,
      89
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     7,     0,     1,     3,     2,     2,     0,
       3,     1,     0,     2,     0,     2,    10,     2,     0,     2,
       0,     3,     3,     0,     4,     1,     3,     0,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       7,     5,     7,     1,     1,     1,     1,     4,     4,     4,
       3,     3,     5,     7,     1,     3,     1,     3,     1,     3,
       1,     2,     1,     1,     1,     3,     4,     0,     2,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     2,    85,     0,     1,     4,     0,    12,
       5,     7,     9,    11,    23,    14,     0,     4,     0,     8,
      27,     0,    13,    14,     0,    17,     6,     9,     0,     0,
       0,    32,     0,     0,     0,     0,     0,    28,    30,    31,
      39,    34,    38,    43,    44,    45,    46,    33,    35,    36,
      37,     0,     3,    15,     0,    10,     0,     0,     0,     0,
       0,     0,     0,     0,    27,     0,    67,    18,    84,     0,
      86,    87,    88,    90,    89,     0,    54,    56,    58,    60,
      64,     0,    62,    63,     0,     0,     0,     0,     0,     0,
      50,    24,    29,    51,    71,     0,    69,     0,    20,     0,
       0,     0,    74,    83,    82,    81,    79,    80,    78,    73,
      72,     0,     0,    77,    76,    75,     0,    61,     0,     0,
      47,    48,    49,    66,     0,    68,     0,     0,    19,     0,
      65,    27,    41,    25,    30,    57,    55,    59,    52,     0,
      69,     4,    20,    22,     0,     0,     0,    70,    27,    21,
      26,    42,    40,    53,     0,    16
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     2,     3,     9,    10,    11,    19,    12,    14,    22,
      23,    97,   128,    98,    21,   132,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      94,    76,    77,    78,    79,    80,    95,   125,    96,   111,
     116,   112,    81,    82,    83
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -113
static const short int yypact[] =
{
      -3,   -24,    16,  -113,  -113,     3,  -113,    -7,   -24,   -24,
       7,  -113,     1,  -113,    18,   -24,   -25,    -7,   -24,  -113,
     103,    21,  -113,   -24,    13,  -113,  -113,     1,    27,    28,
      30,  -113,    35,    36,    37,    39,    40,    38,  -113,  -113,
    -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,   -14,  -113,  -113,    52,  -113,    31,    31,   -24,    31,
      31,    31,    54,    33,   103,    31,    31,   -24,  -113,    31,
    -113,  -113,  -113,  -113,  -113,    55,    32,    14,  -113,  -113,
    -113,    63,    57,  -113,    64,    67,    71,    70,    72,    73,
    -113,  -113,  -113,  -113,  -113,    82,    78,    84,    80,    83,
      86,    58,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,    31,    31,  -113,  -113,  -113,    31,  -113,    58,    31,
    -113,  -113,  -113,  -113,    31,  -113,    88,   -24,  -113,    81,
    -113,   103,  -113,  -113,    97,    14,    47,  -113,  -113,    92,
      78,    -7,    80,  -113,    94,   128,    58,  -113,   103,  -113,
    -113,  -113,  -113,  -113,    99,  -113
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
    -113,  -113,  -113,   -16,  -113,  -113,    93,   115,  -113,   111,
     126,  -113,    -2,    23,  -113,  -112,   -62,   -92,   -97,    -4,
    -113,  -113,  -113,  -113,  -113,  -113,  -113,    85,  -113,  -113,
     -36,    41,    43,    42,    74,   -17,  -113,    11,    44,  -113,
    -113,  -113,  -113,    -1,  -113
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
       5,    26,    92,    50,   134,    24,   138,    13,    16,   133,
      65,    66,    25,     1,    16,     4,     6,    13,   113,    51,
      75,    84,    16,    87,    88,    89,   133,   114,   115,    93,
       7,     8,    18,   100,   153,   102,    17,   103,   104,   105,
     106,   107,   108,   109,   110,    20,    68,    50,   151,    52,
     102,    54,    56,    57,   133,    58,    69,    86,   109,   110,
      59,    60,    61,    51,    62,    91,    99,    64,    63,   144,
       4,    70,    71,    72,    73,    74,    28,    67,    29,    30,
      90,   101,    66,   139,    50,   131,   154,    31,    69,   119,
     118,    32,    33,    34,    35,    65,   120,     4,   121,   122,
      51,    50,     4,    70,    71,    72,    73,    74,   123,   124,
     126,   127,   130,   129,    50,   141,   145,    51,   146,   143,
      55,    28,   150,    29,    30,   148,    99,   155,    50,    50,
      51,    50,    31,    27,    53,    15,    32,    33,    34,    35,
     149,   152,     4,    85,    51,    51,    28,    51,    29,    30,
     142,   147,     0,   136,   135,   117,     0,     0,   137,     0,
       0,    32,    33,    34,    35,     0,     0,     4,   140
};

static const short int yycheck[] =
{
       1,    17,    64,    20,   101,    30,   118,     8,     9,   101,
      24,    25,    37,    16,    15,    39,     0,    18,     4,    20,
      56,    57,    23,    59,    60,    61,   118,    13,    14,    65,
      27,    38,    31,    69,   146,     3,    29,     5,     6,     7,
       8,     9,    10,    11,    12,    27,    15,    64,   145,    28,
       3,    38,    25,    25,   146,    25,    25,    58,    11,    12,
      25,    25,    25,    64,    25,    32,    67,    29,    28,   131,
      39,    40,    41,    42,    43,    44,    18,    25,    20,    21,
      26,    26,    25,   119,   101,    27,   148,    29,    25,    22,
      26,    33,    34,    35,    36,    24,    26,    39,    26,    26,
     101,   118,    39,    40,    41,    42,    43,    44,    26,    31,
      26,    31,    26,    30,   131,    27,    19,   118,    26,    38,
      27,    18,    28,    20,    21,   141,   127,    28,   145,   146,
     131,   148,    29,    18,    23,     9,    33,    34,    35,    36,
     142,   145,    39,    58,   145,   146,    18,   148,    20,    21,
     127,   140,    -1,   112,   111,    81,    -1,    -1,   116,    -1,
      -1,    33,    34,    35,    36,    -1,    -1,    39,   124
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    16,    46,    47,    39,    88,     0,    27,    38,    48,
      49,    50,    52,    88,    53,    55,    88,    29,    31,    51,
      27,    59,    54,    55,    30,    37,    48,    52,    18,    20,
      21,    29,    33,    34,    35,    36,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      80,    88,    28,    54,    38,    51,    25,    25,    25,    25,
      25,    25,    25,    28,    29,    24,    25,    25,    15,    25,
      40,    41,    42,    43,    44,    75,    76,    77,    78,    79,
      80,    87,    88,    89,    75,    72,    88,    75,    75,    75,
      26,    32,    61,    75,    75,    81,    83,    56,    58,    88,
      75,    26,     3,     5,     6,     7,     8,     9,    10,    11,
      12,    84,    86,     4,    13,    14,    85,    79,    26,    22,
      26,    26,    26,    26,    31,    82,    26,    31,    57,    30,
      26,    27,    60,    62,    63,    77,    76,    78,    60,    75,
      83,    27,    58,    38,    61,    19,    26,    82,    48,    57,
      28,    63,    64,    60,    61,    28
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (0)
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
              (Loc).first_line, (Loc).first_column,	\
              (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Type, Value, Location);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
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
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;
  (void) yylocationp;

  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  fprintf (yyoutput, ": ");

# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;
  (void) yylocationp;

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended. */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif


  yyvsp[0] = yylval;
    yylsp[0] = yylloc;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to look-ahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
  *++yylsp = yylloc;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, yylsp - yylen, yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 139 "parser.y"
    {
		AstNode* ast_node = ast_node_new("TranslationUnit", TRANSLATIONUNIT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// NamespaceDecl
		(yyval.astnode) = ast_node;
		
		ast = ast_node;
	;}
    break;

  case 3:
#line 150 "parser.y"
    {
		AstNode* ast_node = ast_node_new("NamespaceDecl", NAMESPACE_DECL, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-5].astnode));	// Namespace Identifier
		ast_node_add_child(ast_node, (yyvsp[-3].astnode));	// VarDeclList
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// ProcFuncList
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));	// ProgramBody
	
		(yyval.astnode) = ast_node;
	;}
    break;

  case 4:
#line 162 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 5:
#line 164 "parser.y"
    {
		AstNode* ast_node = ast_node_new("VarDeclList", VARDECL_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[0].astnode));

		(yyval.astnode) = ast_node;
	;}
    break;

  case 6:
#line 171 "parser.y"
    {
		AstNode* ast_node = (yyvsp[0].astnode);
		if (!ast_node)	{
			ast_node = ast_node_new("VarDeclList", VARDECL_LIST, VOID, yylloc.last_line, NULL);
		}
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 7:
#line 184 "parser.y"
    {
		AstNode* ast_node = ast_node_new("VarDecl", VARDECL, (yyvsp[-1].type), yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[0].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 8:
#line 193 "parser.y"
    {
		AstNode* ast_node = ast_node_new("IdentifierList", IDENT_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 9:
#line 202 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 10:
#line 204 "parser.y"
    {
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		(yyval.astnode) = (yyvsp[-1].astnode);
	;}
    break;

  case 11:
#line 211 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 12:
#line 215 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 13:
#line 217 "parser.y"
    {
		AstNode* ast_node = ast_node_new("FunctionList", FUNCTION_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 14:
#line 226 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 15:
#line 228 "parser.y"
    {
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		(yyval.astnode) = (yyvsp[-1].astnode);
	;}
    break;

  case 16:
#line 237 "parser.y"
    {
		Symbol* symtab;
		AstNode* ast_node = ast_node_new("FunctionDecl", FUNCTION, (yyvsp[-7].type), yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-9].astnode));	// Identifier
		ast_node_add_child(ast_node, (yyvsp[-5].astnode));	// ParamList
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// VarDeclList
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));	// Statements

		ast_node->symbol = symbol_new(NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 17:
#line 248 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 18:
#line 252 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 19:
#line 254 "parser.y"
    {
		AstNode* ast_node = ast_node_new("ParamList", PARAM_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 20:
#line 263 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 21:
#line 265 "parser.y"
    {
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		(yyval.astnode) = (yyvsp[-1].astnode);
	;}
    break;

  case 22:
#line 272 "parser.y"
    {
		AstNode* ast_node = ast_node_new("Parameter", PARAMETER, (yyvsp[0].type), yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// Identifier
		(yyval.astnode) = ast_node;
	;}
    break;

  case 23:
#line 280 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 24:
#line 281 "parser.y"
    { (yyval.astnode) = (yyvsp[-2].astnode); ;}
    break;

  case 25:
#line 285 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 26:
#line 286 "parser.y"
    { (yyval.astnode) = (yyvsp[-1].astnode); ;}
    break;

  case 27:
#line 290 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 28:
#line 292 "parser.y"
    {
		AstNode* ast_node = ast_node_new("StatementList", STATEMENT_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[0].astnode));

		(yyval.astnode) = ast_node;
	;}
    break;

  case 29:
#line 299 "parser.y"
    {
		AstNode* ast_node = (yyvsp[0].astnode);
		if (!ast_node)	{
			ast_node = ast_node_new("StatementList", STATEMENT_LIST, VOID, yylloc.last_line, NULL);
		}
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 30:
#line 310 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 31:
#line 311 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 32:
#line 312 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 33:
#line 316 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 34:
#line 317 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 35:
#line 318 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 36:
#line 319 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 37:
#line 320 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 38:
#line 321 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 39:
#line 325 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 40:
#line 327 "parser.y"
    {
		AstNode* ast_node = ast_node_new("IfStatement", IF_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-4].astnode));	// Expression
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// StatementMatched
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// StatementUnmatched
		(yyval.astnode) = ast_node;
	;}
    break;

  case 41:
#line 338 "parser.y"
    {
		AstNode* ast_node = ast_node_new("IfStatement", IF_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// Expression
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// Statements
		(yyval.astnode) = ast_node;
	;}
    break;

  case 42:
#line 348 "parser.y"
    {
		AstNode* ast_node = ast_node_new("IfStatement", IF_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-4].astnode));	// Expression
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// StatementMatched true
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// StatementMatched false
		(yyval.astnode) = ast_node;
	;}
    break;

  case 43:
#line 358 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 44:
#line 359 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 45:
#line 360 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 46:
#line 361 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 47:
#line 366 "parser.y"
    {
		AstNode* ast_node = ast_node_new("PrintIntStatement", PRINTINT_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 48:
#line 375 "parser.y"
    {
		AstNode* ast_node = ast_node_new("PrintCharStatement", PRINTCHAR_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 49:
#line 384 "parser.y"
    {
		AstNode* ast_node = ast_node_new("PrintBoolStatement", PRINTBOOL_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 50:
#line 393 "parser.y"
    {
		AstNode* ast_node = ast_node_new("PrintLineStatement", PRINTLINE_STMT, VOID, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 51:
#line 401 "parser.y"
    {
		AstNode* ast_node = ast_node_new("Assignment", ASSIGNMENT_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));
		ast_node_add_child(ast_node, (yyvsp[0].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 52:
#line 411 "parser.y"
    {
		AstNode* ast_node = ast_node_new("WhileStatement", WHILE_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));
		ast_node_add_child(ast_node, (yyvsp[0].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 53:
#line 421 "parser.y"
    {
		AstNode* ast_node = ast_node_new("ForStatement", FOR_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-4].astnode));	// Assignment
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// Expression
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// Statements
		(yyval.astnode) = ast_node;
	;}
    break;

  case 54:
#line 430 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 55:
#line 432 "parser.y"
    {
		AstNode* ast_node = ast_node_new("RelExpression", REL_EXPR, BOOLEAN, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// LH Expression
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));	// Relop
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// RH Expression
		(yyval.astnode) = ast_node;
	;}
    break;

  case 56:
#line 442 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 57:
#line 444 "parser.y"
    {
		AstNode* ast_node;
		Type type = ((AstNode*)(yyvsp[-1].astnode))->type;
		ast_node = ast_node_new("AddExpression", ADD_EXPR, type, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// LH Expression
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));	// AddOp (+/-)
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// Term
		(yyval.astnode) = ast_node;
	;}
    break;

  case 58:
#line 456 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 59:
#line 458 "parser.y"
    {
		AstNode* ast_node;
		Type type = ((AstNode*)(yyvsp[-1].astnode))->type;
		ast_node = ast_node_new("MulExpression", MUL_EXPR, type, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// Term
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));	// MulOp (*//)
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// NotFactor
		(yyval.astnode) = ast_node;
	;}
    break;

  case 60:
#line 470 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 61:
#line 472 "parser.y"
    {
		AstNode* ast_node = ast_node_new("NotFactor", NOTFACTOR, BOOLEAN, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[0].astnode));
		(yyval.astnode) = ast_node; 
	;}
    break;

  case 62:
#line 480 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 63:
#line 481 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 64:
#line 482 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 65:
#line 483 "parser.y"
    { (yyval.astnode) = (yyvsp[-1].astnode); ;}
    break;

  case 66:
#line 488 "parser.y"
    {
		AstNode* ast_node = ast_node_new("Call", CALL, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-3].astnode));	// Identifier
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));	// Parameters
		(yyval.astnode) = ast_node;
	;}
    break;

  case 67:
#line 497 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 68:
#line 499 "parser.y"
    {
		AstNode* ast_node = ast_node_new("CallParamList", CALLPARAM_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 69:
#line 508 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 70:
#line 510 "parser.y"
    {
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		(yyval.astnode) = (yyvsp[-1].astnode);
	;}
    break;

  case 71:
#line 518 "parser.y"
    {
		AstNode* ast_node = ast_node_new("CallParameter", CALLPARAM, ((AstNode*)(yyvsp[0].astnode))->type, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[0].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 72:
#line 527 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_PLUS, INTEGER, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 73:
#line 532 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_MINUS, INTEGER, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;	
	;}
    break;

  case 74:
#line 537 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_OR, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 75:
#line 545 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_STAR, INTEGER, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 76:
#line 550 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_SLASH, INTEGER, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 77:
#line 555 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_AND, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 78:
#line 563 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_LESSER, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 79:
#line 568 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_LESSEREQUAL, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 80:
#line 573 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_GREATER, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 81:
#line 578 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_GREATEREQUAL, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 82:
#line 583 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_EQUAL, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 83:
#line 588 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_NOTEQUAL, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 84:
#line 595 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 85:
#line 600 "parser.y"
    {
		AstNode* ast_node = ast_node_new("Identifier", IDENTIFIER, VOID, yylloc.last_line, NULL);
		ast_node->symbol = symbol_new((yyvsp[0].lexeme));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 86:
#line 609 "parser.y"
    {
		AstNode* ast_node = ast_node_new("IntLiteral", INT_LITERAL, INTEGER, yylloc.last_line, NULL);
		value_set_from_int(&ast_node->value, (yyvsp[0].integer));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 87:
#line 615 "parser.y"
    {
		AstNode* ast_node = ast_node_new("BoolLiteral", BOOL_LITERAL, BOOLEAN, yylloc.last_line, NULL);
		value_set_from_bool(&ast_node->value, (yyvsp[0].boolean));
		(yyval.astnode) = ast_node;		
	;}
    break;

  case 88:
#line 621 "parser.y"
    {
		AstNode* ast_node = ast_node_new("CharLiteral", CHAR_LITERAL, CHAR, yylloc.last_line, NULL);
		value_set_from_char(&ast_node->value, (yyvsp[0].character));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 89:
#line 627 "parser.y"
    {
		AstNode* ast_node = ast_node_new("FloatLiteral", FLOAT_LITERAL, FLOAT, yylloc.last_line, NULL);
		value_set_from_float(&ast_node->value, (yyvsp[0].flt));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 90:
#line 633 "parser.y"
    {
		AstNode* ast_node = ast_node_new("DoubleLiteral", DOUBLE_LITERAL, DOUBLE, yylloc.last_line, NULL);
		value_set_from_double(&ast_node->value, (yyvsp[0].dbl));
		(yyval.astnode) = ast_node;
	;}
    break;


    }

/* Line 1037 of yacc.c.  */
#line 1984 "parser.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;
  yylsp -= yylen;

  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {
                 yyerror_range[0] = *yylsp;
		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 yydestruct ("Error: popping",
                             yystos[*yyssp], yyvsp, yylsp);
	       }
        }
      else
	{
	  yydestruct ("Error: discarding", yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyerror_range[0] = yylsp[1-yylen];
  yylsp -= yylen;
  yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping", yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though. */
  YYLLOC_DEFAULT (yyloc, yyerror_range - 1, 2);
  *++yylsp = yyloc;

  /* Shift the error token. */
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
  yydestruct ("Error: discarding lookahead",
              yytoken, &yylval, &yylloc);
  yychar = YYEMPTY;
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 640 "parser.y"


static void yyerror(const char* msg)
{
	fprintf(stderr, "Error: line %d: %s\n", yyget_lineno(), msg);
}

