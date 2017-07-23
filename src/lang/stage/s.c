#include <_lang_.h>
#include <stdio.h>

int g_x1 = 0x11223344;
int g_x2;

int 
main(int argc, char *argv[]) {
  _unused_(argc);
  _unused_(argv);

	static int s_x3 = 0x44002211;
	int i = 1;
	int a[] = { 1, 2, 3 };
	a[i] = (i + 4) * (2 + 6);
	g_x2 = a[i+1];
	
	printf("Hello, %s: %d\n", "stage", 
		a[i] + g_x1 + g_x2 + s_x3);
	return 0;
}
