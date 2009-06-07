#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

/* 
 * Memory Handling Utilities
 */

#define malloc(s)		fmalloc((s), __FILE__, __LINE__)
#define calloc(c, s)	fcalloc((c), (s), __FILE__, __LINE__)
#define realloc(p, s)	frealloc((p), (s), __FILE__, __LINE__)	
#define free(p)			ffree((p), __FILE__, __LINE__)

void* fmalloc(size_t size, const char* file, const unsigned int line);
void* fcalloc(size_t count, size_t size, const char* file, const unsigned int line);
void* frealloc(void* ptr, size_t size, const char* file, const unsigned int line);
void ffree(void* ptr, const char* file, const unsigned int line);

void checkmem();

#endif