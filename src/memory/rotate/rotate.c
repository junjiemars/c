#include "rotate.h"
#include "nore.h"
#include <string.h>
#include <assert.h>

#if ! defined( NM_HAVE_VLA )
#include <stdlib.h>
#endif

void
rotate(void *front, void *middle, void *end) {
	assert(0 != front && 0 != middle && 0 != end);
	assert(front <= middle && middle < end);

	size_t front_size = (char*)middle - (char*)front;	
	size_t middle_size = (char*)end - (char*)middle;

#if ! defined( NM_HAVE_VLA )
	char *buffer = malloc(front_size);
#else
	char buffer[front_size];		
#endif

	memcpy(buffer, front, front_size);
	memmove(front, middle, middle_size);
	memcpy((char*)front + middle_size, buffer, front_size);	 

#if ! defined( NM_HAVE_VLA )
	free(buffer);
#endif
}
