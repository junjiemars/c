#include "stack.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>


void 
stack_new(stack *s, size_t elem_size, void (*free_fn)(void *)) {
	assert(0 < elem_size);

	s->elem_size = elem_size;
	s->log_length = 0;
	s->alloc_length = STACK_INIT_SIZE;
	s->elems = malloc(elem_size * STACK_INIT_SIZE);
	s->free_fn = free_fn;

	assert(0 != s->elems);
}

void
stack_dispose(stack *s) {
	assert( 0 != s);

	if (s->free_fn) {
		for (size_t i=0; i < s->log_length; i++) {
			s->free_fn((char*)s->elems + i * s->elem_size);
		}
	}
	free(s->elems);
}

int
stack_empty(const stack *s) {
	return 0 == s->log_length;
}

void
stack_push(stack *s, const void *elem_addr) {
	void *dst;

	if (s->alloc_length == s->log_length) {
		s->alloc_length *= 2;
		s->elems = realloc(s->elems, s->alloc_length * s->elem_size);
		assert(0 != s->elems);
	}
	
	dst = (char*)s->elems + s->log_length * s->elem_size;
	memcpy(dst, elem_addr, s->elem_size);
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
