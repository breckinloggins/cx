#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/memory.h"
#include "identifier_table.h"

Identifier* identifier_new(const char* name)
{
	Identifier* identifier = (Identifier *)malloc(sizeof(Identifier));
	
	identifier->type = VOID;
	value_set(&identifier->value, identifier->type, NULL);
	identifier->params = -1;
	identifier->param_types = NULL;
	identifier->decl_linenum = 0;
	identifier->is_global = FALSE;
	identifier->stack_index = -1;
	identifier->decl_scope_node = NULL;
	
	identifier->next = NULL;
	
	if (name != NULL)
		identifier->name = strdup(name);
	else
		identifier->name = NULL;
			
	return identifier;
}

Identifier* identifier_insert(Identifier* idtable, Identifier* identifier)
{
	Identifier* id;
	
	if (identifier == NULL)
		return NULL;
	
	id = identifier_lookup(idtable, identifier->name);
	
	if (id)	{
		identifier_destroy(identifier);
		return id;
	}
	
	identifier->next = idtable->next;
	idtable->next = identifier;
	
	return identifier;
}

Identifier* identifier_lookup(Identifier* idtable, const char* name)
{
	Identifier* temp;
	
	if (idtable == NULL)
		return NULL;
		
	for (temp = idtable->next; (temp); temp = temp->next)	{
		if (!strcmp(temp->name, name))
			return temp;
	}
	
	return temp;
}

void identifier_create_params(Identifier* identifier, int quantity)
{
	identifier->params = quantity;
	if (quantity > 0)
		identifier->param_types = (Type *)malloc(sizeof(Type) * quantity);
}

bool identifier_is_function(Identifier* identifier)
{
	return (identifier->params > -1);
}

void identifier_print(Identifier* identifier)
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
	printf("\n\tdeclaration line: %d\n", identifier->decl_linenum);
	printf("\tnext: %x\n\n", identifier->next);
}

void identifier_destroy(Identifier* identifier)
{
	free(identifier->name);
	free(identifier);
	
	// The following don't belong to us:
	//	- decl_scope_node
}

void identifier_table_destroy(Identifier* idtable)
{
	Identifier* first;
	Identifier* to_kill;
	first = idtable->next;
	idtable->next = NULL;
	
	while (first)	{
		to_kill = first;
		first = first->next;
		identifier_destroy(to_kill);
	}
}

void identifier_table_dump(Identifier* idtable)
{
	Identifier* temp = idtable;
	
	for (temp = idtable->next; (temp); temp = temp->next)
		identifier_print(temp);
}