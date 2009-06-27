#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common/memory.h"
#include "parser.h"
#include "c_codegen_visitor.h"

#define V_INIT(lhs, rhs)	visitor->visit_##lhs = &c_codegen_visit_##rhs			

static int tab_level = 0;
static FILE* out;

static void _tab();
static char* _get_type_string(Type type);
static void _print_op_symbol(AstNode* node);
static char* _identifier_get_cname(Identifier* identifier);
static void _cname_cleanup();

Visitor* c_codegen_new(FILE* output)
{
	out = output;
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
	V_INIT(printline_stmt, printline_stmt);
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
	V_INIT(literal, literal);
	V_INIT(add_op, binary_op);
	V_INIT(mul_op, binary_op);
	V_INIT(rel_op, binary_op);
	V_INIT(not_op, not_op);
	
	return visitor;
} 

void c_codegen_cleanup()
{
	_cname_cleanup();
}

C_VISITOR(TranslationUnit)
{	
	fprintf(out, "/* Generated with cxc */\n");
	
	ast_node_accept_children(node->children, visitor);
	
}

C_VISITOR(NamespaceDecl)
{
	AstNode* namespace_identifier = node->children;
	fprintf(out, "/* namespace ");
	ast_node_accept(namespace_identifier, visitor);
	fprintf(out, " */\n\n");
	fprintf(out, "#include <stdio.h>\n\n");
	fprintf(out, "#ifndef FALSE\n#define FALSE\t0\n#endif\n\n");
	fprintf(out, "#ifndef TRUE\n#define TRUE\t1\n#endif\n");
		
	AstNode* child;
	for (child = namespace_identifier->sibling; (child); child = child->sibling)	{
		ast_node_accept(child, visitor);
		fprintf(out, "\n");
	}
}

C_VISITOR(NamespaceDecl_list)
{
	ast_node_accept_children(node->children, visitor);
	fprintf(out, "\n");
}

C_VISITOR(function)
{
	const char* type;
	AstNode* child;
	
	type = _get_type_string(node->type);
	
	_tab();
	fprintf(out, "%s ", type);
	
	child = node->children;						// Identifier
	ast_node_accept(child, visitor);
	
	fprintf(out, " (");
	
	child = child->sibling;
	if (child && child->kind == PARAM_LIST)	{
		ast_node_accept(child, visitor);
		child = child->sibling;
	}
	
	fprintf(out, ")\n");
	_tab();
	fprintf(out, "{\n");	
	++tab_level;
	ast_node_accept(child, visitor);
	--tab_level;
	
	fprintf(out, "\n");
	_tab();
	fprintf(out, "}\n\n");
}

C_VISITOR(vardecl)
{
	const char* type = _get_type_string(node->type);
	
	fprintf(out, "%s ", type);
	ast_node_accept(node->children, visitor);
	fprintf(out, ";\n");
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
		_tab();
		ast_node_accept(child, visitor);
		fprintf(out, ";\n");
	}
}

C_VISITOR(printint_stmt)
{
	fprintf(out, "printf(\"%%d\", ");
	ast_node_accept(node->children, visitor);
	fprintf(out, ")");
}

C_VISITOR(printchar_stmt)
{
	fprintf(out, "printf(\"%%c\", ");
	ast_node_accept(node->children, visitor);
	fprintf(out, ")");
}

C_VISITOR(printbool_stmt)
{
	fprintf(out, "printf(\"%%s\", ");
	ast_node_accept(node->children, visitor);
	fprintf(out, ")");
}

C_VISITOR(printline_stmt)
{
	fprintf(out, "printf(\"\\n\")");
}

C_VISITOR(readchar_expr)
{
	fprintf(out, "getchar()");
}

C_VISITOR(cblock_stmt)
{
	// We just insert the code inside the block directly
	// into the output and hope the user knows what he's doing
	fprintf(out, "{\n");
	fprintf(out, "%s", node->value.literal_content);
	fprintf(out, "\n");
	_tab();
	fprintf(out, "}");
}

C_VISITOR(return_stmt)
{
	fprintf(out, "return");
	if (node->children)	{
		fprintf(out, " ");
		ast_node_accept(node->children, visitor);
	}
}

C_VISITOR(assignment_stmt)
{
	ast_node_accept(node->children, visitor);
	fprintf(out, " = ");
	ast_node_accept(node->children->sibling, visitor);
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
	
	++tab_level;
	ast_node_accept(child, visitor);
	
	if (child->kind != STATEMENT_LIST)	{
		_tab();
		fprintf(out, ";\n");
	}
	
	fprintf(out, "\n");
	--tab_level;
	_tab();
	fprintf(out, "}");
	
	child = child->sibling;					// Else Statements
	if (child)	{
		fprintf(out, " else {\n");
		++tab_level;
		ast_node_accept(child, visitor);
		if (child->kind != STATEMENT_LIST)	{
			_tab();
			fprintf(out, ";\n");
		}
		fprintf(out, "\n");
		--tab_level;
		_tab();
		fprintf(out, "}");
	}
}

C_VISITOR(while_stmt)
{
	AstNode* child;
	const char* var;
	
	fprintf(out, "while (");
	child = node->children;					// Expression
	ast_node_accept(child, visitor);
	fprintf(out, ") {\n");
	
	++tab_level;
	child = child->sibling;					// Statements
	ast_node_accept(child, visitor);
	--tab_level;
	fprintf(out, "\n");
	_tab();
	fprintf(out, "}");
}

