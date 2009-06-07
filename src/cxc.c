/*
 *	Main Cx Compiler executable
 */

#include <stdio.h>
#include <string.h>

#include "common/memory.h"
#include "common/list.h"		// TEMP


	list_e* push_string(const char* string, list_e* list)
	{
		char *s = (char*)malloc(strlen(string) + 1);
		strcpy(s, string);

		list_e* e = list_e_new(s, 1);
		if (list)
			list_e_insert_after(list_last(list), e);

		return e;
	}

int main(int argc, char** argv)
{
	atexit(checkmem);
	
	list_e* strings = push_string("This is string number 1", 0);
	push_string("And this is number 2 (heh)", strings);
	push_string("Well, what do you know, it's the third one, how nice", strings);
	push_string("And finally, the fourth!", strings);
	
	list_e* s;
	for (s = strings; (s); s = s->next)
		printf("%s\n", (char*)s->p);
	
	list_free_forward(strings);
	return 0;
}


