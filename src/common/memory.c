/*
 *	Memory management helpers
 */

#include <stdlib.h>
#include <stdio.h>

#include "memory.h"

#undef malloc
#undef calloc
#undef realloc
#undef free

typedef struct memblock_tag	{
	void* p;						// The actual memory
	size_t size;					// The size of the requested block
	const char* file;				// The name of the file where the memory was allocated
	unsigned int line;				// The actual line of code that allocated the memory
	
	struct memblock_tag* next;	// Pointer to the next block
	} memblock;

static memblock* blocks = NULL;	// Our local collection of blocks

static void memblock_new(void* p, size_t size, const char* file, const unsigned int line)
{
	memblock* m = (memblock*)malloc(sizeof(memblock));
	if (!m)	{
		fprintf(stderr, "Fatal: could not allocate memblock for allocation at %s, line %d\n", file, line);
		exit(1);
	}
	
	m->p = p;
	m->size = size;
	m->file = file;
	m->line = line;
	m->next = blocks;
	
	blocks = m;
}

void* fmalloc(size_t size, const char* file, const unsigned int line)
{
//	fprintf(stderr, "I can haz malloc(%d) at %s, line %d??\n", size, file, line);
	void* p = malloc(size);
	
	if (!p)	{
		fprintf(stderr, "Fatal: could not allocate %d bytes at %s, line %d\n", size, file, line);
		exit(1);
	}
	
	// Keep track of this allocation
	memblock_new(p, size, file, line);
	
	return p;
}

void* fcalloc(size_t count, size_t size, const char* file, const unsigned int line)
{
	void* p = calloc(count, size);
	
	if (!p)	{
		fprintf(stderr, "Fatal: could not allocate %d chunks of %d bytes at %s, line %d\n", count, size, file, line);
		exit(1);
	}
	
	// Keep track of this allocation
	memblock_new(p, count*size, file, line);
	
	return p;
}

void* frealloc(void* ptr, size_t size, const char* file, const unsigned int line)
{
	void *np = realloc(ptr, size);
	
	if (!np)	{
		fprintf(stderr, "Fatal: could not reallocate %d bytes at %s, line %d\n", size, file, line);
		exit(1);
	}
	
	memblock* m = blocks;
	while (m)	{
		if (m->p == ptr)	{
			// This was the old block
			m->size = size;
			m->p = np;
			
			//fprintf(stderr, "Reallocated block\n");
			return np;
		}
	}
	
	// This should NEVER happen
	fprintf(stderr, "Fatal: attempted to locate previous block for realloc in %s, line %d, but failed\n", file, line);
	exit(1);
}

void ffree(void* ptr, const char* file, const unsigned int line)
{
	free(ptr);
	
	memblock* prev = NULL;
	memblock* m = blocks;
	while (m)	{
		if (m->p == ptr)	{
			// Discard this block
			if (!prev)	{
				// This is the first, replace the head
				// blocks pointer
				blocks = m->next;
			}
			else	{
				// Break the link in the chain
				prev->next = m->next;
			}
			
			free(m);
			return;
		}
		
		prev = m;
		m = m->next;
	}
}

void checkmem()
{
	if (!blocks)	{
		// Congratulations, you have no memory leaks!
		return;
	}
	
	fprintf(stderr, "\nYOU HAVE MEMORY LEAKS:\n");
	memblock* m = blocks;
	while (m)	{
		fprintf(stderr, "\t%d bytes at 0x%x, allocated in %s at line %d\n", m->size, m->p, m->file, m->line);
		m = m->next;
	}
}

