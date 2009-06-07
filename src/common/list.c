/* 
 * Implementation of the list structure explained in list.h
 */

#include <stdlib.h>

#include "memory.h"
#include "list.h"

list_e* list_e_new(void* p, int owned)
{
	list_e* e = (list_e*)malloc(sizeof(list_e));
	
	e->prev = NULL;
	e->next = NULL;
	e->p = p;
	e->owned = owned;
	
	return e;
}
			
void list_e_insert_before(list_e* next, list_e* e)
{
	// We may be given an entire "chunk" of a list, and we want to make sure to 
	// insert the whole chunk, not just the element we're given
	list_e* first = list_first(e);
	list_e* last = list_last(e);
	
	// Splice it in
	last->next = next;
	first->prev = next->prev;
	next->prev = last;
}	

void list_e_insert_after(list_e* prev, list_e* e)
{
	// We may be given an entire "chunk" of a list, and we want to make sure to 
	// insert the whole chunk, not just the element we're given
	list_e* first = list_first(e);
	list_e* last = list_last(e);
	
	// Splice it in
	last->next = prev->next;
	first->prev = prev;
	prev->next = first;
}	

void list_e_remove(list_e* e)
{
	// Just remove this specific element and then join together the two ends
	// to get rid of the "hole"
	
	if (e->prev)
		e->prev->next = e->next;
	
	if (e->next)
		e->next->prev = e->prev;
	
	// Orphan the element	
	e->next = NULL;
	e->prev = NULL;
}							

list_e* list_first(list_e* e)
{
	list_e* first = NULL;
	while (e)	{
		first = e;
		
		e = e->prev;
	}
	
	return first;
}								

list_e* list_last(list_e* e)
{
	list_e* last = NULL;
	while (e)	{
		last = e;
		
		e = e->next;
	}
	
	return last;
}								

void list_free_forward(list_e* first)
{
	if (!first) return;
	
	list_free_forward(first->next);
	
	if (first->owned)
		free(first->p);
	
	free(first);
}