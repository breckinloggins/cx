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
     T_PROGRAM = 271,
     T_VAR = 272,
     T_PROCEDURE = 273,
     T_FUNCTION = 274,
     T_BEGIN = 275,
     T_END = 276,
     T_IF = 277,
     T_THEN = 278,
     T_ELSE = 279,
     T_WHILE = 280,
     T_FOR = 281,
     T_TO = 282,
     T_DO = 283,
     T_ASSIGNMENT = 284,
     T_LPAR = 285,
     T_RPAR = 286,
     T_SEMICOLON = 287,
     T_COLON = 288,
     T_COMMA = 289,
     T_DOT = 290,
     T_PRINT_INT = 291,
     T_PRINT_CHAR = 292,
     T_PRINT_BOOL = 293,
     T_PRINT_LINE = 294,
     TYPE_IDENTIFIER = 295,
     IDENTIFIER = 296,
     INT_LITERAL = 297,
     BOOL_LITERAL = 298,
     CHAR_LITERAL = 299
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
#define T_PROGRAM 271
#define T_VAR 272
#define T_PROCEDURE 273
#define T_FUNCTION 274
#define T_BEGIN 275
#define T_END 276
#define T_IF 277
#define T_THEN 278
#define T_ELSE 279
#define T_WHILE 280
#define T_FOR 281
#define T_TO 282
#define T_DO 283
#define T_ASSIGNMENT 284
#define T_LPAR 285
#define T_RPAR 286
#define T_SEMICOLON 287
#define T_COLON 288
#define T_COMMA 289
#define T_DOT 290
#define T_PRINT_INT 291
#define T_PRINT_CHAR 292
#define T_PRINT_BOOL 293
#define T_PRINT_LINE 294
#define TYPE_IDENTIFIER 295
#define IDENTIFIER 296
#define INT_LITERAL 297
#define BOOL_LITERAL 298
#define CHAR_LITERAL 299




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

bool simple_flag = FALSE;
bool c_flag = FALSE;