C_VISITOR(for_stmt)
{
	AstNode* child;
	const char* var;
	
	fprintf(out, "for (");
	child = node->children;					// Assignment
	ast_node_accept(child, visitor);
	
	var = _identifier_get_cname(child->children->identifier);
	fprintf(out, " %s < ", var);			// TODO: WTF?
	
	child = child->sibling;					// Stop condition
	ast_node_accept(child, visitor);
	
	fprintf(out, "; %s++) {\n", var);		// TODO: More hard-coded crap
	
	++tab_level;
	child = child->sibling;					// Statements
	ast_node_accept_children(child, visitor);
	--tab_level;
	
	fprintf(out, "\n");
	_tab();
	fprintf(out, "}");
}

C_VISITOR(binary_expr)
{
	ast_node_accept_children(node->children, visitor);
}

C_VISITOR(notfactor)
{
	fprintf(out, "!");
	ast_node_accept_children(node->children, visitor);
}

C_VISITOR(call)
{
	fprintf(out, "%s (", _identifier_get_cname(node->children->identifier));
	if (node->children->sibling)	{
		// Parameters
		ast_node_accept(node->children->sibling, visitor);
	}
	fprintf(out, ")");
}

C_VISITOR(callparam_list)
{
	AstNode* param;
	for (param = node->children; (param); param = param->sibling)	{
		ast_node_accept(param, visitor);
		if (param->sibling)	{
			fprintf(out, ", ");
		}	
	}
}

C_VISITOR(callparam)
{
	// The expression for the call parameter
	ast_node_accept(node->children, visitor);
}

C_VISITOR(identifier)
{
	char* cname = _identifier_get_cname(node->identifier);
	fprintf(out, "%s", cname);
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

static void _tab()
{
	int i;
	for (i = 0; i < tab_level; i++)	{
		//fprintf(out, "%d%d%d%d", tab_level, tab_level, tab_level, tab_level);
		fprintf(out, "%s", TAB);
	}
}

static char* _get_type_string(Type type)
{
	switch (type)	{
		case INTEGER:
		case BOOLEAN:
			return "int";
		case CHAR:
			return "char";
		case DOUBLE:
			return "double";
		case FLOAT:
			return "float";
		case VOID:
			return "void";
		default:
			fprintf(stderr, "Inernal Compiler Error: _get_type_string: Unknown type %d\n", type);
			exit(1);
	}
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

/*
 *	CName handling: As we go through the code we generate names for the related C identifiers.  We want to 
 *	cache these when possible so we don't spend all our time making the same strings over and over again
 */

typedef struct CName_tag {
	Identifier* id;
	char* cname;
	struct CName_tag* next;
} CName;

static CName* _cname_cache = NULL;

CName* _cname_new(Identifier* id, char* cname)
{
	CName* cn = (CName*)malloc(sizeof(CName));
	cn->id = id;
	cn->cname = cname;
	cn->next = NULL;
	
	return cn;
}

void _cname_destroy(CName* cn)
{
	if (!cn)	{
		return;
	}
	
	_cname_destroy(cn->next);
	free(cn);
}

void _cname_cleanup()
{
	_cname_destroy(_cname_cache);
}

void _cname_insert(CName* cname)
{
	if (!_cname_cache)	{
		_cname_cache = cname;
	} else {
		CName* cn = _cname_cache;
		while (1)	{
			if (!cn->next)	{
				cn->next = cname;
				break;
			}
			
			cn = cn->next;
		}
	}
}

CName* _cname_lookup(Identifier* id)
{
	CName* cn = _cname_cache;
	if (!id || !cn)	{
		return NULL;
	}
	
	while (cn)	{
		if (cn->id == id)	{
			return cn;
		}
		
		cn = cn->next;
	}
	
	return NULL;
}

/* Gets the name that will be used for code generation */
char* _identifier_get_cname(Identifier* identifier)
{
	Scope* s = identifier->decl_scope;
	if (!s)	{
		return identifier->name;
	}
	
	AstNode* scope = s->decl_node;
	if (!scope)	{
		return identifier->name;
	}
	
	CName* cn = _cname_lookup(identifier);
	if (!cn)	{
		char *scope_name = NULL;
		if (scope->kind == NAMESPACE_DECL)	{
			scope_name = scope->children->identifier->name;
		} else if (scope->kind == FUNCTION)	{
			// Do nothing... stuff inside functions are scoped just just fine
			// inside C itself
		} else {
			fprintf(stderr, "Fatal Compiler Error: Unrecognized scope type %d in _identifer_get_cname\n", scope->kind);
			exit(1);
		}
				
		char* cname;
		if (identifier->params >= 0 && !strcmp(identifier->name, "main"))	{
			// HACK: Makes sure we have an actual function called main so the C compiler can find
			//		and entry point.  Fix this by passing the name of the main function to the compiler
			asprintf(&cname, "%s", identifier->name);
		}
		else if (!scope_name) {
			asprintf(&cname, "%s", identifier->name);
		} else {
			asprintf(&cname, "%s_%s", scope_name, identifier->name);
		}
		
		cn = _cname_new(identifier, cname);
		_cname_insert(cn);		
		
		//fprintf(stderr, "Making a cname: %s\n", cname);

	}
	
	return cn->cname;
}