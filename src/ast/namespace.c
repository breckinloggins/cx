/* 
 * Functions for the manipulation of Namespace nodes in the Cx AST
 */

#include <string.h>

#include "../common/memory.h"
#include "ast.h"

namespace_node* namespace_new(const char* name)
{
	namespace_node* ns = (namespace_node*)malloc(sizeof(namespace_node));
	astnode_init((astnode*)ns, namespace_n, namespace_cleanup);
	
	ns->name = (char*)malloc(strlen(name) * sizeof(char));
	strcpy(ns->name, name);
	
	return ns;
}

void namespace_cleanup(astnode* namespace)
{
	free(((namespace_node*)namespace)->name);
}

function_node* namespace_new_function(namespace_node* ns, const char* name, const char* return_type, const char* arg)
{
	function_node* fn = function_new(name, return_type, arg);
	
	list_e* fn_e = list_e_new(fn, 1);
	if (ns->node.children)	{
		list_e_insert_after(list_last(ns->node.children), fn_e);
	}
	else	{
		ns->node.children = fn_e;
	}
	
	fn->node.parent = (astnode*)ns;
	
	return fn;
}
