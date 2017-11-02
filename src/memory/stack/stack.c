#include "stack.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void 
stack_new(stack *s, size_t width, void (*free_fn)(void *)) {
	assert(0 < width);

	s->width = width;
	s->top = 0;
	s->capacity = STACK_INIT_CAPACITY;
	s->elements = malloc(width * STACK_INIT_CAPACITY);
	s->free_fn = free_fn;

	assert(0 != s->elements);
}

void
stack_dispose(stack *s) {
	assert( 0 != s);

	if (s->free_fn) {
		for (size_t i=0; i < s->top; i++) {
			s->free_fn((char*)s->elements + i * s->width);
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
		s->elements = realloc(s->elements, s->capacity * s->width);
		assert(0 != s->elements);
	}
	
	dst = (char*)s->elements + s->top * s->width;
	memcpy(dst, e, s->width);
	s->top++;
}

void
stack_pop(stack *s, void *e) {
	const void *src;
	assert(!stack_empty(s));

	s->top--;
	src = (const char*)s->elements + s->top * s->width;
	memcpy(e, src, s->width);
}
