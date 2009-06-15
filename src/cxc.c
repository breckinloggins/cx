/*
 *	Main Cx Compiler executable
 */

#include <stdio.h>
#include <string.h>

#include "common/memory.h"
#include "ast/ast.h"
#include "parser.tab.h"
#include "c_codegen_visitor.h"

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
	
	Visitor* visitor = c_codegen_new(stdout);
	ast_node_accept(ast, visitor);
	free(visitor);
	
	ast_node_destroy(ast);
	return 0;
}


