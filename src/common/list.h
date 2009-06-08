#ifndef LIST_H
#define LIST_H

/*
// TODO: This is an idea for generic lists in C.  May want to give this a shot to make our lives
//		easier
#define	LIST(T)				list_t_##T
#define DECLARE_LIST(T)		typedef struct list_e_##T_tag	{	\
								##T value;						\
								int owned;						\
								struct list_e_##T_tag* prev;	\
								struct list_e_##T_tag* next;	\
							} LIST(T)
*/

/* Represents an element of a list of zero or more objects.  The list is doubly-linked to facilitate navigation, 
 * but could be converted to a singly-linked list to save space, if you're in to that kind of thing.
 */
typedef struct list_e_tag	{
	void* p;						// Pointer to the object itself
	int owned;						// Set to 1 if the list element owns the object
	struct list_e_tag* prev;		// Pointer to the previous element in the list
	struct list_e_tag* next;		// Pointer to the next element in the list
} list_e;

/* list methods implemented in list.c */
list_e* list_e_new(void* p, int owned);					// Creates a new node but does not insert it anywhere
void list_e_insert_before(list_e* next, list_e* e);		// Inserts the element before the given element
void list_e_insert_after(list_e* prev, list_e* e);		// Inserts the element after the given element
void list_e_remove(list_e* e);							// Removes the element as a member of the list, does
														// 	NOT free the element!

list_e* list_first(list_e* e);							// Given any element of a node list, returns the first
														// 	element (worst case O(n) search)
list_e* list_last(list_e* e);							// Given any element of a node list, returns the last
														//	element (worst case O(n) search)
void list_free_forward(list_e* first);					// Frees all memory for the first node and every node
														// 	after it.  Essentially "chops off" the end of a
														//	list
#endif