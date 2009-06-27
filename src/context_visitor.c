#include <stdlib.h>
#include <stdio.h>

#include "common/memory.h"
#include "parser.h"
#include "context_visitor.h"

static Type declared_type = VOID;
static AstNode* _inside_procfunc = NULL;

static Scope* _current_scope = NULL;

static void _typecheck_print_stmt(AstNode* node, Type type, const char* ptype_str);
static Identifier* _complete_identifier_lookup(Identifier* id);
static AstNode* _get_nearest_scope_node(AstNode* node);

#define V_INIT(lhs, rhs)	visitor->visit_##lhs = &context_visit_##rhs

Visitor* context_new()
{
	Visitor* visitor = (Visitor*)malloc(sizeof(Visitor));
	
	V_INIT(TranslationUnit, TranslationUnit);
	V_INIT(NamespaceDecl, NamespaceDecl);
	V_INIT(NamespaceDecl_list, NamespaceDecl_list);
	V_INIT(vardecl, vardecl);
	V_INIT(function, function);
	V_INIT(param_list, param_list);
	V_INIT(parameter, parameter);
	V_INIT(statement_list, statement_list);
	V_INIT(printint_stmt, printint_stmt);
	V_INIT(printchar_stmt, printchar_stmt);
	V_INIT(printbool_stmt, printbool_stmt);
	V_INIT(readchar_expr, readchar_expr);
	V_INIT(cblock_stmt, cblock_stmt);
	V_INIT(return_stmt, return_stmt);
	V_INIT(assignment_stmt, assignment_stmt);
	V_INIT(if_stmt, if_stmt);
	V_INIT(while_stmt, while_stmt);
	V_INIT(for_stmt, for_stmt);
	V_INIT(rel_expr, binary_expr);
	V_INIT(add_expr, binary_expr);
	V_INIT(mul_expr, binary_expr);
	V_INIT(notfactor, notfactor);
	V_INIT(call, call);
	V_INIT(callparam_list, callparam_list);
	V_INIT(callparam, callparam);
	V_INIT(identifier, identifier);
	
	visitor->visit_printline_stmt = NULL;
	visitor->visit_literal = NULL;
	visitor->visit_add_op = NULL;
	visitor->visit_mul_op = NULL;
	visitor->visit_rel_op = NULL;
	visitor->visit_not_op = NULL;
		
	return visitor;
}

void context_cleanup()
{
	scope_destroy_all();
}

CTX_VISITOR(TranslationUnit)
{
	_current_scope = scope_new(NULL, node);
	_inside_procfunc = NULL;
	
	// Namespace
	ast_node_accept(node->children, visitor);
}

CTX_VISITOR(NamespaceDecl)
{
	_current_scope = scope_new(_current_scope, node);
	
	node->children->identifier->decl_linenum = node->linenum;
	ast_node_accept_children(node->children->sibling, visitor);
	
	_current_scope = _current_scope->parent;
}

CTX_VISITOR(NamespaceDecl_list)
{
	ast_node_accept_children(node->children, visitor);
}

CTX_VISITOR(function)
{
	AstNode* ident;
	AstNode* child;
	
	_inside_procfunc = node;
	
	// Identifier
	ident = node->children;
	ident->type = node->type;
	
	// Let other code know we're dealing with a function
	ident->identifier->params = 0;
	ident->identifier->decl_linenum = node->linenum;
	
	ast_node_accept(ident, visitor);
	
	_current_scope = scope_new(_current_scope, node);
	int has_return = 0;
	
	// ParamList, VarDeclList, Statements
	for (child = ident->sibling; (child); child = child->sibling)	{
		if (child->kind == PARAM_LIST)
			child->identifier = ident->identifier;
		ast_node_accept(child, visitor);
	
		if (child->kind == STATEMENT_LIST)	{
			// It is important that all the "returns" in the function have a return
			// type compatible with the function itself
			AstNode* stmt;
			for (stmt = child->children; (stmt); stmt = stmt->sibling)	{
				if (stmt->kind == RETURN_STMT)	{
					has_return = 1;
					break;
				}			
			}
		}
	}
	
	if (!has_return && node->type != ERROR && node->type != VOID)	{
		fprintf(stderr, "Error (line %d): Function '%s' does not return a value\n", node->linenum, ident->identifier->name);
		node->type = ERROR;
	}
	
	_inside_procfunc = NULL;
	_current_scope = _current_scope->parent;
}

CTX_VISITOR(vardecl)
{
	if (node->type == VOID)	{
		fprintf(stderr, "Error (line %d): Type 'void' is not valid here\n", node->linenum);
		node->type = ERROR;
	}
	
	node->children->type = node->type;
	node->children->identifier->decl_linenum = node->linenum;
	ast_node_accept(node->children, visitor);
	
}

