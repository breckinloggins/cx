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
