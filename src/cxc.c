/*
 *	Main Cx Compiler executable
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>		// TODO: Not Windows portable

#include "common/memory.h"
#include "ast.h"
#include "parser.h"
#include "standard_environment.h"
#include "context_visitor.h"
#include "c_codegen_visitor.h"
#include "graphprinter_visitor.h"

// TODO: Parameterize these for different platforms
#define PATH_SEPARATOR '/'
#define CC_FORMAT "cc -o %s %s"	


char* get_filename_noext(const char* filename)
{
	int i = 0;
	int j = strlen(filename);

	char* p = (char*)filename;
	while (*p)	{
		if (*p == PATH_SEPARATOR)	{
			i = p - filename + 1;
		}

		if (*p == '.')	{
			j = p - filename;
		}

		p++;
	}

	// One would sure hope that after this, i < j (unless there was a dot in the path spec but not one in the file)
	if (i > j) j = strlen(filename);

	char* name = (char*)malloc((j-i+1)*sizeof(char));
	p = (char*)&filename[i];
	int n = 0;
	while (p != &filename[j])	{
		name[n++] = *p++;
	}

	return name;
}

extern FILE* yyin;
extern AstNode* ast;
extern int yydebug;

typedef struct InputFile_tag	{
	char* fullpath;
	char* name_noext;
	struct InputFile_tag* next;
} InputFile;

InputFile* inputfile_new()
{
	InputFile* infile = (InputFile*)malloc(sizeof(InputFile));
	infile->fullpath = NULL;
	infile->name_noext = NULL;
	infile->next = NULL;
	
	return infile;
}

void inputfile_destroy(InputFile* infile, bool deep)
{
	if (deep && infile->next)	{
		inputfile_destroy(infile->next, TRUE);
	}
	
	free(infile->fullpath);
	free(infile->name_noext);
	free(infile);
}

InputFile* inputfile_insert(InputFile* insertBefore, const char* fullpath)
{
	InputFile* infile = inputfile_new();
	infile->fullpath = strdup(fullpath);
	infile->name_noext = get_filename_noext(infile->fullpath);
	
	infile->next = insertBefore;
	
	return infile;
}

static InputFile* input_files = NULL;

void usage()
{
	fprintf(stderr, "Usage: cxc [options] <filename>\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "\t-c\tCompile\n");
	fprintf(stderr, "\t-o\tOutput an executable (implies -c)\n");
	fprintf(stderr, "\t-g\tOutput AST Graph\n");	
}

int main(int argc, char** argv)
{
	atexit(checkmem);
	//yydebug = 1;
	
	if (argc < 2)	{
		usage();
		return 1;
	}
	
	int compile_flag = 0;
	int graph_flag = 0;
	int output_flag = 0;
	char* filename;
	char* ofile = NULL;
	
	int ch;
	while ((ch = getopt(argc, argv, "cgo:")) != -1)	{
		switch (ch)	{
			case 'c':
				compile_flag = 1;
				break;
			case 'g':
				graph_flag = 1;
				break;
			case 'o':
				compile_flag = 1;
				output_flag = 1;
				ofile = strdup(optarg);
				break;
			case '?':
			default:
				usage();
				exit(1);
		}
	}
	argc -= optind;
	argv += optind;
	
	if (!compile_flag && !graph_flag && !output_flag)	{
		compile_flag = 1;
	}
	
	if (!output_flag)	{
		ofile = strdup("a.out");
	}
	
	if (compile_flag && graph_flag)	{
		fprintf(stderr, "Compile option cannot be used with Graph option\n");
		free(ofile);
		exit(1);
	}
	
	if (graph_flag & output_flag)	{
		fprintf(stderr, "Output option cannot be used with Graph option\n");
		free(ofile);
		exit(1);
	}
		
	if (!argc)	{
		fprintf(stderr, "No input file\n");
		free(ofile);
		exit(1);
	}
		
	filename = argv[0];
	
	input_files = inputfile_insert(NULL, filename);
			
	yyin = fopen(input_files->fullpath, "r");
	if (!yyin)	{
		fprintf(stderr, "The file specified (\"%s\") does not exist or could not be opened\n", input_files->fullpath);
		inputfile_destroy(input_files, TRUE);
		free(ofile);
		exit(1);
	}
	
	char* cfile;
	asprintf(&cfile, "%s_gen.c", input_files->name_noext);
	
	inputfile_destroy(input_files, TRUE);
	
	yyparse();
	fclose(yyin);
	
	// First, we'll setup the standard environment, which includes some builtin complex types, 
	//	functions, etc.
	stdenv_init(ast);
	
	// Next, we'll do some contextual analysis on the parse tree
	Visitor* context_visitor = context_new();
	ast_node_accept(ast, context_visitor);
	free(context_visitor);
	
	if (ast_node_check_errors(ast) && !graph_flag)	{
		fprintf(stderr, "Errors in compilation\n");
		ast_node_destroy(ast);
		context_cleanup();
		free(cfile);
		free(ofile);
		return 1;
	}
	
	// Finally, time to generate the output, using one of the several generator visitors
	Visitor* visitor;
	if (compile_flag)	{
		FILE* out = stdout;
		if (output_flag)	{
			out = fopen(cfile, "w");
		}
		
		visitor = c_codegen_new(out);
		ast_node_accept(ast, visitor);
		free(visitor);
		
		if (output_flag)	{
			fclose(out);
			
			char* cmd;
			asprintf(&cmd, CC_FORMAT, ofile, cfile);
			system(cmd);
			free(cmd);
		}
	} else if (graph_flag)	{
		visitor = graphprinter_new(stdout);
		ast_node_accept(ast, visitor);
		free(visitor);
	}
	
	ast_node_destroy(ast);
	context_cleanup();
	c_codegen_cleanup();
	free(cfile);
	free(ofile);
	return 0;
}