CTX_VISITOR(param_list)
{
	int i;
	AstNode* child;
	
	node->child_counter = 0;
	for (child = node->children; (child); child = child->sibling)	{
		ast_node_accept(child, visitor);
		node->child_counter++;
	}
	
	identifier_create_params(node->identifier, node->child_counter);
	
	i = 0;
	for (child = node->children; (child); child = child->sibling)	{
		node->identifier->param_types[i] = child->type;
		i++;
	}
}

CTX_VISITOR(parameter)
{
	node->children->type = node->type;
	node->children->identifier->decl_linenum = node->linenum;
	
	ast_node_accept(node->children, visitor);
}

CTX_VISITOR(statement_list)
{
	ast_node_accept_children(node->children, visitor);
}

CTX_VISITOR(printint_stmt)
{
	ast_node_accept(node->children, visitor);
	_typecheck_print_stmt(node, INTEGER, "Int");
}

CTX_VISITOR(printchar_stmt)
{
	ast_node_accept(node->children, visitor);
	_typecheck_print_stmt(node, CHAR, "Char");	
}

CTX_VISITOR(printbool_stmt)
{
	ast_node_accept(node->children, visitor);
	_typecheck_print_stmt(node, BOOLEAN, "Bool");	
}

CTX_VISITOR(readchar_expr)
{
	//_typecheck_print_stmt(node, CHAR, "Char");
}

CTX_VISITOR(cblock_stmt)
{
	if (!node->value.literal_content)	{
		fprintf(stderr, "Fatal Compiler Error: no content in embedded C block\n");
		exit(1);
	}
}

CTX_VISITOR(return_stmt)
{
	Type return_type = VOID;
	if (node->children)	{
		ast_node_accept(node->children, visitor);
		return_type = node->children->type;
	}
	
	if (!_inside_procfunc)	{
		node->type = ERROR;
		fprintf(stderr, "Error (line %d): Keyword \"return\" is only valid inside a function or method\n", node->linenum);
	}
	else if (_inside_procfunc->type != return_type)	{
		node->type = ERROR;
		fprintf(stderr, "Error (line %d): Incompatible return type\n", node->linenum);
	}
	else	{
		node->type = return_type;
	}
}

CTX_VISITOR(assignment_stmt)
{
	AstNode* lnode = node->children;
	AstNode* rnode = lnode->sibling;
	
	ast_node_accept(lnode, visitor);
	ast_node_accept(rnode, visitor);
	
	if (lnode->identifier->params >= 0)	{
		
		node->type = ERROR;
		fprintf(stderr, "Error (line %d): Identifier '%s' is a function identifier, you cannot "
			"assign a value to it\n", node->linenum, lnode->identifier->name);
	} else if (lnode->type != ERROR && rnode->type != ERROR && lnode->type != rnode->type)	{
		node->type = ERROR;
		fprintf(stderr, "Error (line %d): Incompatible types on assignment\n", node->linenum);
	}
}

CTX_VISITOR(if_stmt)
{
	AstNode* expr = node->children;
	AstNode* stmt = expr->sibling;
	
	ast_node_accept(expr, visitor);
	
	_current_scope = scope_new(_current_scope, node);
	ast_node_accept(stmt, visitor);
	_current_scope = _current_scope->parent;
	
	if (stmt && stmt->sibling)	{
		// This is the else part
		_current_scope = scope_new(_current_scope, node);
		ast_node_accept(stmt->sibling, visitor);
		_current_scope = _current_scope->parent;
	}
	
	if (expr->type != BOOLEAN)	{
		node->type = ERROR;
		fprintf(stderr, "Error (line %d): Condition for if statement must be of Boolean type\n", node->linenum);
	}
}

CTX_VISITOR(while_stmt)
{
	AstNode* expr = node->children;
	AstNode* stmt = expr->sibling;
	
	ast_node_accept(expr, visitor);
	
	_current_scope = scope_new(_current_scope, node);
	ast_node_accept(stmt, visitor);
	_current_scope = _current_scope->parent;
	
	if (expr->type != BOOLEAN)	{
		node->type = ERROR;
		fprintf(stderr, "Error (line %d): Expressin in While statement must be of Boolean type\n", node->linenum);
	}
}

