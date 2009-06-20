#include <stdlib.h>
#include <stdio.h>

#include "common/memory.h"
#include "parser.tab.h"
#include "context_visitor.h"

static Type declared_type = VOID;
static Symbol* symtab;
static Symbol* global_symtab;
static AstNode* _inside_procfunc = NULL;

static void _typecheck_print_stmt(AstNode* node, Type type, const char* ptype_str);
static Symbol* _complete_symbol_lookup(Symbol* sym);
static void _fetch_symbol(AstNode* node, Symbol* sym);

#define V_INIT(lhs, rhs)	visitor->visit_##lhs = &context_visit_##rhs

Visitor* context_new()
{
	Visitor* visitor = (Visitor*)malloc(sizeof(Visitor));
	
	V_INIT(TranslationUnit, TranslationUnit);
	V_INIT(NamespaceDecl, NamespaceDecl);
	V_INIT(vardecl_list, vardecl_list);
	V_INIT(vardecl, vardecl);
	V_INIT(function_list, function_list);
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
	if (global_symtab)
		symbol_table_destroy(global_symtab);
}

CTX_VISITOR(TranslationUnit)
{
	node->symbol = symbol_new(NULL);
	global_symtab = node->symbol;
	symtab = global_symtab;
	_inside_procfunc = NULL;
	
	// Namespace
	ast_node_accept(node->children, visitor);
}

CTX_VISITOR(NamespaceDecl)
{
	node->children->symbol->decl_linenum = node->linenum;
	ast_node_accept_children(node->children->sibling, visitor);
}

CTX_VISITOR(function_list)
{
	symtab = global_symtab;
	
	ast_node_accept_children(node->children, visitor);
	
	symtab = global_symtab;
	_inside_procfunc = NULL;
}

CTX_VISITOR(function)
{
	AstNode* ident;
	AstNode* child;
	
	_inside_procfunc = node;
	
	// Identifier
	symtab = global_symtab;
	ident = node->children;
	ident->type = node->type;
	
	// Let other code know we're dealing with a function
	ident->symbol->params = 0;
	ident->symbol->decl_linenum = node->linenum;
	
	ast_node_accept(ident, visitor);
	
	// ParamList, VarDeclList, Statements
	symtab = node->symbol;
	for (child = ident->sibling; (child); child = child->sibling)	{
		if (child->kind == PARAM_LIST)
			child->symbol = ident->symbol;
		ast_node_accept(child, visitor);
	}
}

CTX_VISITOR(vardecl_list)
{
	AstNode* child;
	
	for (child = node->children; (child); child = child->sibling)
		ast_node_accept(child, visitor);
}

CTX_VISITOR(vardecl)
{
	node->children->type = node->type;
	node->children->symbol->decl_linenum = node->linenum;
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
	
	symbol_create_params(node->symbol, node->child_counter);
	
	i = 0;
	for (child = node->children; (child); child = child->sibling)	{
		node->symbol->param_types[i] = child->type;
		i++;
	}
}

CTX_VISITOR(parameter)
{
	node->children->type = node->type;
	node->children->symbol->decl_linenum = node->linenum;
	
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
	
	if (symbol_is_function(lnode->symbol))	{
		
		node->type = ERROR;
		fprintf(stderr, "Error (line %d): Symbol '%s' is a function identifier, you cannot "
			"assign a value to it\n", node->linenum, lnode->symbol->name);
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
	ast_node_accept(stmt, visitor);
	
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
	ast_node_accept(stmt, visitor);
	
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
			id_node->linenum, id_node->symbol->name, type_get_lexeme(id_node->type));
	}
	
	if (expr->type != INTEGER)	{
		node->type = ERROR;
		fprintf(stderr, "Error (line %d): Value of stop condition is not of Integer type\n", expr->linenum);
	}
	
	ast_node_accept(stmt, visitor);
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
	
	node->type = ident->symbol->type;
	
	if (plist != NULL)	{
		plist->symbol = ident->symbol;
		
		ast_node_accept(plist, visitor);
		params = plist->child_counter;
	} else {
		params = 0;
	}
	
	if (params != ident->symbol->params)	{
		node->type = ERROR;
		fprintf(stderr, "Error (line %d): Expecting %d parameters, received %d\n", node->linenum, ident->symbol->params, params);
	}
}

CTX_VISITOR(callparam_list)
{
	int i;
	AstNode* child;
	
	node->child_counter = 0;
	for (child = node->children; (child); child = child->sibling)	
		node->child_counter++;
	
	if (node->symbol->params != node->child_counter)	{
		node->type = ERROR;
		return;
	}
	
	i = 0;
	for (child = node->children; (child); child = child->sibling)	{
		ast_node_accept(child, visitor);
		
		if (child->type != ERROR && 
			child->type != node->symbol->param_types[i])	{
				
			node->type = ERROR;
			child->type = node->symbol->param_types[i];
			
			fprintf(stderr, "Error (line %d): Call '%s' expecting %s on parameter %d (",
				node->linenum, node->symbol->name, type_get_lexeme(node->symbol->param_types[i]),
				i+1);
			
			if (child->children->kind == IDENTIFIER)
				fprintf(stderr, "'%s'", child->children->symbol->name);
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
	Symbol* sym = symbol_lookup(symtab, node->symbol->name);
	Symbol* _sym = sym;
	
	if (sym == NULL)	{
		if (node->symbol->decl_linenum > 0)	{
			node->symbol->type = node->type;
			node->symbol->is_global = (symtab == global_symtab);
						
			node->symbol = symbol_insert(symtab, node->symbol);
		} else if ((sym = symbol_lookup(global_symtab, node->symbol->name)) != NULL)	{
			_fetch_symbol(node, sym);
		} else {
			node->symbol->type = node->type = ERROR;
			fprintf(stderr, "Error (line %d): Undeclared identifier '%s'\n", node->linenum, node->symbol->name);
		}
	} else if (node->symbol->decl_linenum == 0)	{
		_fetch_symbol(node, sym);
	} else {
		node->symbol->type = node->type = ERROR;
		fprintf(stderr, "Error (line %d): Identifier '%s' already defined on line %d\n", 
			node->linenum, _sym->name, _sym->decl_linenum);
	}	
}

static void _fetch_symbol(AstNode* node, Symbol *sym)
{
	symbol_table_destroy(node->symbol);
	node->symbol = sym;
	node->type = sym->type;
}

static void _typecheck_print_stmt(AstNode* node, Type type, const char* ptype_str)
{
	if (node->children->type != type)	{
		node->type = ERROR;
		fprintf(stderr, "Error (line %d): Expression print%s statement must be of %s type\n",
			node->linenum, ptype_str, type_get_lexeme(type));
	}
}