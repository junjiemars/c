#include <nm_auto_config.h>
#include <nm_auto_headers.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char* argv[]) {
	int n = 9;
	
	if (argc > 1) n = atoi(argv[1]);

	int x, y, z;

	while (1) {
		x = 0;
		y = 1;
		
		do {
			printf("%i ", x);

			z = x + y;
			x = y;
			y = z;	
		} while (x < n);

		putchar('\n');
		break;
	}
	
}

