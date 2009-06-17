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
     T_PROCEDURE = 273,
     T_FUNCTION = 274,
     T_IF = 275,
     T_ELSE = 276,
     T_WHILE = 277,
     T_FOR = 278,
     T_TO = 279,
     T_DO = 280,
     T_ASSIGNMENT = 281,
     T_LPAR = 282,
     T_RPAR = 283,
     T_LBRACK = 284,
     T_RBRACK = 285,
     T_SEMICOLON = 286,
     T_COLON = 287,
     T_COMMA = 288,
     T_DOT = 289,
     T_PRINT_INT = 290,
     T_PRINT_CHAR = 291,
     T_PRINT_BOOL = 292,
     T_PRINT_LINE = 293,
     TYPE_IDENTIFIER = 294,
     IDENTIFIER = 295,
     INT_LITERAL = 296,
     BOOL_LITERAL = 297,
     CHAR_LITERAL = 298,
     DOUBLE_LITERAL = 299,
     FLOAT_LITERAL = 300
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
#define T_PROCEDURE 273
#define T_FUNCTION 274
#define T_IF 275
#define T_ELSE 276
#define T_WHILE 277
#define T_FOR 278
#define T_TO 279
#define T_DO 280
#define T_ASSIGNMENT 281
#define T_LPAR 282
#define T_RPAR 283
#define T_LBRACK 284
#define T_RBRACK 285
#define T_SEMICOLON 286
#define T_COLON 287
#define T_COMMA 288
#define T_DOT 289
#define T_PRINT_INT 290
#define T_PRINT_CHAR 291
#define T_PRINT_BOOL 292
#define T_PRINT_LINE 293
#define TYPE_IDENTIFIER 294
#define IDENTIFIER 295
#define INT_LITERAL 296
#define BOOL_LITERAL 297
#define CHAR_LITERAL 298
#define DOUBLE_LITERAL 299
#define FLOAT_LITERAL 300




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
#line 197 "parser.tab.c"
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
#line 221 "parser.tab.c"

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
#define YYLAST   180

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  47
/* YYNRULES -- Number of rules. */
#define YYNRULES  92
/* YYNRULES -- Number of states. */
#define YYNSTATES  171

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     5,    13,    14,    16,    20,    23,    26,
      27,    31,    33,    34,    37,    38,    41,    43,    45,    57,
      71,    72,    75,    76,    80,    84,    85,    90,    92,    96,
      97,    99,   103,   105,   107,   109,   111,   113,   115,   117,
     119,   121,   123,   131,   137,   145,   147,   149,   151,   153,
     158,   163,   168,   172,   176,   182,   190,   192,   196,   198,
     202,   204,   208,   210,   213,   215,   217,   219,   223,   228,
     229,   232,   233,   237,   239,   241,   243,   245,   247,   249,
     251,   253,   255,   257,   259,   261,   263,   265,   267,   269,
     271,   273,   275
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      47,     0,    -1,    48,    -1,    16,    91,    29,    49,    54,
      62,    30,    -1,    -1,    50,    -1,    50,    31,    49,    -1,
      39,    51,    -1,    53,    52,    -1,    -1,    33,    53,    52,
      -1,    91,    -1,    -1,    56,    55,    -1,    -1,    56,    55,
      -1,    57,    -1,    58,    -1,    18,    91,    27,    59,    28,
      31,    49,    29,    64,    30,    31,    -1,    19,    91,    27,
      59,    28,    32,    39,    31,    49,    29,    64,    30,    31,
      -1,    -1,    61,    60,    -1,    -1,    33,    61,    60,    -1,
      91,    32,    39,    -1,    -1,    29,    64,    30,    34,    -1,
      65,    -1,    29,    64,    30,    -1,    -1,    65,    -1,    65,
      31,    64,    -1,    66,    -1,    67,    -1,    31,    -1,    75,
      -1,    69,    -1,    76,    -1,    77,    -1,    83,    -1,    70,
      -1,    68,    -1,    20,    27,    78,    28,    66,    21,    67,
      -1,    20,    27,    78,    28,    63,    -1,    20,    27,    78,
      28,    66,    21,    66,    -1,    71,    -1,    72,    -1,    73,
      -1,    74,    -1,    35,    27,    78,    28,    -1,    36,    27,
      78,    28,    -1,    37,    27,    78,    28,    -1,    38,    27,
      28,    -1,    91,    26,    78,    -1,    22,    27,    78,    28,
      63,    -1,    23,    27,    75,    24,    78,    28,    63,    -1,
      79,    -1,    79,    89,    79,    -1,    80,    -1,    79,    87,
      80,    -1,    81,    -1,    80,    88,    81,    -1,    82,    -1,
      90,    82,    -1,    91,    -1,    92,    -1,    83,    -1,    27,
      78,    28,    -1,    91,    27,    84,    28,    -1,    -1,    86,
      85,    -1,    -1,    33,    86,    85,    -1,    78,    -1,    12,
      -1,    11,    -1,     3,    -1,    14,    -1,    13,    -1,     4,
      -1,    10,    -1,     8,    -1,     9,    -1,     7,    -1,     6,
      -1,     5,    -1,    15,    -1,    40,    -1,    41,    -1,    42,
      -1,    43,    -1,    45,    -1,    44,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   140,   140,   151,   164,   165,   172,   185,   194,   204,
     205,   213,   217,   218,   228,   229,   237,   238,   242,   258,
     274,   275,   285,   286,   293,   302,   303,   307,   308,   312,
     313,   320,   332,   333,   334,   338,   339,   340,   341,   342,
     343,   347,   348,   359,   369,   380,   381,   382,   383,   387,
     396,   405,   414,   422,   432,   442,   452,   453,   464,   465,
     478,   479,   492,   493,   502,   503,   504,   505,   509,   519,
     520,   530,   531,   539,   548,   553,   558,   566,   571,   576,
     584,   589,   594,   599,   604,   609,   617,   621,   630,   636,
     642,   648,   654
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_OR", "T_AND", "T_NOTEQUAL", "T_EQUAL",
  "T_GREATEREQUAL", "T_LESSEREQUAL", "T_GREATER", "T_LESSER", "T_MINUS",
  "T_PLUS", "T_SLASH", "T_STAR", "T_NOT", "T_NAMESPACE", "T_VAR",
  "T_PROCEDURE", "T_FUNCTION", "T_IF", "T_ELSE", "T_WHILE", "T_FOR",
  "T_TO", "T_DO", "T_ASSIGNMENT", "T_LPAR", "T_RPAR", "T_LBRACK",
  "T_RBRACK", "T_SEMICOLON", "T_COLON", "T_COMMA", "T_DOT", "T_PRINT_INT",
  "T_PRINT_CHAR", "T_PRINT_BOOL", "T_PRINT_LINE", "TYPE_IDENTIFIER",
  "IDENTIFIER", "INT_LITERAL", "BOOL_LITERAL", "CHAR_LITERAL",
  "DOUBLE_LITERAL", "FLOAT_LITERAL", "$accept", "TranslationUnit",
  "NamespaceDecl", "VarDeclList", "VarDecl", "IdentifierList",
  "MultiIdentifier", "SingleIdentifier", "ProcFuncList",
  "MultiProcFuncDecl", "ProcFuncDecl", "ProcDecl", "FuncDecl", "ParamList",
  "MultiParam", "SingleParam", "ProgramBody", "Statements",
  "StatementList", "Statement", "StatementMatched", "StatementUnmatched",
  "IfStatement", "IfStatementMatched", "PrintStatement",
  "PrintIntStatement", "PrintCharStatement", "PrintBoolStatement",
  "PrintLineStatement", "Assignment", "WhileStatement", "ForStatement",
  "Expression", "SimpleExpression", "Term", "NotFactor", "Factor", "Call",
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
     295,   296,   297,   298,   299,   300
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    46,    47,    48,    49,    49,    49,    50,    51,    52,
      52,    53,    54,    54,    55,    55,    56,    56,    57,    58,
      59,    59,    60,    60,    61,    62,    62,    63,    63,    64,
      64,    64,    65,    65,    65,    66,    66,    66,    66,    66,
      66,    67,    67,    68,    69,    70,    70,    70,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    78,    79,    79,
      80,    80,    81,    81,    82,    82,    82,    82,    83,    84,
      84,    85,    85,    86,    87,    87,    87,    88,    88,    88,
      89,    89,    89,    89,    89,    89,    90,    91,    92,    92,
      92,    92,    92
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     7,     0,     1,     3,     2,     2,     0,
       3,     1,     0,     2,     0,     2,     1,     1,    11,    13,
       0,     2,     0,     3,     3,     0,     4,     1,     3,     0,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     7,     5,     7,     1,     1,     1,     1,     4,
       4,     4,     3,     3,     5,     7,     1,     3,     1,     3,
       1,     3,     1,     2,     1,     1,     1,     3,     4,     0,
       2,     0,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     2,    87,     0,     1,     4,     0,    12,
       5,     7,     9,    11,     0,     0,    25,    14,    16,    17,
       4,     0,     8,     0,     0,    29,     0,    13,    14,     6,
       9,    20,    20,     0,     0,     0,    34,     0,     0,     0,
       0,     0,    30,    32,    33,    41,    36,    40,    45,    46,
      47,    48,    35,    37,    38,    39,     0,     3,    15,    10,
       0,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    29,     0,    69,     0,     0,    21,     0,     0,
      86,     0,    88,    89,    90,    92,    91,     0,    56,    58,
      60,    62,    66,     0,    64,    65,     0,     0,     0,     0,
       0,     0,    52,    26,    31,    53,    73,     0,    71,     4,
      22,    24,     0,     0,     0,    76,    85,    84,    83,    81,
      82,    80,    75,    74,     0,     0,    79,    78,    77,     0,
      63,     0,     0,    49,    50,    51,    68,     0,    70,     0,
      23,     0,    67,    29,    43,    27,    32,    59,    57,    61,
      54,     0,    71,    29,     4,     0,     0,     0,    72,     0,
       0,    28,    44,    42,    55,     0,    29,    18,     0,     0,
      19
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     2,     3,     9,    10,    11,    22,    12,    16,    27,
      28,    18,    19,    60,    77,    61,    26,   144,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,   106,    88,    89,    90,    91,    92,   107,   138,
     108,   124,   129,   125,    93,    94,    95
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -126
static const short int yypact[] =
{
     -11,   -25,    16,  -126,  -126,   -12,  -126,   -13,   -25,    -9,
       3,  -126,     4,  -126,   -25,   -25,     7,    -9,  -126,  -126,
     -13,   -25,  -126,    17,    18,    88,    19,  -126,    -9,  -126,
       4,   -25,   -25,    20,    21,    32,  -126,    33,    35,    39,
      40,    22,    12,  -126,  -126,  -126,  -126,  -126,  -126,  -126,
    -126,  -126,  -126,  -126,  -126,  -126,   -15,  -126,  -126,  -126,
      42,    36,    48,    45,    13,    13,   -25,    13,    13,    13,
      46,    34,    88,    13,    13,    52,   -25,  -126,    50,    58,
    -126,    13,  -126,  -126,  -126,  -126,  -126,    56,   161,    25,
    -126,  -126,  -126,   105,    66,  -126,    69,    74,    73,    76,
      78,    79,  -126,  -126,  -126,  -126,  -126,    84,    81,   -13,
      36,  -126,    77,    87,    65,  -126,  -126,  -126,  -126,  -126,
    -126,  -126,  -126,  -126,    13,    13,  -126,  -126,  -126,    13,
    -126,    65,    13,  -126,  -126,  -126,  -126,    13,  -126,    89,
    -126,    86,  -126,    88,  -126,  -126,    99,    25,    30,  -126,
    -126,    94,    81,    88,   -13,    97,    41,    65,  -126,   103,
     100,  -126,  -126,  -126,  -126,   106,    88,  -126,   108,   109,
    -126
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -126,  -126,  -126,   -18,  -126,  -126,   111,   118,  -126,   115,
     142,  -126,  -126,   121,    44,    82,  -126,  -125,   -71,  -106,
    -110,     1,  -126,  -126,  -126,  -126,  -126,  -126,  -126,    93,
    -126,  -126,   -46,    37,    51,    31,    68,   -22,  -126,    11,
      43,  -126,  -126,  -126,  -126,    -1,  -126
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
       5,   104,    29,    55,   146,     1,   150,    13,   145,    14,
      15,    73,    74,    23,    24,     4,     6,     7,    87,    96,
      13,    99,   100,   101,    56,   145,     8,   105,    80,   126,
      62,    62,   164,   115,    20,   113,    25,    21,   127,   128,
      81,   122,   123,    72,    31,    32,   162,    64,    65,    57,
      55,   145,    71,     4,    82,    83,    84,    85,    86,    66,
      67,    33,    68,    34,    35,    98,    69,    70,   103,    76,
      75,    56,   155,    79,   102,    62,    37,    38,    39,    40,
      78,     4,   159,   109,   114,    33,   151,    34,    35,   111,
     112,   139,    55,    74,   143,   168,    36,   131,   132,    73,
      37,    38,    39,    40,   133,     4,   134,   135,    33,    55,
      34,    35,   136,    56,   137,   142,   141,   154,   153,    36,
     156,    55,   157,    37,    38,    39,    40,   161,     4,   166,
      56,    55,    81,   165,    55,    55,   160,   167,   169,    30,
     170,    59,    56,    58,    55,     4,    82,    83,    84,    85,
      86,    17,    56,    63,   140,    56,    56,   163,   110,    97,
     149,   130,   148,   158,   115,    56,   116,   117,   118,   119,
     120,   121,   122,   123,     0,   147,     0,     0,     0,     0,
     152
};

