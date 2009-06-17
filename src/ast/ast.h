#ifndef AST_H
#define AST_H

/*
 *	Routines for construction and manipulation of the Cx Abstract Syntax Tree
 */

#include "../base.h"
#include "../symbol_table.h"

#define VISITOR_PFN(fn)		void (*fn) (struct Visitor_tag*, struct AstNode_tag *)

typedef struct AstNode_tag	{
	char* name;
	int kind;
	Type type;
	Value value;
	Symbol* symbol;
	int linenum;
	int child_counter;
	
	struct AstNode_tag* parent;
	struct AstNode_tag* children;
	struct AstNode_tag* sibling;
} AstNode;

typedef struct Visitor_tag	{
	VISITOR_PFN(visit_TranslationUnit);
	VISITOR_PFN(visit_NamespaceDecl);
	VISITOR_PFN(visit_vardecl_list);
	VISITOR_PFN(visit_vardecl);
	VISITOR_PFN(visit_identifier_list);
	VISITOR_PFN(visit_identifier);
	VISITOR_PFN(visit_procfunc_list);
	VISITOR_PFN(visit_procedure);
	VISITOR_PFN(visit_function);
	VISITOR_PFN(visit_param_list);
	VISITOR_PFN(visit_parameter);
	VISITOR_PFN(visit_statement_list);
	VISITOR_PFN(visit_printint_stmt);
	VISITOR_PFN(visit_printchar_stmt);
	VISITOR_PFN(visit_printbool_stmt);
	VISITOR_PFN(visit_printline_stmt);
	VISITOR_PFN(visit_assignment_stmt);
	VISITOR_PFN(visit_if_stmt);
	VISITOR_PFN(visit_while_stmt);
	VISITOR_PFN(visit_for_stmt);
	VISITOR_PFN(visit_rel_expr);
	VISITOR_PFN(visit_add_expr);
	VISITOR_PFN(visit_mul_expr);
	VISITOR_PFN(visit_notfactor);
	VISITOR_PFN(visit_call);
	VISITOR_PFN(visit_callparam_list);
	VISITOR_PFN(visit_callparam);
	VISITOR_PFN(visit_literal);
	VISITOR_PFN(visit_add_op);
	VISITOR_PFN(visit_mul_op);
	VISITOR_PFN(visit_rel_op);
	VISITOR_PFN(visit_not_op);	
} Visitor;

typedef VISITOR_PFN(VisitFunc);

AstNode* ast_node_new(const char* name, Kind kind, Type type, int linenum, Symbol* symbol);
void ast_node_destroy(AstNode* node);

Value ast_node_get_value(AstNode* node);
int ast_node_get_value_as_int(AstNode* node);
int ast_node_get_child_counter(AstNode* node);
bool ast_node_check_errors(AstNode* node);
void ast_node_add_child(AstNode* node, AstNode* child);
void ast_node_add_sibling(AstNode* node, AstNode* sibling);

void ast_node_accept(AstNode* self, Visitor* visitor);
void ast_node_accept_children(AstNode* self, Visitor* visitor);

#endif