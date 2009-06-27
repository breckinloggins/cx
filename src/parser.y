%{
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "base.h"
#include "parser.h"
#include "ast.h"
#include "identifier_table.h"

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
	char* literal_content;
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
%token T_PRIVATE
%token T_FN
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

%token <literal_content> T_C_BLOCK

%token <type> T_INT;
%token <type> T_BOOL;
%token <type> T_CHAR;
%token <type> T_DOUBLE;
%token <type> T_FLOAT;
%token <type> T_VOID;

%token <lexeme> IDENTIFIER
%token <integer> INT_LITERAL
%token <boolean> BOOL_LITERAL
%token <character> CHAR_LITERAL
%token <dbl> DOUBLE_LITERAL
%token <flt> FLOAT_LITERAL

%type <astnode> TranslationUnit
%type <astnode> NamespaceDecl

%type <type> TypeSpecifier
%type <type> TypeName
%type <type> PrimitiveType

%type <astnode> NamespaceVariableAndFunctionDeclarations
%type <astnode> NamespaceVariableOrFunctionDeclaration
%type <astnode> VarDecl

%type <astnode> Modifier
%type <astnode> FunctionDecl
%type <astnode> ParamList
%type <astnode> SingleParam

%type <astnode> LocalVariableDeclarationsAndStatements
%type <astnode> LocalVariableDeclarationOrStatement

%type <astnode> Statement
%type <astnode> EmptyStatement
%type <astnode> AssignmentStatement
%type <astnode> ExpressionStatement
%type <astnode> IfStatement
%type <astnode> WhileStatement
%type <astnode> ForStatement
%type <astnode> PrintStatement
%type <astnode> PrintCharStatement
%type <astnode> PrintIntStatement
%type <astnode> PrintBoolStatement
%type <astnode> PrintLineStatement
%type <astnode> CBlockStatement
%type <astnode> ReturnStatement
%type <astnode> Block

%type <astnode> Expression
%type <astnode> ReadCharExpression
%type <astnode> SimpleExpression
%type <astnode> NotFactor
%type <astnode> Factor
%type <astnode> Term

%type <astnode> Call
%type <astnode> CallParameterList

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
	T_NAMESPACE Identifier T_LBRACK NamespaceVariableAndFunctionDeclarations T_RBRACK
	{
		AstNode* ast_node = ast_node_new("NamespaceDecl", NAMESPACE_DECL, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $2);	// Namespace Identifier
		ast_node_add_child(ast_node, $4);	// Variable and Function Declarations
	
		$$ = ast_node;
	}
	| T_NAMESPACE Identifier T_LBRACK T_RBRACK
	{
		AstNode* ast_node = ast_node_new("NamespaceDecl", NAMESPACE_DECL, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $2);	// Namespace Identifier
			
		$$ = ast_node;
	}
	;
	
TypeSpecifier:
	TypeName	{ $$ = $1; }
	;

TypeName:
	PrimitiveType	{ $$ = $1; }
	;
	
PrimitiveType:
	T_INT	{ $$ = $1; }
	| T_BOOL	{ $$ = $1; }
	| T_CHAR	{ $$ = $1; }
	| T_DOUBLE	{ $$ = $1; }
	| T_FLOAT	{ $$ = $1; }
	| T_VOID	{ $$ = $1; }

NamespaceVariableAndFunctionDeclarations:
	NamespaceVariableOrFunctionDeclaration
	{
		AstNode* ast_node = ast_node_new("NamespaceDeclList", NAMESPACEDECL_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $1);
		
		$$ = ast_node;
	}
	| NamespaceVariableAndFunctionDeclarations NamespaceVariableOrFunctionDeclaration
	{
		AstNode* ast_node = $1;
		if (!ast_node)	{
			ast_node = ast_node_new("NamespaceDeclList", NAMESPACEDECL_LIST, VOID, yylloc.last_line, NULL);
		}
		
		ast_node_add_child(ast_node, $2);
		$$ = ast_node;
	}
	;

NamespaceVariableOrFunctionDeclaration:
	VarDecl T_SEMICOLON { $$ = $1; }
	| FunctionDecl { $$ = $1; }
	;

VarDecl:
	TypeSpecifier Identifier
	{
		AstNode* ast_node = ast_node_new("VarDecl", VARDECL, $1, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $2);
		$$ = ast_node;
	}
	;

Modifier:
	T_PUBLIC { $$ = NULL; fprintf(stderr, "FIXME: Public modifier not yet supported\n"); exit(1); }	
	| T_PRIVATE { $$ = NULL; fprintf(stderr, "FIXME: Private modifier not yet supported\n"); exit(1); }
	;

FunctionDecl:
	VarDecl T_LPAR ParamList T_RPAR Block
	{
		AstNode* vardecl_node = $1;
		
		AstNode* ast_node = ast_node_new("FunctionDecl", FUNCTION, vardecl_node->type, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, vardecl_node->children);	// Identifier
		ast_node_add_child(ast_node, $3);						// ParamList
		ast_node_add_child(ast_node, $5);						// Block
		
		// We don't need the vardecl_node anymore as we've collapsed its information
		// into this node
		vardecl_node->children = NULL;
		vardecl_node->sibling = NULL;
		ast_node_destroy(vardecl_node);

		$$ = ast_node;
	}
	| Modifier VarDecl T_LPAR ParamList T_RPAR Block
	{
		AstNode* vardecl_node = $2;
		
		AstNode* ast_node = ast_node_new("FunctionDecl", FUNCTION, vardecl_node->type, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, vardecl_node->children);	// Identifier
		ast_node_add_child(ast_node, $4);						// ParamList
		ast_node_add_child(ast_node, $6);						// Block
		
		// We don't need the vardecl_node anymore as we've collapsed its information
		// into this node
		vardecl_node->children = NULL;
		vardecl_node->sibling = NULL;
		ast_node_destroy(vardecl_node);

		$$ = ast_node;
	}
	| Modifier VarDecl T_LPAR T_RPAR Block
	{
			AstNode* vardecl_node = $2;
			
			AstNode* ast_node = ast_node_new("FunctionDecl", FUNCTION, vardecl_node->type, yylloc.last_line, NULL);
			ast_node_add_child(ast_node, vardecl_node->children);	// Identifier
			ast_node_add_child(ast_node, $5);						// Block

			// We don't need the vardecl_node anymore as we've collapsed its information
			// into this node
			vardecl_node->children = NULL;
			vardecl_node->sibling = NULL;
			ast_node_destroy(vardecl_node);

			$$ = ast_node;
	}
	| VarDecl T_LPAR T_RPAR Block
	{
			AstNode* vardecl_node = $1;
			
			AstNode* ast_node = ast_node_new("FunctionDecl", FUNCTION, vardecl_node->type, yylloc.last_line, NULL);
			ast_node_add_child(ast_node, vardecl_node->children);	// Identifier
			ast_node_add_child(ast_node, $4);						// Block

			// We don't need the vardecl_node anymore as we've collapsed its information
			// into this node
			vardecl_node->children = NULL;
			vardecl_node->sibling = NULL;
			ast_node_destroy(vardecl_node);

			$$ = ast_node;
	}
	;
	
ParamList:
	SingleParam
	{
		AstNode* ast_node = ast_node_new("ParamList", PARAM_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $1);
		$$ = ast_node;
	}
	| ParamList T_COMMA SingleParam
	{
		AstNode* ast_node = $1;
		if (!ast_node)	{
			ast_node = ast_node_new("ParamList", PARAM_LIST, VOID, yylloc.last_line,  NULL);
		}
		
		ast_node_add_child(ast_node, $3);
		$$ = ast_node;
	}
	;

SingleParam:
	TypeSpecifier Identifier
	{
		AstNode* ast_node = ast_node_new("Parameter", PARAMETER, $1, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $2);	// Identifier
		$$ = ast_node;
	}
	;

Block:
	T_LBRACK LocalVariableDeclarationsAndStatements T_RBRACK { $$ = $2; }
	| T_LBRACK T_RBRACK {$$ = NULL; }
	;
	
LocalVariableDeclarationsAndStatements:
	LocalVariableDeclarationOrStatement 
	{ 
		AstNode* ast_node = ast_node = ast_node_new("StatementList", STATEMENT_LIST, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $1);
		$$ = ast_node; 
	}
	| LocalVariableDeclarationsAndStatements LocalVariableDeclarationOrStatement 
	{
		AstNode* ast_node = $1;
		if (!ast_node)	{
			ast_node = ast_node_new("StatementList", STATEMENT_LIST, VOID, yylloc.last_line, NULL);
		}
		
		ast_node_add_child(ast_node, $2);
		$$ = ast_node;
	}
	;

LocalVariableDeclarationOrStatement:
	VarDecl T_SEMICOLON { $$ = $1; }
	| Statement { $$ = $1; }
	;
	
Statement:
	EmptyStatement { $$ = NULL; }
	| AssignmentStatement { $$ = $1; }
	| ExpressionStatement { $$ = $1; }
	| IfStatement { $$ = $1; }
	| WhileStatement { $$ = $1; }
	| ForStatement { $$ = $1; }
	| PrintStatement { $$ = $1; }
	| ReturnStatement { $$ = $1; }
	| CBlockStatement { $$ = $1; }
	| Block { $$ = $1; }
	;

EmptyStatement:
	T_SEMICOLON	{ $$ = NULL; }
	;

IfStatement:
	T_IF T_LPAR Expression T_RPAR Statement
	{
		AstNode* ast_node = ast_node_new("IfStatement", IF_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $3);	// Expression
		ast_node_add_child(ast_node, $5);	// Statements
		$$ = ast_node;
	}
	| T_IF T_LPAR Expression T_RPAR Statement T_ELSE Statement
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

CBlockStatement:
	T_C_BLOCK
	{
		AstNode* ast_node = ast_node_new("CBlock", CBLOCK_STMT, VOID, yyloc.last_line, NULL);
		ast_node->value.literal_content = $1;
		$$ = ast_node;
	}

ReturnStatement:
	T_RETURN T_SEMICOLON
	{
		AstNode* ast_node = ast_node_new("ReturnStatement", RETURN_STMT, VOID, yylloc.last_line, NULL);
		$$ = ast_node;
	}
	| T_RETURN Expression T_SEMICOLON
	{
		AstNode* ast_node = ast_node_new("ReturnStatement", RETURN_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $2);
		$$ = ast_node;
	}
	;

AssignmentStatement:
	Assignment T_SEMICOLON { $$ = $1; }
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
	T_WHILE T_LPAR Expression T_RPAR Statement
	{
		AstNode* ast_node = ast_node_new("WhileStatement", WHILE_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $3);
		ast_node_add_child(ast_node, $5);
		$$ = ast_node;
	}
	;
	
ForStatement:
	T_FOR T_LPAR Assignment T_TO Expression T_RPAR Statement
	{
		AstNode* ast_node = ast_node_new("ForStatement", FOR_STMT, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $3);	// Assignment
		ast_node_add_child(ast_node, $5);	// Expression
		ast_node_add_child(ast_node, $7);	// Statements
		$$ = ast_node;
	}
	
ExpressionStatement:
	Expression T_SEMICOLON	{ $$ = $1; }
	;
	
Expression:
	SimpleExpression { $$ = $1; }
	| ReadCharExpression { $$ = $1; }
	| SimpleExpression RelOp SimpleExpression
	{
		AstNode* ast_node = ast_node_new("RelExpression", REL_EXPR, BOOLEAN, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $1);	// LH Expression
		ast_node_add_child(ast_node, $2);	// Relop
		ast_node_add_child(ast_node, $3);	// RH Expression
		$$ = ast_node;
	}
	;
	
ReadCharExpression:
	T_READ_CHAR T_LPAR T_RPAR
	{
		AstNode* ast_node = ast_node_new("ReadCharExpression", READCHAR_EXPR, CHAR, yyloc.last_line, NULL);
		$$ = ast_node;
	}
	
	
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
	Identifier T_LPAR CallParameterList T_RPAR
	{
		AstNode* ast_node = ast_node_new("Call", CALL, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $1);	// Identifier
		ast_node_add_child(ast_node, $3);	// Parameters
		$$ = ast_node;
	}
	| Identifier T_LPAR T_RPAR
	{
		AstNode* ast_node = ast_node_new("Call", CALL, VOID, yylloc.last_line, NULL);
		ast_node_add_child(ast_node, $1);	// Identifier
		$$ = ast_node;
	}
	;
	
CallParameterList:
	Expression
	{
		AstNode* ast_node = ast_node_new("CallParamList", CALLPARAM_LIST, VOID, yylloc.last_line, NULL);
		
		AstNode* param_node = ast_node_new("CallParameter", CALLPARAM, ((AstNode*)$1)->type, yylloc.last_line, NULL);
		ast_node_add_child(param_node, $1);
		ast_node_add_child(ast_node, param_node);
		$$ = ast_node;
	}
	| CallParameterList T_COMMA Expression
	{
		AstNode* ast_node = $1;
		if (!ast_node)	{
			ast_node = ast_node_new("CallParamList", CALLPARAM_LIST, VOID, yylloc.last_line, NULL);
		}

		AstNode* param_node = ast_node_new("CallParameter", CALLPARAM, ((AstNode*)$3)->type, yylloc.last_line, NULL);
		ast_node_add_child(param_node, $3);
		ast_node_add_child(ast_node, param_node);
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
		ast_node->identifier = identifier_new($1);
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
