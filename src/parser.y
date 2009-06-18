%{
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
	
%}

%defines
%locations
%pure-parser
%error-verbose

%union {
	char* lexeme;
	int integer;
	int boolean;
	double dbl;
	float flt;
	char character;
	int type;
	struct AstNode_tag* astnode;
}

/* Tokens */
%left <lexeme> T_OR
%left <lexeme> T_AND
%left <lexeme> T_EQUAL T_NOTEQUAL
%left <lexeme> T_LESSER T_GREATER T_LESSEREQUAL T_GREATEREQUAL
%left <lexeme> T_PLUS T_MINUS
%left <lexeme> T_STAR T_SLASH
%left <lexeme> T_NOT

%token T_NAMESPACE
%token T_VAR

%token T_PUBLIC
%token T_RETURN

%token T_IF
%token T_ELSE
%token T_WHILE
%token T_FOR
%token T_TO
%token T_DO

%token T_ASSIGNMENT

%token T_LPAR
%token T_RPAR
%token T_LBRACK
%token T_RBRACK
%token T_SEMICOLON
%token T_COLON
%token T_COMMA
%token T_DOT

%token T_PRINT_INT
%token T_PRINT_CHAR
%token T_PRINT_BOOL
%token T_PRINT_LINE
%token T_READ_CHAR

%token T_C_BLOCK

%token <type> TYPE_IDENTIFIER
%token <lexeme> IDENTIFIER
%token <integer> INT_LITERAL
%token <boolean> BOOL_LITERAL
%token <character> CHAR_LITERAL
%token <dbl> DOUBLE_LITERAL
%token <flt> FLOAT_LITERAL

%type <astnode> TranslationUnit
%type <astnode> NamespaceDecl
%type <astnode> VarDeclList
%type <astnode> VarDecl
%type <astnode> IdentifierList
%type <astnode> MultiIdentifier
%type <astnode> SingleIdentifier

%type <astnode> FunctionList
%type <astnode> MultiFunctionDecl
%type <astnode> FunctionDecl
%type <astnode> ParamList
%type <astnode> SingleParam
%type <astnode> MultiParam

%type <astnode> Statements
%type <astnode> StatementList
%type <astnode> Statement
%type <astnode> StatementMatched
%type <astnode> StatementUnmatched
%type <astnode> IfStatement
%type <astnode> IfStatementMatched
%type <astnode> WhileStatement
%type <astnode> ForStatement
%type <astnode> PrintStatement
%type <astnode> PrintCharStatement
%type <astnode> PrintIntStatement
%type <astnode> PrintBoolStatement
%type <astnode> PrintLineStatement
%type <astnode> ReadCharStatement
%type <astnode> ReturnStatement

%type <astnode> Expression
%type <astnode> SimpleExpression
%type <astnode> NotFactor
%type <astnode> Factor
%type <astnode> Term

%type <astnode> Call
%type <astnode> CallParamList
%type <astnode> CallParameter
%type <astnode> MultiCallParameter

%type <astnode> Assignment
%type <astnode> Identifier
%type <astnode> Literal

%type <astnode> AddOp
%type <astnode> MulOp
%type <astnode> RelOp
%type <astnode> NotOp

%start TranslationUnit

%%

TranslationUnit:
	NamespaceDecl
	{
		AstNode* ast_node = ast_node_new("TranslationUnit", TRANSLATIONUNIT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $1);	// NamespaceDecl
		$$ = ast_node;
		
		ast = ast_node;
	}
	;

NamespaceDecl:
	T_NAMESPACE Identifier T_LBRACK VarDeclList FunctionList T_RBRACK
	{
		AstNode* ast_node = ast_node_new("NamespaceDecl", NAMESPACE_DECL, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $2);	// Namespace Identifier
		ast_node_add_child(ast_node, $4);	// VarDeclList
		ast_node_add_child(ast_node, $5);	// ProcFuncList
	
		$$ = ast_node;
	}
	;

