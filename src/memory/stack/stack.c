#include "stack.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void 
stack_new(stack *s, size_t size, void (*free_fn)(void *)) {
	assert(0 < size);

	s->size = size;
	s->top = 0;
	s->capacity = STACK_INIT_CAPACITY;
	s->elements = malloc(size * STACK_INIT_CAPACITY);
	s->free_fn = free_fn;

	assert(0 != s->elements);
}

void
stack_dispose(stack *s) {
	assert( 0 != s);

	if (s->free_fn) {
		for (size_t i=0; i < s->top; i++) {
			s->free_fn((char*)s->elements + i * s->size);
		}
	}
	free(s->elements);
}

int
stack_empty(const stack *s) {
	return 0 == s->top;
}

void
stack_push(stack *s, const void *e) {
	void *dst;

	if (s->capacity == s->top) {
		s->capacity *= 2;
		s->elements = realloc(s->elements, s->capacity * s->size);
		assert(0 != s->elements);
	}
	
	dst = (char*)s->elements + s->top * s->size;
	memcpy(dst, e, s->size);
	s->top++;
}

void
stack_pop(stack *s, void *e) {
	const void *src;
	assert(!stack_empty(s));

	s->top--;
	src = (const char*)s->elements + s->top * s->size;
	memcpy(e, src, s->size);
}
