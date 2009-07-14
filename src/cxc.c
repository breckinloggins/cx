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
#define CC_O_FORMAT "cc -o %s %s"	
#define CC_C_FORMAT "cc -c %s"

char* get_extension(const char* filename)
{
	int i = 0;
	int len = strlen(filename);
	int j = len;
	
	char* p = (char*)filename;
	while (*p)	{
		if (*p == PATH_SEPARATOR && j < len)	{
			j = len;	// Rest because the dot we found was part of the path, NOT
						// the file
		}
		
		if (*p == '.')	{
			j = p - filename + 1;
		}
		
		p++;
	}
	
	if (j == len)	{
		// None found
		return NULL;
	}
	
	char* ext = (char*)malloc((len - j)*sizeof(char));
	p = (char*)&filename[j];
	int n = 0;
	while (*p)	{
		ext[n++] = *p++;
	}
	
	return ext;
}

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
extern AstNode* parse_ast;
extern int yydebug;

static AstNode* ast;

typedef struct InputFile_tag	{
	char* fullpath;
	char* name_noext;
	AstNode* parse_ast;
	struct InputFile_tag* next;
} InputFile;

InputFile* inputfile_new()
{
	InputFile* infile = (InputFile*)malloc(sizeof(InputFile));
	infile->fullpath = NULL;
	infile->name_noext = NULL;
	infile->parse_ast = NULL;
	infile->next = NULL;
	
	return infile;
}

void inputfile_destroy(InputFile* infile, bool deep)
{
	if (!infile)	{
		return;
	}
	
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
static char* ofile = NULL;
static int compile_flag = 0;
static int link_flag = 0;
static int stdout_flag = 0;
static int graph_flag = 0;

void usage()
{
	fprintf(stderr, "Usage: cxc [options] <filename>\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "\t-s\tPrint the generated code to stdout\n");
	fprintf(stderr, "\t-c\tCompile\n");
	fprintf(stderr, "\t-o name\tOutput an executable\n");
	fprintf(stderr, "\t-g\tOutput AST Graph\n");	
}

void cleanup_exit(int error_code)	{
	if (!ast)	{
		ast_node_destroy(parse_ast);
	}
	else	{
		ast_node_destroy(ast);
	}
	
	free(ofile);
	inputfile_destroy(input_files, TRUE);
	context_cleanup();
	c_codegen_cleanup();
	exit(error_code);
}

int parseopts(int argc, char** argv)
{
	if (argc < 2)	{
		usage();
		exit(1);
	}
	
	int ch;
	while ((ch = getopt(argc, argv, "scgo:")) != -1)	{
		switch (ch)	{
			case 's':
				stdout_flag = 1;
				break;
			case 'c':
				compile_flag = 1;
				break;
			case 'g':
				graph_flag = 1;
				break;
			case 'o':
				link_flag = 1;
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
	
	if (!stdout_flag && !compile_flag && !graph_flag && !link_flag)	{
		compile_flag = 1;
	}
	
	if (stdout_flag && (compile_flag || link_flag))	{
		fprintf(stderr, "Standard Out flag cannot currently be used with the Compile or Link options\n");
		cleanup_exit(1);
	}
	
	if (compile_flag && link_flag)	{
		fprintf(stderr, "Compile option cannot be used with Link option\n");
		cleanup_exit(1);
	}
	
	if (compile_flag && graph_flag)	{
		fprintf(stderr, "Compile option cannot be used with Graph option\n");
		cleanup_exit(1);
	}
	
	if (graph_flag & link_flag)	{
		fprintf(stderr, "Output option cannot be used with Graph option\n");
		cleanup_exit(1);
	}
		
	if (!argc)	{
		fprintf(stderr, "No input file\n");
		cleanup_exit(1);
	}
	
	int i;
	for (i = 0; i < argc; i++)	{
		input_files = inputfile_insert(input_files, argv[i]);
	}
	
	return argc;
}

int main(int argc, char** argv)
{
	atexit(checkmem);
	//yydebug = 1;
	
	argc = parseopts(argc, argv);
	
	// Create the master tree.  All parse trees from the inputted translation units will be children
	// of TARGET
	ast = ast_node_new("Target", TARGET, VOID, 0);
	
	InputFile* in = input_files;
	while (in)	{
		yyin = fopen(in->fullpath, "r");
		if (!yyin)	{
			fprintf(stderr, "The file specified (\"%s\") does not exist or could not be opened\n", in->fullpath);
			cleanup_exit(1);
		}
		
		char* ext = get_extension(in->fullpath);
		if (ext && !strcmp(ext, "cx"))	{	// HACK: We should probably not do this based on file ext	
			yyparse();
			
			// If we got here we can be sure of no syntax errors, so add this parse tree to the main
			// AST
			ast_node_add_child(ast, parse_ast);
			in->parse_ast = parse_ast;
		}
		
		free(ext);		
		fclose(yyin);
		
		in = in->next;
	}
				
	// Setup the standard environment, which includes some builtin complex types, 
	//	functions, etc.
	stdenv_init(ast);
	
	// Next, we'll do some contextual analysis on the parse tree
	Visitor* context_visitor = context_new();
	ast_node_accept(ast, context_visitor);
	free(context_visitor);
	
	if (ast_node_check_errors(ast) && !graph_flag)	{
		fprintf(stderr, "Errors in compilation\n");
		cleanup_exit(1);
	}
	
	// Finally, time to generate the output, using one of the several generator visitors
	Visitor* visitor;
	if (compile_flag || link_flag || stdout_flag)	{
		// TODO: None of this code is safe!
		InputFile* in;
		
		char* infiles = NULL;
		int infiles_length = 257*argc*sizeof(char);	// Max PATH length + one space per arg
		if (link_flag || compile_flag)	{
			infiles = (char*)malloc(infiles_length);
			memset(infiles, 0, infiles_length);
		}	
		
		for (in = input_files; (in); in = in->next)	{
			FILE* out = stdout;
	
			char* cfile;
			char* ext = "c";
			if (!in->parse_ast)	{
				// Binary file
				ext = "o";
			}
	
			if (link_flag || compile_flag)	{
				asprintf(&cfile, "%s.%s", in->name_noext, ext);
																
				if (strlen(infiles) + strlen(cfile) > (infiles_length - 1))	{
					infiles_length += strlen(cfile);
					infiles = (char*)realloc(infiles, infiles_length);
				}
				
				strcat(infiles, " ");								
				strcat(infiles, cfile);
				
				out = fopen(cfile, "w");
				free(cfile);
			}

			if (in->parse_ast)	{
				visitor = c_codegen_new(out);
				ast_node_accept(in->parse_ast, visitor);
				free(visitor);
			}
			
			if (out != stdout)	{
				fclose(out);
			}
		}
		
		if (compile_flag)	{
			char* cmd;
			asprintf(&cmd, CC_C_FORMAT, infiles);
			system(cmd);
			free(cmd);
		}
		else if (link_flag)	{
			char* cmd;
			asprintf(&cmd, CC_O_FORMAT, ofile, infiles);
			system(cmd);
			free(cmd);
		}
		
		free(infiles);
		
		
	} else if (graph_flag)	{
		visitor = graphprinter_new(stdout);
		ast_node_accept(ast, visitor);
		free(visitor);
	}
	
	cleanup_exit(0);
}


