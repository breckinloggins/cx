#ifndef IDENTIFIER_TABLE_H
#define IDENTIFIER_TABLE_H

#include "base.h"

typedef struct Scope_tag	{
	struct Scope_tag* parent;			// This scope's enclosing scope
	struct AstNode_tag* decl_node;		// The node that encompasses this scope, for example, a NAMESPACE or FUNCTION
	struct Identifier_tag* idtable;		// Pointer to the list of identifiers for this scope
} Scope;

typedef struct Identifier_tag	{
	char* name;							// The name of the identifier as declared in source
	Type type;
	Value value;
	int decl_linenum;
	struct Scope_tag* decl_scope;		// The scope in which this identifier was declared
	
	// For functions
	int params;
	Type* param_types;
	
	struct Identifier_tag* next;
} Identifier;

Identifier* identifier_new(const char* name);
void identifier_destroy(Identifier* identifier);
void identifier_create_params(Identifier* identifier, int quantity);

Scope*		scope_new(Scope* parent, struct AstNode_tag* decl_node);
void		scope_destroy_all();
Identifier*	scope_lookup(Scope* scope, char* name);
Identifier* scope_insert(Scope* scope, Identifier* id);

#endif // IDENTIFIER_TABLE_H