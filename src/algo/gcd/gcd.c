#include "_algo_.h"

int  ecluid(int a, int b);
int  ecluid_tr(int a, int b);


int
main(int argc, char **argv)
{
	if (argc < 3)
    {
      fprintf(stderr, "ecluid(a, b)\n");
      return 1;
    }

	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
  int c;

  c = ecluid(a, b);
	printf("gcd: ecluid(%i, %i) = %i\n", a, b, c);

  c = ecluid_tr(a, b);
	printf("gcd: ecluid_tr(%i, %i) = %i\n", a, b, c);

	return 0;
}


int
ecluid(int a, int b)
{
	while (b)
    {
      a = b;
      b = a % b;
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
