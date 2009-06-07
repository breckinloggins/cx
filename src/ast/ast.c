/* 
 *	General Functions for the manipulation of Cx's Abstract Syntax Tree
 */

#include "../common/memory.h"
#include "ast.h"

astnode* astnode_new(nodetype type)
{
	astnode* n = (astnode*)malloc(sizeof(astnode));
	
	astnode_init(n, type, 0);
	return n;
}

void astnode_init(astnode* node, nodetype type, void (*cleanup)(astnode*))
{
	node->type = type;
	node->parent = NULL;
	node->children = NULL;
	node->cleanup = cleanup;	
}

void astnode_destroy(astnode* node)
{
	// Destroy the children first (that sounds bad)
	list_e* child = 0;
	for (child = node->children; (child); child = child->next)	{
		astnode_destroy(child->p);
		child->p = 0;				// So list_free_forward won't free it again
	}
	
	list_free_forward(node->children);
	
	// Now, if there's any special handling that this node needs, let it 
	// do it
	if (node->cleanup)
		node->cleanup(node);
	
	free(node);
}