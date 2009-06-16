/*
 *	Main Cx Compiler executable
 */

#include <stdio.h>
#include <string.h>

#include "common/memory.h"
#include "ast/ast.h"
#include "parser.tab.h"
#include "context_visitor.h"
#include "c_codegen_visitor.h"
#include "graphprinter_visitor.h"

extern FILE* yyin;
extern AstNode* ast;
extern int yydebug;

int main(int argc, char** argv)
{
	atexit(checkmem);
	//yydebug = 1;
	
	if (argc < 2)	{
		fprintf(stderr, "Usage: cxc <filename>\n");
		return 1;
	}
	
	yyin = fopen(argv[1], "r");
	
	yyparse();
	
	// First, we'll do some contextual analysis on the parse tree
	Visitor* context_visitor = context_new();
	ast_node_accept(ast, context_visitor);
	free(context_visitor);
	
	if (ast_node_check_errors(ast))	{
		fprintf(stderr, "Too many errors to compile\n");
		ast_node_destroy(ast);
		context_cleanup();
		return 1;
	}
	
	
	
	Visitor* visitor = c_codegen_new(stdout);
	ast_node_accept(ast, visitor);
	free(visitor);
	
	ast_node_destroy(ast);
	context_cleanup();
	return 0;
}


