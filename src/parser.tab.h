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
/* Line 1274 of yacc.c.  */
#line 136 "parser.tab.h"
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




