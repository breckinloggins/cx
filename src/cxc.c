/*
 *	Main Cx Compiler executable
 */

#include <stdio.h>
#include <string.h>

#include "common/memory.h"
#include "ast/ast.h"
#include "cgen/cgen.h"

int main(int argc, char** argv)
{
	atexit(checkmem);
	
	transunit_node* trans = transunit_new();
	namespace_node* ns_system = transunit_new_namespace(trans, "System");
	namespace_node* ns_collections = transunit_new_namespace(trans, "System.Collections");
	namespace_node* ns_io = transunit_new_namespace(trans, "System.IO");
	
	namespace_new_function(ns_system, "WriteLine", "void", "string line");
	namespace_new_function(ns_system, "ReadLine", "string", "void");
	
	namespace_new_function(ns_collections, "ToArray", "int[]", "IList list");
	
	namespace_new_function(ns_io, "OpenFile", "FileHandle", "string path");
	
	cgen_transunit(stderr, trans);
	
	astnode_destroy((astnode*)trans);
	
	
	return 0;
}


