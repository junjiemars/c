#include "_lang_.h"
#include <stdio.h>


size_t 
sqr(size_t n) {
	return (n*n);
}

size_t
sum(size_t (*fn)(size_t), size_t* lst, size_t n) {
	size_t s = 0;
	for (size_t i=0; i<n; ++i) {
		s += (*fn)(lst[i]);
	}	
	return s;
}


int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);
  
	printf("----------\n");
	size_t a1[10] = { 0,1,2,3,4,5, };
	printf("sum(|sqr|)=%zu\n", sum(&sqr, a1, sizeof(a1)/sizeof(a1[0])));

}
