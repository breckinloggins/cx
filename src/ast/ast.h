#ifndef AST_H
#define AST_H

#include "../common/list.h"

/*
 *	Routines for construction and manipulation of the Cx Abstract Syntax Tree
 */

typedef enum { transunit_n, namespace_n, function_n } nodetype;

/* Represents the root structure of every node in the AST.  All other types of nodes
 * "inherit" from this base node.
 */
typedef struct astnode_tag	{
	nodetype type;					// The type of node this represents
	struct astnode_tag* parent;		// The parent of this AST node
	list_e* children;				// The child nodes (if any) of this AST node
	
	void (*cleanup)(struct astnode_tag* n);	// A pointer to a function that, if implemented, will be called
											// when this AST node is destroyed.
} astnode;

/* 
 * A Function in Cx is strictly a namespace-level concept.  In classes, functions are represented by
 * class_method nodes.
 */
typedef struct function_node_tag	{
	astnode node;
	
	char* name;						// The name of this function
	char* return_type;				// (TEMP) A string representing the return type
	char* arg;						// (TEMP) A string representing the arguments
} function_node;

/* A Namespace is the top-level syntactic organization structure in Cx programs.  Multiple namespaces are
 * orgianized into a Translation Unit (see above).
 *
 * Cx namespaces can contain: Fields, Properties, Classes, Structs, Unions, and Functions
 * Note that functions in a Cx namespace don't the equivalent of a Class's "this" pointer.  Namespace are to be 
 * thought of as simply "bags of code" and do not have any object-oriented concepts baked into them.
 *
 * The generated C-name of a namespace object is well-defined: it is simply "namespace_object".  So, for example, 
 * a C-module could call the function Start() in the namespace MyApp by referring to it is MyApp_Start();
 */
typedef struct namespace_node_tag	{
	astnode node;
	
	char* name;						// The fully-qualified name of the namespace
} namespace_node;

/* A Translation Unit (a concept borrowed from C) is the fundamental unit of compilation
 * for Cx programs.  Each translation unit corresponds to a .o output file in most environments, 
 * or, for example, an Assembly in .NET.  Translation units consists of one or more Namespaces.
 * 
 * We use Namespaces as the building blocks of Translation Units so that the compiler is not tied
 * to a concept of a "file" (for example, the compiler doesn't care if each namespace is stored in a BLOB
 * in a database).
 */
typedef struct transunit_node_tag	{
	astnode node;						
	
	// NOTE: The namespaces are stored in the node's children nodelist.  Use the convenience functions
	//			for transunit_node to access them
} transunit_node;

/*
 * General Abstract Syntax Tree Functions (ast.c)
 */
astnode* astnode_new(nodetype type);
void astnode_init(astnode* node, nodetype type, void (*cleanup)(astnode*));
void astnode_destroy(astnode* node);				// Destroys this node and every node under it

/*
 * Function Functions (function.c)
 */
function_node* function_new(const char* name, const char* return_type, const char* arg);
void function_cleanup(astnode* function);

/*
 * Namespace Functions (namespace.c)
 */
namespace_node* namespace_new(const char* name);
void namespace_cleanup(astnode* namespace);
function_node* namespace_new_function(namespace_node* ns, const char* name, const char* return_type, const char* arg);

/* 
 * Translation Unit Functions (transunit.c)
 */
transunit_node* transunit_new();									
namespace_node* transunit_new_namespace(transunit_node* t, const char* namespace);	


#endif