/*
 * Functions for generating target code based on a Cx AST
 */

#include <string.h>

#include "cgen.h"
#include "../common/memory.h"

static void strrep(char* src, char old, char new)
{
	while (*src != '\0')	{
		if (*src == old)
			*src = new;
		src += sizeof(char);
	}
}

void cgen_transunit(FILE* f, transunit_node* t)
{
	if (!t) return;
	
	list_e* ns_e;
	for (ns_e = t->node.children; (ns_e); ns_e = ns_e->next)	{
		cgen_namespace(f, (namespace_node*)ns_e->p);
		fprintf(f, "\n");
	}
}

void cgen_namespace(FILE* f, namespace_node* ns)
{
	if (!ns) return;
	fprintf(f, "/* Begin Namespace: %s */\n", ns->name);
	
	list_e* fn_e;
	for (fn_e = ns->node.children; (fn_e); fn_e = fn_e->next)	{
		cgen_function(f, (function_node*)fn_e->p);
		fprintf(f, "\n");
	}
	
	fprintf(f, "/* End Namespace: %s */\n", ns->name);
}

void cgen_function(FILE* f, function_node* fn)
{
	char* cname = (char*)malloc(strlen(fn->name) * strlen(((namespace_node*)fn->node.parent)->name) + 2);
	sprintf(cname, "%s_%s", ((namespace_node*)fn->node.parent)->name, fn->name);
	strrep(cname, '.', '_');
	fprintf(f, "%s %s(%s)\n", fn->return_type, cname, fn->arg);
	fprintf(f, "{\n");
	fprintf(f, "\t// Function body\n");
	fprintf(f, "}\n");
	free(cname);
}