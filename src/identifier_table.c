#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/memory.h"
#include "ast.h"
#include "identifier_table.h"

Identifier* _identifier_lookup(Identifier* idtable, const char* name)
{
	Identifier* temp;
	
	if (idtable == NULL)
		return NULL;
		
	for (temp = idtable; (temp); temp = temp->next)	{
		if (!strcmp(temp->name, name))
			return temp;
	}
	
	return temp;
}

Identifier* _identifier_insert(Identifier* idtable, Identifier* identifier)
{
	Identifier* id;
	
	if (identifier == NULL)
		return NULL;
	
	id = _identifier_lookup(idtable, identifier->name);
	
	if (id)	{
		identifier_destroy(identifier);
		return id;
	}
	
	identifier->next = idtable->next;
	idtable->next = identifier;
	
	return identifier;
}

void _identifier_print(Identifier* identifier)
{
	if (identifier == NULL)	{
		printf("NULL\n\n");
		return;
	}
	
	printf("Identifier: %x\n", identifier);
	printf("\tname: %s\n", identifier->name);
	printf("\ttype: %d\n", identifier->type);
	printf("\tvalue: ");
	value_print(stdout, &identifier->value, identifier->type);
	int decl_linenum = 0;
	if (identifier->decl_node)	{
		decl_linenum = identifier->decl_node->linenum;
	}
	printf("\n\tdeclaration line: %d\n", decl_linenum);
	printf("\tnext: %x\n\n", identifier->next);
}

void _identifier_table_destroy(Identifier* idtable)
{
	if (!idtable)	{
		return;
	}
	
	_identifier_table_destroy(idtable->next);
	identifier_destroy(idtable);
}

void _identifier_table_dump(Identifier* idtable)
{
	Identifier* temp = idtable;
	
	for (temp = idtable->next; (temp); temp = temp->next)
		_identifier_print(temp);
}

// When scopes are created, we keep track of them in lists made up of these nodes
typedef struct _ScopeNode_tag	{
	Scope scope;
	struct _ScopeNode_tag* next;
} _ScopeNode;

static _ScopeNode* _scopes = NULL;

void _scopenode_destroy(_ScopeNode* sn)
{
	if (!sn)	{
		return;
	}
	
	if (sn->next)	{
		_scopenode_destroy(sn->next);
	}
	
	if (sn->scope.idtable)	{
		_identifier_table_destroy(sn->scope.idtable);
	}
	
	free(sn);
}

/*
 * Public Functions
 */

Identifier* identifier_new(const char* name)
{
	Identifier* identifier = (Identifier *)malloc(sizeof(Identifier));

	identifier->type = VOID;
	value_set(&identifier->value, identifier->type, NULL);
	identifier->decl_scope = NULL;
	identifier->decl_node = NULL;
	identifier->next = NULL;

	if (name != NULL)
		identifier->name = strdup(name);
	else
		identifier->name = NULL;

	return identifier;
}

void identifier_destroy(Identifier* identifier)
{
	free(identifier->name);
	
	free(identifier);
	
	// The following don't belong to us:
	//	- decl_node
	//	- decl_scope
}

Scope* scope_new(Scope* parent, struct AstNode_tag* decl_node)
{
	_ScopeNode* sn = (_ScopeNode*)malloc(sizeof(_ScopeNode));
	sn->next = _scopes;
	_scopes = sn;
	
	// We return the underlying scope to the user, who is blissfully unaware that we 
	// are keeping track of them.  Sneaky Sneaky.	
	Scope* scope = &sn->scope;
	scope->parent = parent;
	scope->decl_node = decl_node;
	scope->idtable = NULL;
		
	return scope;
}

void scope_destroy_all()
{
	_scopenode_destroy(_scopes);
}

Identifier*	scope_lookup(Scope* scope, char* name)
{
	Identifier* id = _identifier_lookup(scope->idtable, name);
	if (!id && scope->parent)	{
		// Not here, but we have an enclosing scope, look for it there
		id = scope_lookup(scope->parent, name);
	}
	
	return id;	// NULL if no identifier by this name
}

Identifier* scope_insert(Scope* scope, Identifier* id)
{
	// NOTE: We don't check for duplicates here.  Implementation code needs
	//	to do that
	id->decl_scope = scope;
	
	if (scope->idtable)	{
		id = _identifier_insert(scope->idtable, id);
	} else {
		scope->idtable = id;
	}
	
	return id;
}