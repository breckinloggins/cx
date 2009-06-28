#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct String_tag	{
	char* p;
	size_t length;
} String;

String* string_new(const char* source)
{
	String* s = (String*)malloc(sizeof(String));
	s->length = strlen(source);
	s->p = strdup(source);
}

int main(int argc, char** argv)
{
	String* s = string_new("Hello, World\n");
	
	fprintf(stdout, "%s", *s);
}