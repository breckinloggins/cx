#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common/memory.h"
#include "parser.tab.h"
#include "c_codegen_visitor.h"

#define V_INIT(lhs, rhs)	visitor->visit_##lhs = &c_codegen_visit_##rhs			
	
static char *pf_name;
static int tmp_var = 0;
static FILE* out;

static void _tab(AstNode* node);
static char* _get_type_string(Type type);
static char* _create_temporary();
static void _print_op_symbol(AstNode* node);

Visitor* c_codegen_new(FILE* output)
{
	out = output;
	Visitor* visitor = (Visitor*)malloc(sizeof(Visitor));
	
	V_INIT(program, program);
	V_INIT(programdecl, programdecl);
	V_INIT(vardecl_list, vardecl_list);
	V_INIT(vardecl, vardecl);
	V_INIT(identifier_list, identifier_list);
	V_INIT(procfunc_list, procfunc_list);
	V_INIT(procedure, procfunc);
	V_INIT(function, procfunc);
	V_INIT(param_list, param_list);
	V_INIT(parameter, parameter);
	V_INIT(statement_list, statement_list);
	V_INIT(printint_stmt, printint_stmt);
	V_INIT(printchar_stmt, printchar_stmt);
	V_INIT(printbool_stmt, printbool_stmt);
	V_INIT(printline_stmt, printline_stmt);
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
	V_INIT(identifier, identifier);
	V_INIT(literal, literal);
	V_INIT(add_op, binary_op);
	V_INIT(mul_op, binary_op);
	V_INIT(rel_op, binary_op);
	V_INIT(not_op, not_op);
	
	visitor->visit_callparam = NULL;
	
	return visitor;
} 

C_VISITOR(program)
{
	AstNode* child;
	
	fprintf(out, "/* Generated with cxc */\n");
	for (child = node->children; 
	child != NULL && child->kind != STATEMENT_LIST; 
	child = child->sibling)	{
		ast_node_accept(child, visitor);
		fprintf(out, "\n");
	}
	
	if (child)	{
		fprintf(out, "int main(int argc, char** argv)\n{\n");
		ast_node_accept(child, visitor);
		fprintf(out, "\n"TAB"return 0;\n}\n\n");
	}
	
	
}

C_VISITOR(programdecl)
{
	fprintf(out, "/* program ");
	ast_node_accept(node->children, visitor);
	fprintf(out, "; */\n\n");
	fprintf(out, "#include <stdio.h>\n\n");
	fprintf(out, "#ifndef FALSE\n#define FALSE\t0\n#endif\n\n");
	fprintf(out, "#ifndef TRUE\n#define TRUE\t1\n#endif\n");
}

C_VISITOR(procfunc_list)
{
	ast_node_accept_children(node->children, visitor);
}

C_VISITOR(procfunc)
{
	const char* type;
	AstNode* child;
	
	type = _get_type_string(node->type);
	pf_name = _create_temporary();				// TODO: This isn't gonna work for Cx, we want
												//		non-random function names!
	
	fprintf(out, "%s ", type);
	
	child = node->children;						// Identifier
	ast_node_accept(child, visitor);
	
	fprintf(out, " (");
	
	child = child->sibling;
	if (child->kind == PARAM_LIST)	{
		ast_node_accept(child, visitor);
		child = child->sibling;
	}
	
	fprintf(out, ")\n{\n");
	
	if (node->kind == FUNCTION)
		fprintf(out, TAB"%s %s;\n", type, pf_name);
	
	if (child->kind == VARDECL_LIST)	{
		ast_node_accept(child, visitor);
		child = child->sibling;
	}
	
	fprintf(out, "\n");
	
	ast_node_accept(child, visitor);
	
	if (node->kind == FUNCTION)
		fprintf(out, "\n"TAB"return %s;\n", pf_name);
	fprintf(out, "}\n\n");
	
	free(pf_name);	
}

C_VISITOR(vardecl_list)
{
	ast_node_accept_children(node->children, visitor);
	fprintf(out, "\n");
}

C_VISITOR(vardecl)
{
	const char* type = _get_type_string(node->type);
	
	fprintf(out, TAB"%s ", type);
	ast_node_accept(node->children, visitor);
	fprintf(out, ";\n");
}

C_VISITOR(identifier_list)
{
	AstNode* child;
	
	for (child = node->children; (child); child = child->sibling)	{
		ast_node_accept(child, visitor);
		if (child->sibling != NULL)
			fprintf(out, ", ");
	}
}

C_VISITOR(param_list)
{
	AstNode* child;
	
	for(child = node->children; (child); child = child->sibling)	{
		fprintf(out, "%s ", _get_type_string(child->type));
		ast_node_accept(child, visitor);
		if (child->sibling)
			fprintf(out, ", ");
	}
}

C_VISITOR(parameter)
{
	ast_node_accept(node->children, visitor);
}

C_VISITOR(statement_list)
{
	AstNode* child;
	
	for(child = node->children; (child); child = child->sibling)	{
		_tab(child);
		ast_node_accept(child, visitor);
		fprintf(out, "\n");
	}
}

