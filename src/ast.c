/* 
 *	General Functions for the manipulation of Cx's Abstract Syntax Tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/memory.h"
#include "ast.h"
#include "parser.h"

AstNode* ast_node_new(const char* name, Kind kind, PrimitiveType type, int linenum)
{
	//printf("Created a node of type %s\n", name);
	
	AstNode* node = (AstNode*)malloc(sizeof(AstNode));
	
	if (name)
		node->name = strdup(name);
	else
		node->name = NULL;
		
	node->kind = kind;
	node->type = type;
	node->linenum = linenum;
	node->identifier = NULL;
	node->parent = NULL;
	node->children = NULL;
	node->sibling = NULL;
	
	return node;
}

void ast_node_destroy(AstNode* self)
{
	if (self)	{
		ast_node_destroy(self->children);
		ast_node_destroy(self->sibling);
		free(self->name);
		
		if (self->type == CBLOCK_STMT)
			free(self->value.literal_content);
		
		if (self->identifier && self->identifier->decl_scope == NULL)	{
			// TODO: This is probably an error.  ALL identifiers should be claimed
			// by a scope!
			//fprintf(stderr, "Internal Compiler Error: Orphaned identifier '%s' at line %d\n", self->identifier->name, self->linenum);
			identifier_destroy(self->identifier);
		}
		
		free(self);
	}
}

Value ast_node_get_value(AstNode* self)
{
	if (self->kind == IDENTIFIER)	{
		return self->identifier->value;
	}
	
	return self->value;
}

int ast_node_get_value_as_int(AstNode* self)
{
	return ast_node_get_value(self).integer;
}

bool ast_node_check_errors(AstNode* self)
{
	AstNode* child;
	
	if (self == NULL || self->type == ERROR)
		return TRUE;
	
	for (child = self->children; (child); child = child->sibling)	{
		if (ast_node_check_errors(child))
			return TRUE;
	}
	
	return FALSE;
}

void ast_node_add_child(AstNode* self, AstNode* child)
{
	AstNode* temp;
	
	if (!child)
		return;
	
	if (self->children == NULL)	{
		child->parent = self;
		self->children = child;
	} else {
		ast_node_add_sibling(self->children, child);
	}
	
	for (temp = child; (temp); temp = temp->sibling)	{
		temp->parent = self;
	}
}

void ast_node_add_sibling(AstNode* self, AstNode* sibling)
{
	AstNode* temp;
	
	if (!sibling)
		return;
		
	if (self->sibling == NULL)	{
		self->sibling = sibling;
	} else {
		for (temp = self->sibling; (temp->sibling); temp = temp->sibling)
			;	// Just to get to the end of the list
		temp->sibling = sibling;
	}
}

void ast_node_accept(AstNode* self, Visitor* visitor)
{
	VisitFunc visit;
	
	if (!self)
		return;
	
	switch(self->kind)	{
		case TARGET:
			visit = visitor->visit_Target;
			break;
		case TRANSLATIONUNIT:
			visit = visitor->visit_TranslationUnit;
			break;
		case NAMESPACE_DECL:
			visit = visitor->visit_NamespaceDecl;
			break;
		case NAMESPACEDECL_LIST:
			visit = visitor->visit_NamespaceDecl_list;
			break;
		case VARDECL:
			visit = visitor->visit_vardecl;
			break;
		case FUNCTION:
			visit = visitor->visit_function;
			break;
		case PARAM_LIST:
			visit = visitor->visit_param_list;
			break;
		case PARAMETER:
			visit = visitor->visit_parameter;
			break;
		case STATEMENT_LIST:
			visit = visitor->visit_statement_list;
			break;
		case PRINTINT_STMT:
			visit = visitor->visit_printint_stmt;
			break;
		case PRINTCHAR_STMT:
			visit = visitor->visit_printchar_stmt;
			break;
		case PRINTBOOL_STMT:
			visit = visitor->visit_printbool_stmt;
			break;
		case PRINTLINE_STMT:
			visit = visitor->visit_printline_stmt;
			break;
		case CBLOCK_STMT:
			visit = visitor->visit_cblock_stmt;
			break;
		case RETURN_STMT:
			visit = visitor->visit_return_stmt;
			break;
		case ASSIGNMENT_STMT:
			visit = visitor->visit_assignment_stmt;
			break;
		case IF_STMT:
			visit = visitor->visit_if_stmt;
			break;
		case WHILE_STMT:
			visit = visitor->visit_while_stmt;
			break;
		case DOWHILE_STMT:
			visit = visitor->visit_dowhile_stmt;
			break;
		case FOR_STMT:
			visit = visitor->visit_for_stmt;
			break;
		case READCHAR_EXPR:
			visit = visitor->visit_readchar_expr;
			break;
		case REL_EXPR:
			visit = visitor->visit_rel_expr;
			break;
		case ADD_EXPR:
			visit = visitor->visit_add_expr;
			break;
		case MUL_EXPR:
			visit = visitor->visit_mul_expr;
			break;
		case NOTFACTOR:
			visit = visitor->visit_notfactor;
			break;
		case CALL:
			visit = visitor->visit_call;
			break;
		case CALLPARAM_LIST:
			visit = visitor->visit_callparam_list;
			break;
		case CALLPARAM:
			visit = visitor->visit_callparam;
			break;
		case IDENTIFIER:
			visit = visitor->visit_identifier;
			break;
		case INT_LITERAL:
		case BOOL_LITERAL:
		case CHAR_LITERAL:
		case DOUBLE_LITERAL:
		case FLOAT_LITERAL:
			visit = visitor->visit_literal;
			break;
		case T_PLUS:
		case T_MINUS:
		case T_OR:
			visit = visitor->visit_add_op;
			break;
		case T_STAR:
		case T_SLASH:
		case T_AND:
			visit = visitor->visit_mul_op;
			break;
		case T_EQUAL:
		case T_NOTEQUAL:
		case T_LESSER:
		case T_GREATER:
		case T_LESSEREQUAL:
		case T_GREATEREQUAL:
			visit = visitor->visit_rel_op;
			break;
		case T_NOT:
			visit = visitor->visit_not_op;
			break;
		default:
			fprintf(stderr, "Internal Compiler Error: Unrecognized kind (%d) in ast_node_accept\n", self->kind);
			exit(1);
	}
	
	if (visit != NULL)
		visit(visitor, self);
}

void ast_node_accept_children(AstNode* self, Visitor* visitor)
{
	AstNode* temp;
	for (temp = self; (temp); temp = temp->sibling)
		ast_node_accept(temp, visitor);
}

char* kind_get_name(int kind)
{
	switch(kind)	{
		case TARGET:					return "Target";
		case TRANSLATIONUNIT: 			return "TranslationUnit";
		case USING_DECL:				return "UsingDecl";
		case USINGDECL_LIST:			return "UsingDeclList";
		case NAMESPACE_DECL: 			return "NamespaceDecl";
		case NAMESPACEDECL_LIST: 		return "NamespaceDeclList";
		case VARDECL: 					return "VarDecl";
		case FUNCTION: 					return "Function";
		case PARAM_LIST: 				return "ParamList";
		case PARAMETER: 				return "Parameter";
		case STATEMENT_LIST: 			return "StatementList";
		case EXPRESSIONSTMT_LIST: 		return "ExpressionStatementList";
		case PRINTINT_STMT: 			return "PrintIntStatement";
		case PRINTCHAR_STMT: 			return "PrintCharStatement";
		case PRINTBOOL_STMT: 			return "PrintBoolStatement";
		case PRINTLINE_STMT:			return "PrintLineStatement";
		case CBLOCK_STMT:				return "CBlockStatement";
		case ASSIGNMENT_STMT:			return "AssignmentStatement";
		case RETURN_STMT:				return "ReturnStatement";
		case IF_STMT:					return "IfStatement";
		case WHILE_STMT:				return "WhileStatement";
		case DOWHILE_STMT:				return "DoWhileStatement";
		case FOR_STMT:					return "ForStatement";
		case REL_EXPR:					return "RelationExpression";
		case ADD_EXPR:					return "AddExpression";
		case MUL_EXPR:					return "MulExpression";
		case READCHAR_EXPR:				return "ReadCharExpression";
		case NOTFACTOR:					return "NotFactor";
		case CALL:						return "Call";
		case CALLPARAM_LIST:			return "CallParamList";
		case CALLPARAM:					return "CallParam";
		case IDENTIFIER:				return "Identifier";
		case INT_LITERAL:				return "IntLiteral";
		case BOOL_LITERAL:				return "BoolLiteral";
		case CHAR_LITERAL:				return "CharLiteral";
		case DOUBLE_LITERAL:			return "DoubleLiteral";
		case FLOAT_LITERAL:				return "FloatLiteral";
		case T_PLUS:					return "+";
		case T_MINUS:					return "-";
		case T_OR:						return "||";
		case T_STAR:					return "*";
		case T_SLASH:					return "/";
		case T_AND:						return "&&";
		case T_LESSER:					return "<";
		case T_LESSEREQUAL:				return "<=";
		case T_GREATER:					return ">";
		case T_GREATEREQUAL:			return ">=";
		case T_EQUAL:					return "==";
		case T_NOTEQUAL:				return "!=";
		
		default:	
			fprintf(stderr, "Internal Compiler Error: Unrecognized kind (%d) in kind_get_name\n", kind);
			exit(1);
	}
}