VarDeclList:
	/* empty */ { $$ = NULL; }
	| VarDecl
	{
		AstNode* ast_node = ast_node_new("VarDeclList", VARDECL_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $1);

		$$ = ast_node;
	}
	| VarDecl T_SEMICOLON VarDeclList
	{
		AstNode* ast_node = $3;
		if (!ast_node)	{
			ast_node = ast_node_new("VarDeclList", VARDECL_LIST, VOID, yylloc.last_line, NULL);
		}
		ast_node_add_child(ast_node, $1);
		$$ = ast_node;
	}
	;


VarDecl:
	TYPE_IDENTIFIER IdentifierList
	{
		AstNode* ast_node = ast_node_new("VarDecl", VARDECL, $1, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $2);
		$$ = ast_node;
	}
	;


IdentifierList:
	SingleIdentifier MultiIdentifier
	{
		AstNode* ast_node = ast_node_new("IdentifierList", IDENT_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_sibling($1, $2);
		ast_node_add_child(ast_node, $1);
		$$ = ast_node;
	}
	;

MultiIdentifier:
	/* empty */	 { $$ = NULL; }
	| T_COMMA SingleIdentifier MultiIdentifier
	{
		ast_node_add_sibling($2, $3);
		$$ = $2;
	}
	;
	
SingleIdentifier:
	Identifier { $$ = $1; }
	;

FunctionList:
	/* empty */ { $$ = NULL; }
	| FunctionDecl MultiFunctionDecl
	{
		AstNode* ast_node = ast_node_new("FunctionList", FUNCTION_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_sibling($1, $2);
		ast_node_add_child(ast_node, $1);
		$$ = ast_node;
	}
	;
	
MultiFunctionDecl:
	/* empty */ { $$ = NULL; }
	| FunctionDecl MultiFunctionDecl
	{
		ast_node_add_sibling($1, $2);
		$$ = $1;
	}
	;
	
FunctionDecl:
	/* HACK: T_PUBLIC is here just to avoid some shift/reduce conflicts for the time being */
	T_PUBLIC TYPE_IDENTIFIER SingleIdentifier T_LPAR ParamList T_RPAR
	T_LBRACK VarDeclList StatementList T_RBRACK
	{
		Symbol* symtab;
		AstNode* ast_node = ast_node_new("FunctionDecl", FUNCTION, $2, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $3);	// Identifier
		ast_node_add_child(ast_node, $5);	// ParamList
		ast_node_add_child(ast_node, $8);	// VarDeclList
		ast_node_add_child(ast_node, $9);	// Statements

		ast_node->symbol = symbol_new(NULL);
		$$ = ast_node;
	}
	;
	
ParamList:
	/* empty */ { $$ = NULL; }
	| SingleParam MultiParam
	{
		AstNode* ast_node = ast_node_new("ParamList", PARAM_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_sibling($1, $2);
		ast_node_add_child(ast_node, $1);
		$$ = ast_node;
	}
	;
	
MultiParam:
	/* empty */ { $$ = NULL; }
	| T_COMMA SingleParam MultiParam
	{
		ast_node_add_sibling($2, $3);
		$$ = $2;
	}

SingleParam:
	Identifier T_COLON TYPE_IDENTIFIER
	{
		AstNode* ast_node = ast_node_new("Parameter", PARAMETER, $3, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $1);	// Identifier
		$$ = ast_node;
	}
	;
	
Statements:
	Statement { $$ = $1; }
	| T_LBRACK StatementList T_RBRACK { $$ = $2; }
	;

StatementList:
	/* empty */ { $$ = NULL; }
	| Statement
	{
		AstNode* ast_node = ast_node_new("StatementList", STATEMENT_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $1);

		$$ = ast_node;
	}
	| Statement T_SEMICOLON StatementList
	{
		AstNode* ast_node = $3;
		if (!ast_node)	{
			ast_node = ast_node_new("StatementList", STATEMENT_LIST, VOID, yylloc.last_line, NULL);
		}
		ast_node_add_child(ast_node, $1);
		$$ = ast_node;
	}
	;

Statement:
	StatementMatched { $$ = $1; }
	| StatementUnmatched { $$ = $1; }
	| T_SEMICOLON	{ $$ = NULL; }
	;

StatementMatched:
	Assignment { $$ = $1; }
	| IfStatementMatched { $$ = $1; }
	| WhileStatement { $$ = $1; }
	| ForStatement { $$ = $1; }
	| Call { $$ = $1; }
	| PrintStatement { $$ = $1; }
	| ReturnStatement { $$ = $1; }
	| ReadCharStatement { $$ = $1; }
	;

StatementUnmatched:
	IfStatement { $$ = $1; }
	| T_IF T_LPAR Expression T_RPAR StatementMatched T_ELSE StatementUnmatched
	{
		AstNode* ast_node = ast_node_new("IfStatement", IF_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $3);	// Expression
		ast_node_add_child(ast_node, $5);	// StatementMatched
		ast_node_add_child(ast_node, $7);	// StatementUnmatched
		$$ = ast_node;
	}
	;

IfStatement:
	T_IF T_LPAR Expression T_RPAR Statements
	{
		AstNode* ast_node = ast_node_new("IfStatement", IF_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $3);	// Expression
		ast_node_add_child(ast_node, $5);	// Statements
		$$ = ast_node;
	}
	;
	
IfStatementMatched:
	T_IF T_LPAR Expression T_RPAR StatementMatched T_ELSE StatementMatched
	{
		AstNode* ast_node = ast_node_new("IfStatement", IF_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $3);	// Expression
		ast_node_add_child(ast_node, $5);	// StatementMatched true
		ast_node_add_child(ast_node, $7);	// StatementMatched false
		$$ = ast_node;
	}
	;
	
PrintStatement:
	PrintIntStatement { $$ = $1; }
	| PrintCharStatement { $$ = $1; }
	| PrintBoolStatement { $$ = $1; }
	| PrintLineStatement { $$ = $1; }
	;

PrintIntStatement:
	T_PRINT_INT T_LPAR Expression T_RPAR
	{
		AstNode* ast_node = ast_node_new("PrintIntStatement", PRINTINT_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $3);
		$$ = ast_node;
	}
	;
	
PrintCharStatement:
	T_PRINT_CHAR T_LPAR Expression T_RPAR
	{
		AstNode* ast_node = ast_node_new("PrintCharStatement", PRINTCHAR_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $3);
		$$ = ast_node;
	}
	;
	
PrintBoolStatement:
	T_PRINT_BOOL T_LPAR Expression T_RPAR
	{
		AstNode* ast_node = ast_node_new("PrintBoolStatement", PRINTBOOL_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $3);
		$$ = ast_node;
	}
	;
	
PrintLineStatement:
	T_PRINT_LINE T_LPAR T_RPAR
	{
		AstNode* ast_node = ast_node_new("PrintLineStatement", PRINTLINE_STMT, VOID, yylloc.last_line, NULL);
		$$ = ast_node;
	}
	;

ReadCharStatement:
	T_READ_CHAR T_LPAR T_RPAR
	{
		AstNode* ast_node = ast_node_new("ReadCharStatement", READCHAR_STMT, CHAR, yyloc.last_line, NULL);
		$$ = ast_node;
	}

ReturnStatement:
	T_RETURN
	{
		AstNode* ast_node = ast_node_new("ReturnStatement", RETURN_STMT, VOID, yylloc.last_line, NULL);
		$$ = ast_node;
	}
	| T_RETURN Expression
	{
		AstNode* ast_node = ast_node_new("ReturnStatement", RETURN_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $2);
		$$ = ast_node;
	}
	;
	
Assignment:
	Identifier T_ASSIGNMENT Expression
	{
		AstNode* ast_node = ast_node_new("Assignment", ASSIGNMENT_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $1);
		ast_node_add_child(ast_node, $3);
		$$ = ast_node;
	}
	;

WhileStatement:
	T_WHILE T_LPAR Expression T_RPAR Statements
	{
		AstNode* ast_node = ast_node_new("WhileStatement", WHILE_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $3);
		ast_node_add_child(ast_node, $5);
		$$ = ast_node;
	}
	;
	
ForStatement:
	T_FOR T_LPAR Assignment T_TO Expression T_RPAR Statements
	{
		AstNode* ast_node = ast_node_new("ForStatement", FOR_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $3);	// Assignment
		ast_node_add_child(ast_node, $5);	// Expression
		ast_node_add_child(ast_node, $7);	// Statements
		$$ = ast_node;
	}
	
Expression:
	SimpleExpression { $$ = $1; }
	| SimpleExpression RelOp SimpleExpression
	{
		AstNode* ast_node = ast_node_new("RelExpression", REL_EXPR, BOOLEAN, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $1);	// LH Expression
		ast_node_add_child(ast_node, $2);	// Relop
		ast_node_add_child(ast_node, $3);	// RH Expression
		$$ = ast_node;
	}
	;
	
SimpleExpression:
	Term { $$ = $1; }
	| SimpleExpression AddOp Term
	{
		AstNode* ast_node;
		Type type = ((AstNode*)$2)->type;
		ast_node = ast_node_new("AddExpression", ADD_EXPR, type, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $1);	// LH Expression
		ast_node_add_child(ast_node, $2);	// AddOp (+/-)
		ast_node_add_child(ast_node, $3);	// Term
		$$ = ast_node;
	}
	;
	
Term:
	NotFactor { $$ = $1; }
	| Term MulOp NotFactor
	{
		AstNode* ast_node;
		Type type = ((AstNode*)$2)->type;
		ast_node = ast_node_new("MulExpression", MUL_EXPR, type, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $1);	// Term
		ast_node_add_child(ast_node, $2);	// MulOp (*//)
		ast_node_add_child(ast_node, $3);	// NotFactor
		$$ = ast_node;
	}
	;
	
NotFactor:
	Factor { $$ = $1; }
	| NotOp Factor
	{
		AstNode* ast_node = ast_node_new("NotFactor", NOTFACTOR, BOOLEAN, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $2);
		$$ = ast_node; 
	}
	;
	
Factor:
	Identifier { $$ = $1; }
	| Literal { $$ = $1; }
	| Call { $$ = $1; }
	| T_LPAR Expression T_RPAR { $$ = $2; }
	;
	
Call:
	Identifier T_LPAR CallParamList T_RPAR
	{
		AstNode* ast_node = ast_node_new("Call", CALL, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $1);	// Identifier
		ast_node_add_child(ast_node, $3);	// Parameters
		$$ = ast_node;
	}
	;
	
CallParamList:
	/* empty */	 { $$ = NULL; }
	| CallParameter MultiCallParameter
	{
		AstNode* ast_node = ast_node_new("CallParamList", CALLPARAM_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_sibling($1, $2);
		ast_node_add_child(ast_node, $1);
		$$ = ast_node;
	}
	;
	
MultiCallParameter:
	/* empty */ { $$ = NULL; }
	| T_COMMA CallParameter MultiCallParameter
	{
		ast_node_add_sibling($2, $3);
		$$ = $2;
	}
	;
	
CallParameter:
	Expression
	{
		AstNode* ast_node = ast_node_new("CallParameter", CALLPARAM, ((AstNode*)$1)->type, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $1);
		$$ = ast_node;
	}
	;

AddOp:
	T_PLUS
	{
		AstNode* ast_node = ast_node_new($1, T_PLUS, INTEGER, yylloc.last_line, NULL);
		$$ = ast_node;
	}
	| T_MINUS
	{
		AstNode* ast_node = ast_node_new($1, T_MINUS, INTEGER, yylloc.last_line, NULL);
		$$ = ast_node;	
	}
	| T_OR
	{
		AstNode* ast_node = ast_node_new($1, T_OR, BOOLEAN, yylloc.last_line, NULL);
		$$ = ast_node;
	}
	;
	
MulOp:
	T_STAR
	{
		AstNode* ast_node = ast_node_new($1, T_STAR, INTEGER, yylloc.last_line, NULL);
		$$ = ast_node;
	}
	| T_SLASH
	{
		AstNode* ast_node = ast_node_new($1, T_SLASH, INTEGER, yylloc.last_line, NULL);
		$$ = ast_node;
	}
	| T_AND
	{
		AstNode* ast_node = ast_node_new($1, T_AND, BOOLEAN, yylloc.last_line, NULL);
		$$ = ast_node;
	}
	;
	
RelOp:
	T_LESSER
	{
		AstNode* ast_node = ast_node_new($1, T_LESSER, BOOLEAN, yylloc.last_line, NULL);
		$$ = ast_node;
	}
	| T_LESSEREQUAL
	{
		AstNode* ast_node = ast_node_new($1, T_LESSEREQUAL, BOOLEAN, yylloc.last_line, NULL);
		$$ = ast_node;
	}
	| T_GREATER
	{
		AstNode* ast_node = ast_node_new($1, T_GREATER, BOOLEAN, yylloc.last_line, NULL);
		$$ = ast_node;
	}
	| T_GREATEREQUAL
	{
		AstNode* ast_node = ast_node_new($1, T_GREATEREQUAL, BOOLEAN, yylloc.last_line, NULL);
		$$ = ast_node;
	}
	| T_EQUAL
	{
		AstNode* ast_node = ast_node_new($1, T_EQUAL, BOOLEAN, yylloc.last_line, NULL);
		$$ = ast_node;
	}
	| T_NOTEQUAL
	{
		AstNode* ast_node = ast_node_new($1, T_NOTEQUAL, BOOLEAN, yylloc.last_line, NULL);
		$$ = ast_node;
	}
	;
	
NotOp:
	T_NOT { $$ = NULL; }
	;

Identifier:
	IDENTIFIER
	{
		AstNode* ast_node = ast_node_new("Identifier", IDENTIFIER, VOID, yylloc.last_line, NULL);
		ast_node->symbol = symbol_new($1);
		$$ = ast_node;
	}
	;
	
Literal:
	INT_LITERAL
	{
		AstNode* ast_node = ast_node_new("IntLiteral", INT_LITERAL, INTEGER, yylloc.last_line, NULL);
		value_set_from_int(&ast_node->value, $1);
		$$ = ast_node;
	}
	| BOOL_LITERAL
	{
		AstNode* ast_node = ast_node_new("BoolLiteral", BOOL_LITERAL, BOOLEAN, yylloc.last_line, NULL);
		value_set_from_bool(&ast_node->value, $1);
		$$ = ast_node;		
	}
	| CHAR_LITERAL
	{
		AstNode* ast_node = ast_node_new("CharLiteral", CHAR_LITERAL, CHAR, yylloc.last_line, NULL);
		value_set_from_char(&ast_node->value, $1);
		$$ = ast_node;
	}
	| FLOAT_LITERAL
	{
		AstNode* ast_node = ast_node_new("FloatLiteral", FLOAT_LITERAL, FLOAT, yylloc.last_line, NULL);
		value_set_from_float(&ast_node->value, $1);
		$$ = ast_node;
	}
	| DOUBLE_LITERAL
	{
		AstNode* ast_node = ast_node_new("DoubleLiteral", DOUBLE_LITERAL, DOUBLE, yylloc.last_line, NULL);
		value_set_from_double(&ast_node->value, $1);
		$$ = ast_node;
	}
	;
	
%%

static void yyerror(const char* msg)
{
	fprintf(stderr, "Error: line %d: %s\n", yyget_lineno(), msg);
}