C_VISITOR(printint_stmt)
{
	fprintf(out, "printf(\"%%d\", ");
	ast_node_accept(node->children, visitor);
	fprintf(out, ");");
}

C_VISITOR(printchar_stmt)
{
	fprintf(out, "printf(\"%%c\", ");
	ast_node_accept(node->children, visitor);
	fprintf(out, ");");
}

C_VISITOR(printbool_stmt)
{
	fprintf(out, "printf(\"%%s\", ");
	ast_node_accept(node->children, visitor);
	fprintf(out, ");");
}

C_VISITOR(printline_stmt)
{
	fprintf(out, "printf(\"\\n\");");
}

C_VISITOR(assignment_stmt)
{
	ast_node_accept(node->children, visitor);
	fprintf(out, " = ");
	ast_node_accept(node->children->sibling, visitor);
	fprintf(out, ";");
}

C_VISITOR(if_stmt)
{
	AstNode* child;
	const char* var;
	
	fprintf(out, "if (");
	child = node->children;					// Expression
	ast_node_accept(child, visitor);
	fprintf(out, ") {\n");
	
	child = child->sibling;					// If Statements
	ast_node_accept(child, visitor);
	
	fprintf(out, "\n");
	_tab(node);
	fprintf(out, "}");
	
	child = child->sibling;					// Else Statements
	if (child)	{
		fprintf(out, " else {\n");
		ast_node_accept(child, visitor);
		fprintf(out, "\n");
		_tab(node);
		fprintf(out, "}");
	}
	
	fprintf(out, "\n");
}

C_VISITOR(while_stmt)
{
	AstNode* child;
	const char* var;
	
	fprintf(out, "while (");
	child = node->children;					// Expression
	ast_node_accept(child, visitor);
	fprintf(out, ") {\n");
	
	child = child->sibling;					// Statements
	ast_node_accept(child, visitor);
	
	_tab(node);
	fprintf(out, "}\n");
}

C_VISITOR(for_stmt)
{
	AstNode* child;
	const char* var;
	
	fprintf(out, "for (");
	child = node->children;					// Assignment
	ast_node_accept(child, visitor);
	
	var = child->children->symbol->name;
	fprintf(out, " %s < ", var);			// TODO: WTF?
	
	child = child->sibling;					// Stop condition
	ast_node_accept(child, visitor);
	
	fprintf(out, "; %s++) {\n", var);		// TODO: More hard-coded crap
	
	child = child->sibling;					// Statements
	ast_node_accept_children(child, visitor);
	
	fprintf(out, "\n");
	_tab(node);
	fprintf(out, "}\n");
}

C_VISITOR(binary_expr)
{
	ast_node_accept_children(node->children, visitor);
}

C_VISITOR(notfactor)
{
	ast_node_accept_children(node->children, visitor);
}

C_VISITOR(call)
{
	fprintf(out, "%s ();\n", node->children->symbol->name);
	//ast_node_accept(node->children, visitor);
}

C_VISITOR(callparam_list)
{
	ast_node_accept_children(node->children, visitor);
}

C_VISITOR(identifier)
{
	fprintf(out, "%s", node->symbol->name);
}

C_VISITOR(literal)
{
	if (node->type == BOOLEAN)	{
		fprintf(out, "%s", node->value.boolean? "TRUE":"FALSE");
	} else {
		value_print(out, &node->value, node->type);
	}
}

C_VISITOR(binary_op)
{
	_print_op_symbol(node);
}

C_VISITOR(not_op)
{
	fprintf(out, " !");
}

static void _tab(AstNode* node)
{
	AstNode* parent;
	for (parent = node->parent; parent->parent != NULL; parent = parent->parent)
		fprintf(out, TAB);
}

static char* _get_type_string(Type type)
{
	switch (type)	{
		case INTEGER:
		case BOOLEAN:
			return "int";
		case CHAR:
			return "char";
		default:
			return "void";
	}
}

static char* _create_temporary()
{
	char* temp;
	
	if (asprintf(&temp, "tmp%.5d", tmp_var) < 0)
		return NULL;
	
	tmp_var++;
	return temp;
}

static void _print_op_symbol(AstNode* node)
{
	switch(node->kind)	{
		case T_OR:
			fprintf(out, " || ");
			break;
		case T_AND:
			fprintf(out, " && ");
			break;
		case T_EQUAL:
			fprintf(out, " == ");
			break;
		case T_NOTEQUAL:
			fprintf(out, " != ");
			break;
		case T_LESSER:
			fprintf(out, " < ");
			break;
		case T_GREATER:
			fprintf(out, " > ");
			break;
		case T_LESSEREQUAL:
			fprintf(out, " <= ");
			break;
		case T_GREATEREQUAL:
			fprintf(out, " >= ");
			break;
		case T_PLUS:
		case T_MINUS:
		case T_STAR:
		case T_SLASH:
			fprintf(out, " %s ", node->name);
	}
}