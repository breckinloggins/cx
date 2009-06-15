#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/memory.h"
#include "symbol_table.h"

Symbol* symbol_new(const char* name)
{
	Symbol* symbol = (Symbol *)malloc(sizeof(Symbol));
	
	symbol->type = VOID;
	value_set(&symbol->value, symbol->type, NULL);
	symbol->params = -1;
	symbol->param_types = NULL;
	symbol->decl_linenum = 0;
	symbol->is_global = FALSE;
	symbol->stack_index = -1;
	
	symbol->next = NULL;
	
	if (name != NULL)
		symbol->name = strdup(name);
	else
		symbol->name = NULL;
		
	return symbol;
}

Symbol* symbol_insert(Symbol* symtab, Symbol* symbol)
{
	Symbol* sym;
	
	if (symbol == NULL)
		return NULL;
	
	sym = symbol_lookup(symtab, symbol->name);
	
	if (sym)	{
		symbol_destroy(symbol);
		return sym;
	}
	
	symbol->next = symtab->next;
	symtab->next = symbol;
	
	return symbol;
}

Symbol* symbol_lookup(Symbol* symtab, const char* name)
{
	Symbol* temp;
	
	if (symtab == NULL)
		return NULL;
		
	for (temp = symtab->next; (temp); temp = temp->next)	{
		if (!strcmp(temp->name, name))
			return temp;
	}
	
	return temp;
}

void symbol_create_params(Symbol* symbol, int quantity)
{
	symbol->params = quantity;
	if (quantity > 0)
		symbol->param_types = (Type *)malloc(sizeof(Type) * quantity);
}

bool symbol_is_function(Symbol* symbol)
{
	return (symbol->params > -1);
}

void symbol_print(Symbol* symbol)
{
	if (symbol == NULL)	{
		printf("NULL\n\n");
		return;
	}
	
	printf("Symbol: %x\n", symbol);
	printf("\tname: %s\n", symbol->name);
	printf("\ttype: %d\n", symbol->type);
	printf("\tvalue: ");
	value_print(stdout, &symbol->value, symbol->type);
	printf("\n\tdeclaration line: %d\n", symbol->decl_linenum);
	printf("\tnext: %x\n\n", symbol->next);
}

void symbol_destroy(Symbol* symbol)
{
	free(symbol->name);
	free(symbol);
}

void symbol_table_destroy(Symbol* symtab)
{
	Symbol* first;
	Symbol* to_kill;
	first = symtab->next;
	symtab->next = NULL;
	
	while (first)	{
		to_kill = first;
		first = first->next;
		symbol_destroy(to_kill);
	}
}

void symbol_table_dump(Symbol* symtab)
{
	Symbol* temp = symtab;
	
	for (temp = symtab->next; (temp); temp = temp->next)
		symbol_print(temp);
}