static const short int yycheck[] =
{
       1,    72,    20,    25,   114,    16,   131,     8,   114,    18,
      19,    26,    27,    14,    15,    40,     0,    29,    64,    65,
      21,    67,    68,    69,    25,   131,    39,    73,    15,     4,
      31,    32,   157,     3,    31,    81,    29,    33,    13,    14,
      27,    11,    12,    31,    27,    27,   156,    27,    27,    30,
      72,   157,    30,    40,    41,    42,    43,    44,    45,    27,
      27,    20,    27,    22,    23,    66,    27,    27,    34,    33,
      28,    72,   143,    28,    28,    76,    35,    36,    37,    38,
      32,    40,   153,    31,    28,    20,   132,    22,    23,    39,
      32,   109,   114,    27,    29,   166,    31,    28,    24,    26,
      35,    36,    37,    38,    28,    40,    28,    28,    20,   131,
      22,    23,    28,   114,    33,    28,    39,    31,    29,    31,
      21,   143,    28,    35,    36,    37,    38,    30,    40,    29,
     131,   153,    27,    30,   156,   157,   154,    31,    30,    21,
      31,    30,   143,    28,   166,    40,    41,    42,    43,    44,
      45,     9,   153,    32,   110,   156,   157,   156,    76,    66,
     129,    93,   125,   152,     3,   166,     5,     6,     7,     8,
       9,    10,    11,    12,    -1,   124,    -1,    -1,    -1,    -1,
     137
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    16,    47,    48,    40,    91,     0,    29,    39,    49,
      50,    51,    53,    91,    18,    19,    54,    56,    57,    58,
      31,    33,    52,    91,    91,    29,    62,    55,    56,    49,
      53,    27,    27,    20,    22,    23,    31,    35,    36,    37,
      38,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    83,    91,    30,    55,    52,
      59,    61,    91,    59,    27,    27,    27,    27,    27,    27,
      27,    30,    31,    26,    27,    28,    33,    60,    32,    28,
      15,    27,    41,    42,    43,    44,    45,    78,    79,    80,
      81,    82,    83,    90,    91,    92,    78,    75,    91,    78,
      78,    78,    28,    34,    64,    78,    78,    84,    86,    31,
      61,    39,    32,    78,    28,     3,     5,     6,     7,     8,
       9,    10,    11,    12,    87,    89,     4,    13,    14,    88,
      82,    28,    24,    28,    28,    28,    28,    33,    85,    49,
      60,    39,    28,    29,    63,    65,    66,    80,    79,    81,
      63,    78,    86,    29,    31,    64,    21,    28,    85,    64,
      49,    30,    66,    67,    63,    30,    29,    31,    64,    30,
      31
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
#line 141 "parser.y"
    {
		AstNode* ast_node = ast_node_new("TranslationUnit", TRANSLATIONUNIT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// NamespaceDecl
		(yyval.astnode) = ast_node;
		
		ast = ast_node;
	;}
    break;

  case 3:
#line 152 "parser.y"
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
#line 164 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 5:
#line 166 "parser.y"
    {
		AstNode* ast_node = ast_node_new("VarDeclList", VARDECL_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[0].astnode));

		(yyval.astnode) = ast_node;
	;}
    break;

  case 6:
#line 173 "parser.y"
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
#line 186 "parser.y"
    {
		AstNode* ast_node = ast_node_new("VarDecl", VARDECL, (yyvsp[-1].type), yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[0].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 8:
#line 195 "parser.y"
    {
		AstNode* ast_node = ast_node_new("IdentifierList", IDENT_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 9:
#line 204 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 10:
#line 206 "parser.y"
    {
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		(yyval.astnode) = (yyvsp[-1].astnode);
	;}
    break;

  case 11:
#line 213 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 12:
#line 217 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 13:
#line 219 "parser.y"
    {
		AstNode* ast_node = ast_node_new("ProcFuncList", PROCFUNC_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 14:
#line 228 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 15:
#line 230 "parser.y"
    {
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		(yyval.astnode) = (yyvsp[-1].astnode);
	;}
    break;

  case 16:
#line 237 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 17:
#line 238 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 18:
#line 244 "parser.y"
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

  case 19:
#line 260 "parser.y"
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

  case 20:
#line 274 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 21:
#line 276 "parser.y"
    {
		AstNode* ast_node = ast_node_new("ParamList", PARAM_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 22:
#line 285 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 23:
#line 287 "parser.y"
    {
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		(yyval.astnode) = (yyvsp[-1].astnode);
	;}
    break;

  case 24:
#line 294 "parser.y"
    {
		AstNode* ast_node = ast_node_new("Parameter", PARAMETER, (yyvsp[0].type), yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// Identifier
		(yyval.astnode) = ast_node;
	;}
    break;

  case 25:
#line 302 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 26:
#line 303 "parser.y"
    { (yyval.astnode) = (yyvsp[-2].astnode); ;}
    break;

  case 27:
#line 307 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 28:
#line 308 "parser.y"
    { (yyval.astnode) = (yyvsp[-1].astnode); ;}
    break;

  case 29:
#line 312 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 30:
#line 314 "parser.y"
    {
		AstNode* ast_node = ast_node_new("StatementList", STATEMENT_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[0].astnode));

		(yyval.astnode) = ast_node;
	;}
    break;

  case 31:
#line 321 "parser.y"
    {
		AstNode* ast_node = (yyvsp[0].astnode);
		if (!ast_node)	{
			ast_node = ast_node_new("StatementList", STATEMENT_LIST, VOID, yylloc.last_line, NULL);
		}
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 32:
#line 332 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 33:
#line 333 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 34:
#line 334 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 35:
#line 338 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 36:
#line 339 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
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
#line 347 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 42:
#line 349 "parser.y"
    {
		AstNode* ast_node = ast_node_new("IfStatement", IF_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-4].astnode));	// Expression
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// StatementMatched
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// StatementUnmatched
		(yyval.astnode) = ast_node;
	;}
    break;

  case 43:
#line 360 "parser.y"
    {
		AstNode* ast_node = ast_node_new("IfStatement", IF_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// Expression
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// Statements
		(yyval.astnode) = ast_node;
	;}
    break;

  case 44:
#line 370 "parser.y"
    {
		AstNode* ast_node = ast_node_new("IfStatement", IF_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-4].astnode));	// Expression
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// StatementMatched true
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// StatementMatched false
		(yyval.astnode) = ast_node;
	;}
    break;

  case 45:
#line 380 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 46:
#line 381 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
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
#line 388 "parser.y"
    {
		AstNode* ast_node = ast_node_new("PrintIntStatement", PRINTINT_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 50:
#line 397 "parser.y"
    {
		AstNode* ast_node = ast_node_new("PrintCharStatement", PRINTCHAR_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 51:
#line 406 "parser.y"
    {
		AstNode* ast_node = ast_node_new("PrintBoolStatement", PRINTBOOL_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 52:
#line 415 "parser.y"
    {
		AstNode* ast_node = ast_node_new("PrintLineStatement", PRINTLINE_STMT, VOID, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 53:
#line 423 "parser.y"
    {
		AstNode* ast_node = ast_node_new("Assignment", ASSIGNMENT_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));
		ast_node_add_child(ast_node, (yyvsp[0].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 54:
#line 433 "parser.y"
    {
		AstNode* ast_node = ast_node_new("WhileStatement", WHILE_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));
		ast_node_add_child(ast_node, (yyvsp[0].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 55:
#line 443 "parser.y"
    {
		AstNode* ast_node = ast_node_new("ForStatement", FOR_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-4].astnode));	// Assignment
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// Expression
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// Statements
		(yyval.astnode) = ast_node;
	;}
    break;

  case 56:
#line 452 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 57:
#line 454 "parser.y"
    {
		AstNode* ast_node = ast_node_new("RelExpression", REL_EXPR, BOOLEAN, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-2].astnode));	// LH Expression
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));	// Relop
		ast_node_add_child(ast_node, (yyvsp[0].astnode));	// RH Expression
		(yyval.astnode) = ast_node;
	;}
    break;

  case 58:
#line 464 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 59:
#line 466 "parser.y"
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

  case 60:
#line 478 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 61:
#line 480 "parser.y"
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

  case 62:
#line 492 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 63:
#line 494 "parser.y"
    {
		AstNode* ast_node = ast_node_new("NotFactor", NOTFACTOR, BOOLEAN, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[0].astnode));
		(yyval.astnode) = ast_node; 
	;}
    break;

  case 64:
#line 502 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 65:
#line 503 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 66:
#line 504 "parser.y"
    { (yyval.astnode) = (yyvsp[0].astnode); ;}
    break;

  case 67:
#line 505 "parser.y"
    { (yyval.astnode) = (yyvsp[-1].astnode); ;}
    break;

  case 68:
#line 510 "parser.y"
    {
		AstNode* ast_node = ast_node_new("Call", CALL, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[-3].astnode));	// Identifier
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));	// Parameters
		(yyval.astnode) = ast_node;
	;}
    break;

  case 69:
#line 519 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 70:
#line 521 "parser.y"
    {
		AstNode* ast_node = ast_node_new("CallParamList", CALLPARAM_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		ast_node_add_child(ast_node, (yyvsp[-1].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 71:
#line 530 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 72:
#line 532 "parser.y"
    {
		ast_node_add_sibling((yyvsp[-1].astnode), (yyvsp[0].astnode));
		(yyval.astnode) = (yyvsp[-1].astnode);
	;}
    break;

  case 73:
#line 540 "parser.y"
    {
		AstNode* ast_node = ast_node_new("CallParameter", CALLPARAM, ((AstNode*)(yyvsp[0].astnode))->type, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, (yyvsp[0].astnode));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 74:
#line 549 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_PLUS, INTEGER, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 75:
#line 554 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_MINUS, INTEGER, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;	
	;}
    break;

  case 76:
#line 559 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_OR, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 77:
#line 567 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_STAR, INTEGER, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 78:
#line 572 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_SLASH, INTEGER, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 79:
#line 577 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_AND, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 80:
#line 585 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_LESSER, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 81:
#line 590 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_LESSEREQUAL, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 82:
#line 595 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_GREATER, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 83:
#line 600 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_GREATEREQUAL, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 84:
#line 605 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_EQUAL, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 85:
#line 610 "parser.y"
    {
		AstNode* ast_node = ast_node_new((yyvsp[0].lexeme), T_NOTEQUAL, BOOLEAN, yylloc.last_line, NULL);
		(yyval.astnode) = ast_node;
	;}
    break;

  case 86:
#line 617 "parser.y"
    { (yyval.astnode) = NULL; ;}
    break;

  case 87:
#line 622 "parser.y"
    {
		AstNode* ast_node = ast_node_new("Identifier", IDENTIFIER, VOID, yylloc.last_line, NULL);
		ast_node->symbol = symbol_new((yyvsp[0].lexeme));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 88:
#line 631 "parser.y"
    {
		AstNode* ast_node = ast_node_new("IntLiteral", INT_LITERAL, INTEGER, yylloc.last_line, NULL);
		value_set_from_int(&ast_node->value, (yyvsp[0].integer));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 89:
#line 637 "parser.y"
    {
		AstNode* ast_node = ast_node_new("BoolLiteral", BOOL_LITERAL, BOOLEAN, yylloc.last_line, NULL);
		value_set_from_bool(&ast_node->value, (yyvsp[0].boolean));
		(yyval.astnode) = ast_node;		
	;}
    break;

  case 90:
#line 643 "parser.y"
    {
		AstNode* ast_node = ast_node_new("CharLiteral", CHAR_LITERAL, CHAR, yylloc.last_line, NULL);
		value_set_from_char(&ast_node->value, (yyvsp[0].character));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 91:
#line 649 "parser.y"
    {
		AstNode* ast_node = ast_node_new("FloatLiteral", FLOAT_LITERAL, FLOAT, yylloc.last_line, NULL);
		value_set_from_float(&ast_node->value, (yyvsp[0].flt));
		(yyval.astnode) = ast_node;
	;}
    break;

  case 92:
#line 655 "parser.y"
    {
		AstNode* ast_node = ast_node_new("DoubleLiteral", DOUBLE_LITERAL, DOUBLE, yylloc.last_line, NULL);
		value_set_from_double(&ast_node->value, (yyvsp[0].dbl));
		(yyval.astnode) = ast_node;
	;}
    break;


    }

/* Line 1037 of yacc.c.  */
#line 2019 "parser.tab.c"

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


#line 662 "parser.y"


static void yyerror(const char* msg)
{
	fprintf(stderr, "Error: line %d: %s\n", yyget_lineno(), msg);
}

