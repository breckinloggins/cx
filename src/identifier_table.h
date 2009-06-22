#ifndef IDENTIFIER_TABLE_H
#define IDENTIFIER_TABLE_H

#include "base.h"

typedef struct Identifier_tag	{
	char* name;							// The name of the identifier as declared in source
	Type type;
	Value value;
	int decl_linenum;
	struct AstNode_tag* decl_scope_node;	// The innermost scoping node in which this identifier was
											// declared.  For example, a NAMESPACE, FUNCTION, or CLASS node
	
	// For functions
	int params;
	Type* param_types;
	
	bool is_global;
	int stack_index;
	
	struct Identifier_tag* next;
} Identifier;

Identifier* identifier_new(const char* name);
Identifier* identifier_lookup(Identifier* idtable, const char* name);
Identifier* identifier_insert(Identifier* idtable, Identifier* identifier);
void identifier_destroy(Identifier* identifier);

void identifier_create_params(Identifier* identifier, int quantity);
bool identifier_is_function(Identifier* identifier);
void identifier_print(Identifier* identifier);

void identifier_table_destroy(Identifier* idtable);
void identifier_table_dump(Identifier* idtable);

#endif // IDENTIFIER_TABLE_H