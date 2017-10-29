#include "rotate.h"
#include <string.h>
#include <assert.h>

void
rotate(void *front, void *middle, void *end) {
	assert(0 != front && 0 != middle && 0 != end);
	assert(front <= middle && middle < end);

	size_t front_size = (char*)middle - (char*)front;	
	size_t middle_size = (char*)end - (char*)middle;

	char buffer[front_size + 1];	
	memcpy(buffer, front, front_size);
	memmove(front, middle, middle_size);
	memcpy((char*)front + middle_size, buffer, front_size);	 
}