int opts;

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
#line 31 "parser.y"
typedef union YYSTYPE {
	char* lexeme;
	int integer;
	int boolean;
	char character;
	int type;
	struct AstNode_tag* astnode;
} YYSTYPE;
/* Line 185 of yacc.c.  */
#line 198 "parser.tab.c"
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
#line 222 "parser.tab.c"

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
#define YYLAST   172

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  49
/* YYNRULES -- Number of rules. */
#define YYNRULES  92
/* YYNRULES -- Number of states. */
#define YYNSTATES  171

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
       0,     0,     3,     8,    12,    13,    16,    17,    20,    26,
      29,    30,    34,    36,    37,    40,    41,    44,    46,    48,
      60,    74,    75,    78,    79,    83,    87,    88,    93,    95,
      99,   100,   103,   104,   108,   110,   112,   114,   116,   118,
     120,   122,   124,   126,   128,   135,   140,   147,   149,   151,
     153,   155,   160,   165,   170,   174,   178,   183,   190,   192,
     196,   198,   202,   204,   208,   210,   213,   215,   217,   219,
     223,   228,   229,   232,   233,   237,   239,   241,   243,   245,
     247,   249,   251,   253,   255,   257,   259,   261,   263,   265,
     267,   269,   271
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      46,     0,    -1,    47,    48,    54,    62,    -1,    16,    92,
      32,    -1,    -1,    50,    49,    -1,    -1,    50,    49,    -1,
      17,    51,    33,    40,    32,    -1,    53,    52,    -1,    -1,
      34,    53,    52,    -1,    92,    -1,    -1,    56,    55,    -1,
      -1,    56,    55,    -1,    57,    -1,    58,    -1,    18,    92,
      30,    59,    31,    32,    48,    20,    64,    21,    32,    -1,
      19,    92,    30,    59,    31,    33,    40,    32,    48,    20,
      64,    21,    32,    -1,    -1,    61,    60,    -1,    -1,    34,
      61,    60,    -1,    92,    33,    40,    -1,    -1,    20,    64,
      21,    35,    -1,    66,    -1,    20,    64,    21,    -1,    -1,
      66,    65,    -1,    -1,    32,    66,    65,    -1,    67,    -1,
      68,    -1,    32,    -1,    76,    -1,    70,    -1,    77,    -1,
      78,    -1,    84,    -1,    71,    -1,    69,    -1,    22,    79,
      23,    67,    24,    68,    -1,    22,    79,    23,    63,    -1,
      22,    79,    23,    67,    24,    67,    -1,    72,    -1,    73,
      -1,    74,    -1,    75,    -1,    36,    30,    79,    31,    -1,
      37,    30,    79,    31,    -1,    38,    30,    79,    31,    -1,
      39,    30,    31,    -1,    92,    29,    79,    -1,    25,    79,
      28,    63,    -1,    26,    76,    27,    79,    28,    63,    -1,
      80,    -1,    80,    90,    80,    -1,    81,    -1,    80,    88,
      81,    -1,    82,    -1,    81,    89,    82,    -1,    83,    -1,
      91,    83,    -1,    92,    -1,    93,    -1,    84,    -1,    30,
      79,    31,    -1,    92,    30,    85,    31,    -1,    -1,    87,
      86,    -1,    -1,    34,    87,    86,    -1,    79,    -1,    12,
      -1,    11,    -1,     3,    -1,    14,    -1,    13,    -1,     4,
      -1,    10,    -1,     8,    -1,     9,    -1,     7,    -1,     6,
      -1,     5,    -1,    15,    -1,    41,    -1,    42,    -1,    43,
      -1,    44,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   144,   144,   159,   168,   169,   178,   179,   187,   196,
     206,   207,   215,   219,   220,   230,   231,   239,   240,   244,
     260,   276,   277,   287,   288,   295,   304,   305,   309,   310,
     314,   315,   325,   326,   334,   335,   336,   340,   341,   342,
     343,   344,   345,   349,   350,   361,   371,   382,   383,   384,
     385,   389,   398,   407,   416,   424,   434,   444,   454,   455,
     466,   467,   480,   481,   494,   495,   504,   505,   506,   507,
     511,   521,   522,   532,   533,   541,   550,   555,   560,   568,
     573,   578,   586,   591,   596,   601,   606,   611,   619,   623,
     632,   638,   644
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_OR", "T_AND", "T_NOTEQUAL", "T_EQUAL",
  "T_GREATEREQUAL", "T_LESSEREQUAL", "T_GREATER", "T_LESSER", "T_MINUS",
  "T_PLUS", "T_SLASH", "T_STAR", "T_NOT", "T_PROGRAM", "T_VAR",
  "T_PROCEDURE", "T_FUNCTION", "T_BEGIN", "T_END", "T_IF", "T_THEN",
  "T_ELSE", "T_WHILE", "T_FOR", "T_TO", "T_DO", "T_ASSIGNMENT", "T_LPAR",
  "T_RPAR", "T_SEMICOLON", "T_COLON", "T_COMMA", "T_DOT", "T_PRINT_INT",
  "T_PRINT_CHAR", "T_PRINT_BOOL", "T_PRINT_LINE", "TYPE_IDENTIFIER",
  "IDENTIFIER", "INT_LITERAL", "BOOL_LITERAL", "CHAR_LITERAL", "$accept",
  "Program", "ProgramDecl", "VarDeclList", "MultiVarDecl", "VarDecl",
  "IdentifierList", "MultiIdentifier", "SingleIdentifier", "ProcFuncList",
  "MultiProcFuncDecl", "ProcFuncDecl", "ProcDecl", "FuncDecl", "ParamList",
  "MultiParam", "SingleParam", "ProgramBody", "Statements",
  "StatementList", "MultiStatement", "Statement", "StatementMatched",
  "StatementUnmatched", "IfStatement", "IfStatementMatched",
  "PrintStatement", "PrintIntStatement", "PrintCharStatement",
  "PrintBoolStatement", "PrintLineStatement", "Assignment",
  "WhileStatement", "ForStatement", "Expression", "SimpleExpression",
  "Term", "NotFactor", "Factor", "Call", "CallParamList",
  "MultiCallParameter", "CallParameter", "AddOp", "MulOp", "RelOp",
  "NotOp", "Identifier", "Literal", 0
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
       0,    45,    46,    47,    48,    48,    49,    49,    50,    51,
      52,    52,    53,    54,    54,    55,    55,    56,    56,    57,
      58,    59,    59,    60,    60,    61,    62,    62,    63,    63,
      64,    64,    65,    65,    66,    66,    66,    67,    67,    67,
      67,    67,    67,    68,    68,    69,    70,    71,    71,    71,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    79,
      80,    80,    81,    81,    82,    82,    83,    83,    83,    83,
      84,    85,    85,    86,    86,    87,    88,    88,    88,    89,
      89,    89,    90,    90,    90,    90,    90,    90,    91,    92,
      93,    93,    93
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     4,     3,     0,     2,     0,     2,     5,     2,
       0,     3,     1,     0,     2,     0,     2,     1,     1,    11,
      13,     0,     2,     0,     3,     3,     0,     4,     1,     3,
       0,     2,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     6,     4,     6,     1,     1,     1,
       1,     4,     4,     4,     3,     3,     4,     6,     1,     3,
       1,     3,     1,     3,     1,     2,     1,     1,     1,     3,
       4,     0,     2,     0,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     4,    89,     0,     1,     0,    13,     6,
       3,     0,    10,    12,     0,     0,    26,    15,    17,    18,
       5,     6,     0,     0,     9,     0,     0,    30,     2,    14,
      15,     7,     0,    10,    21,    21,     0,     0,     0,    36,
       0,     0,     0,     0,     0,    32,    34,    35,    43,    38,
      42,    47,    48,    49,    50,    37,    39,    40,    41,     0,
      16,     8,    11,     0,    23,     0,     0,    88,     0,    90,
      91,    92,     0,    58,    60,    62,    64,    68,     0,    66,
      67,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      31,     0,    71,     0,     0,    22,     0,     0,     0,     0,
      78,    87,    86,    85,    83,    84,    82,    77,    76,     0,
       0,    81,    80,    79,     0,    65,     0,     0,     0,     0,
       0,    54,    27,    32,    55,    75,     0,    73,     4,    23,
      25,     0,    69,    30,    45,    28,    34,    61,    59,    63,
      56,     0,    51,    52,    53,    33,    70,     0,    72,     0,
      24,     0,     0,     0,     0,    73,    30,     4,    29,    46,
      44,    57,    74,     0,     0,     0,    30,    19,     0,     0,
      20
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     2,     3,     8,    20,     9,    11,    24,    12,    16,
      29,    30,    18,    19,    63,    95,    64,    28,   134,    44,
      90,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,   125,    73,    74,    75,    76,    77,
     126,   148,   127,   109,   114,   110,    78,    79,    80
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -126
static const short int yypact[] =
{
       4,   -14,    28,    15,  -126,    12,  -126,   -14,    -2,    15,
    -126,    -3,     8,  -126,   -14,   -14,    26,    -2,  -126,  -126,
    -126,    15,    21,   -14,  -126,    34,    38,    80,  -126,  -126,
      -2,  -126,    37,     8,   -14,   -14,     6,     6,   -14,  -126,
      41,    44,    45,    50,    49,    51,  -126,  -126,  -126,  -126,
    -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,    10,
    -126,  -126,  -126,    54,    48,    53,    56,  -126,     6,  -126,
    -126,  -126,    66,   138,    11,  -126,  -126,  -126,    13,    61,
    -126,    64,    67,    68,     6,     6,     6,    65,    60,    80,
    -126,     6,     6,    69,   -14,  -126,    59,    70,    73,    40,
    -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,     6,
       6,  -126,  -126,  -126,     6,  -126,    40,     6,    77,    78,
      79,  -126,  -126,    51,  -126,  -126,    82,    88,    15,    48,
    -126,    71,  -126,    80,  -126,  -126,    76,    11,     7,  -126,
    -126,    86,  -126,  -126,  -126,  -126,  -126,     6,  -126,   105,
    -126,    94,   108,    98,    40,    88,    80,    15,  -126,  -126,
    -126,  -126,  -126,   110,   113,   106,    80,  -126,   121,   119,
    -126
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -126,  -126,  -126,  -119,   133,     2,  -126,   123,   134,  -126,
     128,   151,  -126,  -126,   125,    32,    72,  -126,  -109,  -125,
      39,   -87,   -94,    14,  -126,  -126,  -126,  -126,  -126,  -126,
    -126,   126,  -126,  -126,   -33,    58,    62,    55,    85,   -26,
    -126,    17,    23,  -126,  -126,  -126,  -126,    -1,  -126
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
       5,    58,   123,    72,    81,   136,    13,   140,   152,   149,
     100,    21,   135,    25,    26,   111,    14,    15,   107,   108,
       1,    67,    13,    21,   112,   113,    59,     4,     6,   135,
      22,   163,     7,    65,    65,    98,    68,    83,   164,    91,
      92,   168,    23,    68,    10,   161,    27,     4,    69,    70,
      71,   118,   119,   120,     4,    69,    70,    71,   124,   159,
     133,    32,    36,    58,    34,    37,    38,   135,    35,    61,
      88,    84,    39,    58,    85,    86,    40,    41,    42,    43,
      87,     4,    94,    89,   141,    93,    96,    97,    59,    99,
      58,    92,   116,    65,   117,   122,   121,    91,    59,   130,
     153,   128,    36,   131,   132,    37,    38,    58,   142,   143,
     144,   151,    39,   146,   154,    59,    40,    41,    42,    43,
      36,     4,   147,    37,    38,   156,   157,    58,    58,   158,
      58,   165,    59,   166,    40,    41,    42,    43,   167,     4,
      58,   100,   169,   101,   102,   103,   104,   105,   106,   107,
     108,   170,    59,    59,    31,    59,    62,    33,    60,    17,
      66,   150,   145,   115,    82,    59,   129,   160,   138,   139,
     155,   137,   162
};

