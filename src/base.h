#ifndef BASE_H
#define BASE_H

/*
 *	Base tyoes and methods for Cx compiler.  Based on the toypasc source (code.google.com/p/toypasc)
 */

#include <stdio.h>		// For FILE*

#define VOID(var)		((void *)&var)
#define IS_LITERAL(k)	( k == BOOL_LITERAL   || \
					   	  k == DOUBLE_LITERAL || \
					      k == FLOAT_LITERAL  || \
						  k == CHAR_LITERAL   || \
						  k == INT_LITERAL)

typedef enum	{
	FALSE = 0,
	TRUE
} bool;

typedef enum PrimTypeEnum	{
	ERROR = -1,
	VOID,
	INTEGER,
	DOUBLE,
	FLOAT,
	BOOLEAN,
	CHAR
} PrimitiveType;

typedef enum KindEnum	{
	NONE_KIND = -1,
	TARGET,
	TRANSLATIONUNIT,
	USING_DECL,
	USINGDECL_LIST,
	NAMESPACE_DECL,
	NAMESPACEDECL_LIST,
	VARDECL,
	FUNCTION,
	PARAM_LIST,
	PARAMETER,
	STATEMENT_LIST,
	EXPRESSIONSTMT_LIST,
	PRINTINT_STMT,
	PRINTCHAR_STMT,
	PRINTBOOL_STMT,
	PRINTLINE_STMT,
	CBLOCK_STMT,
	ASSIGNMENT_STMT,
	RETURN_STMT,
	IF_STMT,
	WHILE_STMT,
	DOWHILE_STMT,
	FOR_STMT,
	REL_EXPR,
	ADD_EXPR,
	MUL_EXPR,
	READCHAR_EXPR,
	NOTFACTOR,
	CALL,
	CALLPARAM_LIST,
	CALLPARAM,
	// IDENTIFIER is defined as a token
	// INT_LITERAL, BOOL_LITERAL, CHAR_LITERAL, ... are defined as tokens
} Kind;

typedef union	{
	int integer;
	double dbl;
	float flt;
	bool boolean;
	char character;
	char* literal_content;
} Value;

char* type_get_lexeme(PrimitiveType type);
PrimitiveType type_get_from_lexeme(const char* lexeme);

void value_get(Value* value, PrimitiveType type, void* val);
void value_set(Value* value, PrimitiveType type, void* val);

void value_set_from_int(Value* value, int val);
void value_set_from_bool(Value* value, bool val);
void value_set_from_char(Value* value, char val);
void value_set_from_double(Value* value, double val);
void value_set_from_float(Value* value, float val);

void value_print(FILE* file, Value* value, PrimitiveType type);

#endif	// BASE_H