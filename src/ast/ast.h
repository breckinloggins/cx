#ifndef AST_H
#define AST_H

#include "../common/list.h"

/*
 *	Routines for construction and manipulation of the Cx Abstract Syntax Tree
 */

typedef enum { transunit_n, namespace_n } nodetype;

/* Represents the root structure of every node in the AST.  All other types of nodes
 * "inherit" from this base node.
 */
typedef struct astnode_tag	{
	nodetype type;					// The type of node this represents
	struct astnode_tag* parent;		// The parent of this AST node
	list_e* children;				// The child nodes (if any) of this AST node
} astnode;

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
typedef struct namespace_tag	{
	astnode node;
	
	const char* name;				// The fully-qualified name of the namespace
}

#endif