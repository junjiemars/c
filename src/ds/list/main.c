#include <list.h>
#include <stdlib.h>

#define _unused_(x) ((void)(x))


int
main(int argc, const char *argv[]) {
	list *lst = list_init(malloc(sizeof(list)));	

	list_free(lst, free); 

	free(lst);
}
