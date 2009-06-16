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
		fprintf(stderr, "Usage: cxc [options] <filename>\n");
		fprintf(stderr, "Options:\n");
		fprintf(stderr, "\t-c\tCompile\n");
		fprintf(stderr, "\t-g\tOutput AST Graph\n");
		return 1;
	}
	
	int compile_flag = 1;
	int graph_flag = 0;
	char* filename;
	
	// TODO: Unsafe code
	if (argv[1][0] == '-')	{
		switch (argv[1][1])	{
			case 'c':
				compile_flag = 1;
				graph_flag = 0;
				break;
			case 'g':
				compile_flag = 0;
				graph_flag = 1;
				break;
			default: 
				fprintf(stderr, "Unrecognized option '%c'\n", argv[1][1]);
				exit(1);
		}
		
		if (argc < 3)	{
			fprintf(stderr, "No input file\n");
			exit(1);
		}
		
		filename = argv[2];
	} else {
		filename = argv[1];
	}
	
	
				
	yyin = fopen(filename, "r");
	
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
	
	Visitor* visitor;
	if (compile_flag)	{
		visitor = c_codegen_new(stdout);
		ast_node_accept(ast, visitor);
		free(visitor);
	} else if (graph_flag)	{
		visitor = graphprinter_new(stdout);
		ast_node_accept(ast, visitor);
		free(visitor);
	}
	
	ast_node_destroy(ast);
	context_cleanup();
	return 0;
}


