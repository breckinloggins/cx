#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "base.h"

typedef struct Symbol_tag	{
	char* name;
	Type type;
	Value value;
	int decl_linenum;
	
	// For functions
	int params;
	Type* param_types;
	
	bool is_global;
	int stack_index;
	struct Symbol_tag* next;
} Symbol;

static Symbol* global_symble_table;

Symbol* symbol_new(const char* name);
Symbol* symbol_lookup(Symbol* symtab, const char* name);
Symbol* symbol_insert(Symbol* symtab, Symbol* symbol);
void symbol_destroy(Symbol* symbol);

void symbol_create_params(Symbol* symbol, int quantity);
bool symbol_is_function(Symbol* symbol);
void symbol_print(Symbol* symbol);

void symbol_table_destroy(Symbol* symtab);
void symbol_table_dump(Symbol* symtab);

#endif // SYMBOL_TABLE_H