CTX_VISITOR(for_stmt)
{
	AstNode* asgn = node->children;
	AstNode* expr = asgn->sibling;
	AstNode* stmt = expr->sibling;
	AstNode* id_node = asgn->children;
	
	ast_node_accept(asgn, visitor);
	ast_node_accept(expr, visitor);
	
	if (id_node->type != INTEGER)	{
		node->type = ERROR;
		fprintf(stderr, "Error (line %d): Identifier '%s' is of %s type; it must be Integer\n", 
			id_node->linenum, id_node->identifier->name, type_get_lexeme(id_node->type));
	}
	
	if (expr->type != INTEGER)	{
		node->type = ERROR;
		fprintf(stderr, "Error (line %d): Value of stop condition is not of Integer type\n", expr->linenum);
	}

	_current_scope = scope_new(_current_scope, node);
	ast_node_accept(stmt, visitor);
	_current_scope = _current_scope->parent;
}

CTX_VISITOR(binary_expr)
{
	AstNode* lnode = node->children;
	AstNode* op = lnode->sibling;
	AstNode* rnode = op->sibling;
	
	ast_node_accept(lnode, visitor);
	ast_node_accept(rnode, visitor);
	
	if (lnode->type != ERROR && rnode->type != ERROR && lnode->type != rnode->type)	{
		node->type = ERROR;
		fprintf(stderr, "Error (line %d): Operation '%s' over incompatible types\n", op->linenum, op->name);
	}
}

CTX_VISITOR(notfactor)
{
	ast_node_accept(node->children, visitor);
	
	if (node->children->type != BOOLEAN)	{
		node->type = ERROR;
		fprintf(stderr, "Error (line %d): Operation 'not' over non-boolean operand\n", node->linenum);
	}
}

CTX_VISITOR(call)
{
	int params;
	AstNode* ident = node->children;
	AstNode* plist = ident->sibling;
	
	ast_node_accept(ident, visitor);
	
	if (ident->type == ERROR)
		return;
	
	node->type = ident->identifier->type;
	
	if (plist != NULL)	{
		plist->identifier = ident->identifier;
		
		ast_node_accept(plist, visitor);
		params = plist->child_counter;
	} else {
		params = 0;
	}
	
	if (params != ident->identifier->params)	{
		node->type = ERROR;
		fprintf(stderr, "Error (line %d): Expecting %d parameters, received %d\n", node->linenum, ident->identifier->params, params);
	}
}

CTX_VISITOR(callparam_list)
{
	int i;
	AstNode* child;
	
	node->child_counter = 0;
	for (child = node->children; (child); child = child->sibling)	
		node->child_counter++;
	
	if (node->identifier->params != node->child_counter)	{
		node->type = ERROR;
		return;
	}
	
	i = 0;
	for (child = node->children; (child); child = child->sibling)	{
		ast_node_accept(child, visitor);
		
		if (child->type != ERROR && 
			child->type != node->identifier->param_types[i])	{
				
			node->type = ERROR;
			child->type = node->identifier->param_types[i];
			
			fprintf(stderr, "Error (line %d): Call '%s' expecting %s on parameter %d (",
				node->linenum, node->identifier->name, type_get_lexeme(node->identifier->param_types[i]),
				i+1);
			
			if (child->children->kind == IDENTIFIER)
				fprintf(stderr, "'%s'", child->children->identifier->name);
			else
				value_print(stderr, &child->value, child->type);
			
			fprintf(stderr, "), received %s\n", type_get_lexeme(child->type));
		}
		i++;
	}
}

CTX_VISITOR(callparam)
{
	ast_node_accept(node->children, visitor);
	node->type = node->children->type;
}

CTX_VISITOR(identifier)
{
	Identifier* id = scope_lookup(_current_scope, node->identifier->name);

	if (id == NULL)	{
		if (node->identifier->decl_linenum == 0)	{
			node->identifier->type = node->type = ERROR;
			fprintf(stderr, "Error (line %d): Undeclared identifier '%s'\n", node->linenum, node->identifier->name);
		} else {
			node->identifier->type = node->type;
			node->identifier = scope_insert(_current_scope, node->identifier);
		}
	} else if (node->identifier->decl_linenum == 0)	{
		identifier_destroy(node->identifier);
		node->identifier = id;
		node->type = id->type;
	} else {
		node->identifier->type = node->type = ERROR;
		fprintf(stderr, "Error (line %d): Identifier '%s' already defined on line %d\n", 
			node->linenum, id->name, id->decl_linenum);
	}	
}

static void _typecheck_print_stmt(AstNode* node, Type type, const char* ptype_str)
{
	if (node->children->type != type)	{
		node->type = ERROR;
		fprintf(stderr, "Error (line %d): Expression print%s statement must be of %s type\n",
			node->linenum, ptype_str, type_get_lexeme(type));
	}
}