static const unsigned char yycheck[] =
{
       1,    27,    89,    36,    37,    99,     7,   116,   133,   128,
       3,     9,    99,    14,    15,     4,    18,    19,    11,    12,
      16,    15,    23,    21,    13,    14,    27,    41,     0,   116,
      33,   156,    17,    34,    35,    68,    30,    38,   157,    29,
      30,   166,    34,    30,    32,   154,    20,    41,    42,    43,
      44,    84,    85,    86,    41,    42,    43,    44,    91,   153,
      20,    40,    22,    89,    30,    25,    26,   154,    30,    32,
      21,    30,    32,    99,    30,    30,    36,    37,    38,    39,
      30,    41,    34,    32,   117,    31,    33,    31,    89,    23,
     116,    30,    28,    94,    27,    35,    31,    29,    99,    40,
      24,    32,    22,    33,    31,    25,    26,   133,    31,    31,
      31,    40,    32,    31,    28,   116,    36,    37,    38,    39,
      22,    41,    34,    25,    26,    20,    32,   153,   154,    21,
     156,    21,   133,    20,    36,    37,    38,    39,    32,    41,
     166,     3,    21,     5,     6,     7,     8,     9,    10,    11,
      12,    32,   153,   154,    21,   156,    33,    23,    30,     8,
      35,   129,   123,    78,    38,   166,    94,   153,   110,   114,
     147,   109,   155
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    16,    46,    47,    41,    92,     0,    17,    48,    50,
      32,    51,    53,    92,    18,    19,    54,    56,    57,    58,
      49,    50,    33,    34,    52,    92,    92,    20,    62,    55,
      56,    49,    40,    53,    30,    30,    22,    25,    26,    32,
      36,    37,    38,    39,    64,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    84,    92,
      55,    32,    52,    59,    61,    92,    59,    15,    30,    42,
      43,    44,    79,    80,    81,    82,    83,    84,    91,    92,
      93,    79,    76,    92,    30,    30,    30,    30,    21,    32,
      65,    29,    30,    31,    34,    60,    33,    31,    79,    23,
       3,     5,     6,     7,     8,     9,    10,    11,    12,    88,
      90,     4,    13,    14,    89,    83,    28,    27,    79,    79,
      79,    31,    35,    66,    79,    79,    85,    87,    32,    61,
      40,    33,    31,    20,    63,    66,    67,    81,    80,    82,
      63,    79,    31,    31,    31,    65,    31,    34,    86,    48,
      60,    40,    64,    24,    28,    87,    20,    32,    21,    67,
      68,    63,    86,    64,    48,    21,    20,    32,    64,    21,
      32
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
#line 145 "parser.y"
    {
		AstNode* ast_node = ast_node_new("Program", PROGRAM, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-3].astnode));	// ProgramDecl
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// VarDeclList
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));	// ProcFuncList
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// ProgramBody
		
		(yyval.astnode) = ast_node;
		
		ast = ast_node;
	;}
    break;

  case 3:
