/* 
 * Functions for the manipulation of Function nodes in the Cx AST
 */

#include <string.h>

#include "../common/memory.h"
#include "ast.h"

function_node* function_new(const char* name, const char* return_type, const char* arg)
{
	function_node* fn = (function_node*)malloc(sizeof(function_node));
	astnode_init((astnode*)fn, function_n, function_cleanup);
	
	fn->name = (char*)malloc(strlen(name) * sizeof(char));
	fn->return_type = (char*)malloc(strlen(return_type) * sizeof(char));
	fn->arg = (char*)malloc(strlen(arg) * sizeof(char));
	
	strcpy(fn->name, name);
	strcpy(fn->return_type, return_type);
	strcpy(fn->arg, arg);
	
	return fn;
}

void function_cleanup(astnode* function)
{
	free(((function_node*)function)->name);
	free(((function_node*)function)->return_type);
	free(((function_node*)function)->arg);
}