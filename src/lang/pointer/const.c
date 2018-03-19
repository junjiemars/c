#include <_lang_.h>
#include <stdio.h>


int 
main(){

	printf("----------\n");
	int v1 = 0x11223344, v2 = 0x44332211;
	const int *p1 = &v1;
	**(int**)&p1 = v2+0x1;
	printf("const int* p1@%p = 0x%x\n", p1, *p1);

	int *const p2 = &v1;
	*(int**)&p2 = &v2;
	printf("int* const p2@%p = 0x%x\n", p2, *p2);

	const int *const p3 = &v1;
	*(int**)&p3 = &v2;
	printf("const int* const p3@%p = 0x%x\n", p3, *p3);
	**(int**)&p3 = *p3+0x1;
	printf("const int* const p3@%p = 0x%x\n", p3, *p3);

	int *p41 = &v1;
	int* *p4 = &p41;
	printf("int** p4@%p = 0x%x\n", *p4, **p4);
	
	const int** p5 = &p1;
	printf("const int** p5@%p = 0x%x\n", *p5, **p5);	

	int *const *p6 = &p2;
	printf("int* const*: p6@%p = 0x0x%x\n", *p6, **p6);

	int **const p7 = &p41;
	printf("int** const p7@%p = 0x0x%x\n", *p7, **p7);

	const int *const *p8 = &p1;
	printf("const int* const* p8@%p = 0x%x\n", *p8, **p8);

	const int **const p9 = &p1;
	printf("const int** const p9@%p = 0x%x\n", *p9, **p9);

	int *const *const p0 = &p41;
	printf("int* const* const p0@%p = 0x%x\n", *p0, **p0);

}
