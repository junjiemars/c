#include <modern.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	_unused_(argc);
	_unused_(argv);

	/* FLA: fixed length array */
	int x1[] = { [3]=49, [1]=12, };
	int x2[] = { 2, 3, };	
	printf("length-of({ [3]=49, [1]=12, })=%lu\n", sizeof(x1)/sizeof(x1[0]));
	printf("length-of({ 2, 3, })=%lu\n", sizeof(x2)/sizeof(x2[0]));

	/* multi-dementional array */
	int y1[2][3];
	int y2[][2] = { [2]={49,48,}, };
	for (size_t m=0,n=0; m<2; ++m,++n) {
		y1[m][n] = m*n + 10;
	}
	printf("y2[][2]=");
	for (size_t m=0,n=0; m<sizeof(y2)/sizeof(y2[0][0]); ++m,++n) {
		printf("%i,", y2[m][n]);
	}	
	printf("\n");

	/* string is a 0-terminated array of char */
	/* string intro see modern/str */
	char s1[] = "abcd";
	char s2[] = { "abcd" };
	char s3[] = { 'a', 'b', 'c', 'd', 0, };	
	printf("s1[](\"abcd\")=%s\n", s1);
	printf("s2[]({\"abcd\"})=%s\n", s2);
	printf("s2[]({ 'a', 'b', 'c', 'd', 0, })=%s\n", s3);

	return 0;
}
