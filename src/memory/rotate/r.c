#include <_memory_.h>
#include "rotate.h"
#include <stdio.h>


int
main(void) {
	char ss[] = "ABCDEFGH";
	int p = 3;

	printf("\nROTATE %s[%i]\n", ss, p);
	printf("----------\n");
	rotate(ss, &ss[p], &ss[_nof_(ss)-1]);
	printf("%s\n", ss);

	p = 4;
	printf("\nROTATE %s[%i]\n", ss, p);
	printf("----------\n");
	rotate(ss, &ss[p], &ss[_nof_(ss)-1]);
	printf("%s\n", ss);

}
