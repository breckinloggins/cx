#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/memory.h"
#include "base.h"

Type type_get_from_lexeme(const char* lexeme)
{
	if (!strcasecmp(lexeme, "Integer"))
		return INTEGER;
	else if (!strcasecmp(lexeme, "Boolean"))
		return BOOLEAN;
	else if (!strcasecmp(lexeme, "Char"))
		return VOID;
}

char* type_get_lexeme(Type type)
{
	switch (type)	{
		case VOID:
			return "void";
		case INTEGER:
			return "Integer";
		case BOOLEAN:
			return "Boolean";
		case CHAR:
			return "Char";
		case ERROR:
			return "Error";
		default:
			return "";
	}
}

void value_print(FILE* file, Value* value, Type type)
{
	if (type == INTEGER)	{
		fprintf(file, "%d", value->integer);
	} else if (type == BOOLEAN)	{
		fprintf(file, "%s", value->boolean? "true" : "false");
	} else if (type == CHAR)	{
		fprintf(file, "'%c'", value->character);
	}
}

void value_get(Value* value, Type type, void* val)
{
	if (value == NULL)	{
		fprintf(stderr, "%s: value_get: value == NULL\n", __FILE__);
		exit(1);
	}
	
	if (type == INTEGER)	{
		*((int *) val) = value->integer;
	} else if (type == BOOLEAN)	{
		*((bool *) val) = value->boolean;
	} else if (type == CHAR)	{
		*((char *) val) = value->character;
	} else {
		fprintf(stderr, "%s: value_get: unknown type\n", __FILE__);
		exit(1);
	}
}

void value_set(Value* value, Type type, void* val)
{
	if (value == NULL)	{
		fprintf(stderr, "%s: value_set: value == NULL\n", __FILE__);
		exit(1);
	}
	
	if (type == VOID || val == NULL)	{
		value->integer = 0;
	} else if (type == INTEGER)	{
		value->integer = *((int *)val);
	} else if (type == BOOLEAN)	{
		value->boolean = *((bool *)val);
	} else if (type == CHAR)	{
		value->character = *((char *)val);
	} else	{
		fprintf(stderr, "%s: value_set: unknown type\n", __FILE__);
		exit(1);
	}
}

void value_set_from_int(Value* value, int val)
{
	value_set(value, INTEGER, VOID(val));
}

void value_set_from_bool(Value* value, bool val)
{
	value_set(value, BOOLEAN, VOID(val));
}

void value_set_from_char(Value* value, char val)
{
	value_set(value, CHAR, VOID(val));
}
