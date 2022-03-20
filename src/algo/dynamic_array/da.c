#include <_algo_.h>
#include <setjmp.h>


static void add_element(int);
static void test_add_element(void);

char *dynamic;
int current_element = 0;
int total_elements = 4;
jmp_buf env;


int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	test_add_element();
	free(dynamic);

	return 0;
}


void
add_element(int c) {
	if (0 == current_element) {
		dynamic = malloc(sizeof(char) * total_elements);
	}
	if (current_element == (total_elements - 1)) {
		total_elements *= 2;
		dynamic = realloc(dynamic, total_elements);
	}
	dynamic[current_element++] = (char)c;
}

void
test_add_element(void) {
	int size = 10;
	for (int i=0; i<size; i++) {
		add_element('a' + i);
	}
	assert(current_element == size);
	assert(total_elements == 16);
}
