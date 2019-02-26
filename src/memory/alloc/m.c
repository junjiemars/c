#include <_memory_.h>
#include <stdlib.h>


typedef struct node_s {
	int val;
	struct node_s* next;
} node_s;


int* 
cast(const size_t length) {
	int *x = (int*)malloc(sizeof(int) * length);
	return x;
}

int*
non_cast(const size_t length) {
	int *x = malloc(length * sizeof *x);
	return x;
}

int*
better(const short length) {
	int *x = malloc(sizeof *x * length);
	return x;
}
	

int
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);
	
	int* int_ptr = cast(10);
	int_ptr[9] = 0x1122;
	free(int_ptr);

	int_ptr = non_cast(10);
	int_ptr[9] = 0x2211;
	free(int_ptr);

	int_ptr = better(10);
	int_ptr[9] = 0x2211;
	free(int_ptr);

	node_s *x = malloc(sizeof(node_s));
	node_s *y = malloc(sizeof(node_s));
	node_s *z = malloc(sizeof(node_s));

	x->val = 1;
	y->val = 2;
	y->val = 3;

	x->next = y;
	y->next = z;
	z->next = x;

	free(x);
	free(y);
	free(z);

	return 0;
}
