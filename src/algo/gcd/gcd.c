#include <_algo_.h>
#include <stdio.h>
#include <stdlib.h>

int ecluid(int a, int b);
int ecluid_tr(int a, int b);

int
ecluid(int a, int b)
{
	while (b)
    {
      int m = a % b;
      a = b;
      b = m;
    }
	return a;
}

int
ecluid_tr(int a, int b)
{
	if (0 == b)
    {
      return a;
    } 
	return ecluid_tr(b, a % b);
}

int
main(int argc, char **argv)
{
	if (argc < 3)
    {
      printf("ecluid(a, b)\n");
      return 1;
    }
	
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);

	printf("gcd: ecluid(%i, %i) = %i\n", a, b, ecluid(a, b));
	printf("gcd: ecluid_tr(%i, %i) = %i\n", a, b, ecluid_tr(a, b));
	
	return 0;
}
