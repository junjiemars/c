#include <modern.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	_unused_(argc);
	_unused_(argv);

	/* i can't be negative */
	for (size_t i=3; i <= 3; --i) {
		printf("i=%zu\n", i);
	}

	int count = 1;
	switch (count) {
		default: puts("+++"); /* wherever */
		case 2: puts("++");
		case 1: puts("+");
		case 0: ;
	}

	return 0;
}
