#include "stack.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define ALLOCATION_SIZE 4u

void 
stack_new(stack *s, size_t elem_size) {
	assert(0 < elem_size);

	s->elem_size = elem_size;
	s->log_length = 0;
	s->alloc_length = ALLOCATION_SIZE;
	s->elems = malloc(elem_size * ALLOCATION_SIZE);

	assert(0 != s->elems);
}

void
stack_dispose(stack *s) {
	free(s->elems);
}

int
stack_empty(const stack *s) {
	return 0 == s->log_length;
}

void
stack_push(stack *s, const void *elem_addr) {
	void *dest;
	if (s->alloc_length == s->log_length) {
		s->alloc_length *= 2;
		s->elems = realloc(s->elems, s->alloc_length * s->elem_size);
		assert(0 != s->elems);
	}
	
	dest = (char*)s->elems + s->log_length * s->elem_size;
	memcpy(dest, elem_addr, s->elem_size);
	s->log_length++;
}

void
stack_pop(stack *s, void *elem_addr) {
	const void *src;
	assert(!stack_empty(s));

	s->log_length--;
	src = (const char*)s->elems + s->log_length * s->elem_size;
	memcpy(elem_addr, src, s->elem_size);
}
