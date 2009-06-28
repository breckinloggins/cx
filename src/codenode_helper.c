/*
 * The functions in this module know about the "structure" of the AST and expose that knowledge via convenience methods that
 * return various parts of the AST.  The functions here also verify that the structure of the AST is valid according to its
 * knowledge of the language.  This part of it may be disabled in RELEASE configurations, depending on the stability of the
 * compiler.
 */

#include <stdio.h>
#include <stdlib.h>

#include "common/memory.h"
#include "codenode_helper.h"
#include "parser.h"

static void _verify_node(AstNode* node, int kind, const char* function);

AstNode* function_get_identifier(AstNode* function)
{
	_verify_node(function, FUNCTION, "function_get_identifier");
	_verify_node(function->children, IDENTIFIER, "function_get_identifier");
	
	return function->children;
}

AstNode* function_get_params(AstNode* function)
{
	AstNode* ident = function_get_identifier(function);
	_verify_node(ident->sibling, PARAM_LIST, "function_get_params");
		
	return ident->sibling; 
}

AstNode* function_get_statements(AstNode* function)
{
	AstNode* params = function_get_params(function);
	_verify_node(params->sibling, STATEMENT_LIST, "function_get_statements");
	
	return params->sibling;
}

int paramlist_get_count(AstNode* params)
{
	_verify_node(params, PARAM_LIST, "paramlist_get_count");
	int count = 0;
	AstNode* child;
	for (child = params->children; (child); child = child->sibling)	{
		_verify_node(child, PARAMETER, "paramlist_get_count");
		++count;
	}
	
	return count;
}

int callparamlist_get_count(AstNode* callparams)
{
	_verify_node(callparams, CALLPARAM_LIST, "callparamlist_get_count");
	int count = 0;
	AstNode* child;
	for (child = callparams->children; (child); child = child->sibling)	{
		_verify_node(child, CALLPARAM, "callparamlist_get_count");
		++count;
	}
	
	return count;
}


static void _verify_node(AstNode* node, int kind, const char* function)
{
	// TODO: We may want to make this a no op in release mode
	if (node == NULL || node->kind != kind)	{
		fprintf(stderr, "Fatal Compiler Error: Node is not the correct type in %s()\n", function);
		exit(1);
	}
}