#line 160 "parser.y"
    {
		AstNode* ast_node = ast_node_new("ProgramDecl", PROGRAM_DECL, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 4:
#line 168 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 5:
#line 170 "parser.y"
    {
		AstNode* ast_node = ast_node_new("VarDeclList", VARDECL_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 6:
#line 178 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 7:
#line 180 "parser.y"
    {
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		(yyval.astnode) = (yyvsp[-1].astnode);
	;}
    break;

  case 8:
#line 188 "parser.y"
    {
		AstNode* ast_node = ast_node_new("VarDecl", VARDECL, (yyvsp[-1].type), yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-3].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 9:
#line 197 "parser.y"
    {
		AstNode* ast_node = ast_node_new("IdentifierList", IDENT_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 10:
#line 206 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 11:
#line 208 "parser.y"
    {
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		(yyval.astnode) = (yyvsp[-1].astnode);
	;}
    break;

  case 12:
#line 215 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 13:
#line 219 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 14:
#line 221 "parser.y"
    {
		AstNode* ast_node = ast_node_new("ProcFuncList", PROCFUNC_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 15:
#line 230 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 16:
#line 232 "parser.y"
    {
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		(yyval.astnode) = (yyvsp[-1].astnode);
	;}
    break;

  case 17:
#line 239 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 18:
#line 240 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 19:
#line 246 "parser.y"
    {
		Symbol* symtab;
		AstNode* ast_node = ast_node_new("ProcDecl", PROCEDURE, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-9].astnode));	// Identifier
		ast_node_add_child(ast_node, (yyvsp[-7].astnode));	// ParamList
		ast_node_add_child(ast_node, (yyvsp[-4].astnode));	// VarDeclList
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// Statements
		
		ast_node->symbol = symbol_new(NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 20:
#line 262 "parser.y"
    {
		Symbol* symtab;
		AstNode* ast_node = ast_node_new("FuncDecl", FUNCTION, (yyvsp[-6].type), yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-11].astnode));	// Identifier
		ast_node_add_child(ast_node, (yyvsp[-9].astnode));	// ParamList
		ast_node_add_child(ast_node, (yyvsp[-4].astnode));	// VarDeclList
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// Statements

		ast_node->symbol = symbol_new(NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 21:
#line 276 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 22:
#line 278 "parser.y"
    {
		AstNode* ast_node = ast_node_new("ParamList", PARAM_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 23:
#line 287 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 24:
#line 289 "parser.y"
    {
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		(yyval.astnode) = (yyvsp[-1].astnode);
	;}
    break;

  case 25:
#line 296 "parser.y"
    {
		AstNode* ast_node = ast_node_new("Parameter", PARAMETER, (yyvsp[0].type), yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// Identifier
		(yyval.astnode) = ast_node;
	;}
    break;

  case 26:
#line 304 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 27:
#line 305 "parser.y"
    { (yyval.astnode) = (yyvsp[-2].astnode); ;}
    break;

  case 28:
#line 309 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 29:
#line 310 "parser.y"
    { (yyval.astnode) = (yyvsp[-1].astnode); ;}
    break;

  case 30:
#line 314 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 31:
#line 316 "parser.y"
    {
		AstNode* ast_node = ast_node_new("StatementList", STATEMENT_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 32:
#line 325 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 33:
#line 327 "parser.y"
    {
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		(yyval.astnode) = (yyvsp[-1].astnode);
	;}
    break;

  case 34:
#line 334 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 35:
#line 335 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 36:
#line 336 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 37:
#line 340 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 38:
#line 341 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 39:
#line 342 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 40:
#line 343 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 41:
#line 344 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 42:
#line 345 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 43:
#line 349 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 44:
#line 351 "parser.y"
    {
		AstNode* ast_node = ast_node_new("IfStatement", IF_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-4].astnode));	// Expression
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// StatementMatched
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// StatementUnmatched
		(yyval.astnode) = ast_node;
	;}
    break;

  case 45:
#line 362 "parser.y"
    {
		AstNode* ast_node = ast_node_new("IfStatement", IF_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// Expression
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// Statements
		(yyval.astnode) = ast_node;
	;}
    break;

  case 46:
#line 372 "parser.y"
    {
		AstNode* ast_node = ast_node_new("IfStatement", IF_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-4].astnode));	// Expression
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// StatementMatched true
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// StatementMatched false
		(yyval.astnode) = ast_node;
	;}
    break;

  case 47:
#line 382 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 48:
#line 383 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 49:
#line 384 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 50:
#line 385 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 51:
#line 390 "parser.y"
    {
		AstNode* ast_node = ast_node_new("PrintIntStatement", PRINTINT_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 52:
#line 399 "parser.y"
    {
		AstNode* ast_node = ast_node_new("PrintCharStatement", PRINTCHAR_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 53:
#line 408 "parser.y"
    {
		AstNode* ast_node = ast_node_new("PrintBoolStatement", PRINTBOOL_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 54:
#line 417 "parser.y"
    {
		AstNode* ast_node = ast_node_new("PrintLineStatement", PRINTLINE_STMT, VOID, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 55:
#line 425 "parser.y"
    {
		AstNode* ast_node = ast_node_new("Assignment", ASSIGNMENT_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));
		ast_node_add_child(ast_node, (yyvsp[0].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 56:
#line 435 "parser.y"
    {
		AstNode* ast_node = ast_node_new("WhileStatement", WHILE_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));
		ast_node_add_child(ast_node, (yyvsp[0].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 57:
#line 445 "parser.y"
    {
		AstNode* ast_node = ast_node_new("ForStatement", FOR_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-4].astnode));	// Assignment
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// Expression
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// Statements
		(yyval.astnode) = ast_node;
	;}
    break;

  case 58:
#line 454 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 59:
#line 456 "parser.y"
    {
		AstNode* ast_node = ast_node_new("RelExpression", REL_EXPR, BOOLEAN, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// LH Expression
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));	// Relop
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// RH Expression
		(yyval.astnode) = ast_node;
	;}
    break;

  case 60:
#line 466 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 61:
#line 468 "parser.y"
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

  case 62:
#line 480 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 63:
#line 482 "parser.y"
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

  case 64:
#line 494 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 65:
#line 496 "parser.y"
    {
		AstNode* ast_node = ast_node_new("NotFactor", NOTFACTOR, BOOLEAN, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[0].astnode));
		(yyval.astnode) = ast_node; 
	;}
    break;

  case 66:
#line 504 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 67:
#line 505 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 68:
#line 506 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 69:
#line 507 "parser.y"
    { (yyval.astnode) = (yyvsp[-1].astnode); ;}
    break;

  case 70:
#line 512 "parser.y"
    {
		AstNode* ast_node = ast_node_new("Call", CALL, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-3].astnode));	// Identifier
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));	// Parameters
		(yyval.astnode) = ast_node;
	;}
    break;

  case 71:
#line 521 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 72:
#line 523 "parser.y"
    {
		AstNode* ast_node = ast_node_new("CallParamList", CALLPARAM_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 73:
#line 532 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 74:
#line 534 "parser.y"
    {
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		(yyval.astnode) = (yyvsp[-1].astnode);
	;}
    break;

  case 75:
#line 542 "parser.y"
    {
		AstNode* ast_node = ast_node_new("CallParameter", CALLPARAM, ((AstNode*)(yyvsp[0].astnode))->type, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[0].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 76:
#line 551 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_PLUS, INTEGER, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 77:
#line 556 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_MINUS, INTEGER, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;	
	;}
    break;

  case 78:
#line 561 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_OR, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 79:
#line 569 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_STAR, INTEGER, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 80:
#line 574 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_SLASH, INTEGER, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 81:
#line 579 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_AND, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 82:
#line 587 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_LESSER, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 83:
#line 592 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_LESSEREQUAL, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 84:
#line 597 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_GREATER, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 85:
#line 602 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_GREATEREQUAL, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 86:
#line 607 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_EQUAL, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 87:
#line 612 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_NOTEQUAL, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 88:
#line 619 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 89:
#line 624 "parser.y"
    {
		AstNode* ast_node = ast_node_new("Identifier", IDENTIFIER, VOID, yylloc.last_line, NULL);
		ast_node->symbol = symbol_new((yyvsp[0].lexeme));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 90:
#line 633 "parser.y"
    {
		AstNode* ast_node = ast_node_new("IntLiteral", INT_LITERAL, INTEGER, yylloc.last_line, NULL);
		value_set_from_int(&ast_node->value, (yyvsp[0].integer));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 91:
#line 639 "parser.y"
    {
		AstNode* ast_node = ast_node_new("BoolLiteral", BOOL_LITERAL, BOOLEAN, yylloc.last_line, NULL);
		value_set_from_bool(&ast_node->value, (yyvsp[0].boolean));
		(yyval.astnode) = ast_node;		
	;}
    break;

  case 92:
#line 645 "parser.y"
    {
		AstNode* ast_node = ast_node_new("CharLiteral", CHAR_LITERAL, CHAR, yylloc.last_line, NULL);
		value_set_from_char(&ast_node->value, (yyvsp[0].character));
		(yyval.astnode) = ast_node;
	;}
    break;


    }

/* Line 1037 of yacc.c.  */
#line 2000 "parser.tab.c"

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


#line 652 "parser.y"


static void yyerror(const char* msg)
{
	fprintf(stderr, "Error: line %d: %s\n", yyget_lineno(), msg);
}

