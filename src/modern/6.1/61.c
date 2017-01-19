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
	int y2[][2] = { [3]={49,48,}, [1]={0xff, 0xff00}, };

	for (size_t m=0; m < sizeof(y1)/sizeof(y1[0]); ++m) {
		for (size_t n=0; n < sizeof(y1[0])/sizeof(y1[0][0]); ++n) {
			y1[m][n] = (m+1)*(n+1) + 10;
		}
	}
	_unused_(y1);

	printf("y2[][2]=");
	for (size_t m=0; m < sizeof(y2)/sizeof(y2[0]); ++m) {
		for (size_t n=0; n < sizeof(y2[0])/sizeof(y2[0][0]); ++n) {
			printf("%i,", y2[m][n]);
		}
	}	
	printf("\n");
	_unused_(y2);

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
