/*
 * Functions for the manipulation of Translation Unit nodes in the Cx AST
 */

#include "../common/memory.h"
#include "ast.h"			

transunit_node* transunit_new()
{
	transunit_node* t = (transunit_node*)malloc(sizeof(transunit_node));
	astnode_init((astnode*)t, transunit_n, 0);
	
	return t;
}
									
namespace_node* transunit_new_namespace(transunit_node* t, const char* namespace)
{
	namespace_node* ns = namespace_new(namespace);
	
	list_e* ns_e = list_e_new(ns, 1);
	if (t->node.children)	{
		list_e_insert_after(list_last(t->node.children), ns_e);
	}
	else	{
		t->node.children = ns_e;
	}
	
	ns->node.parent = (astnode*)t;
	
	return ns;
}

