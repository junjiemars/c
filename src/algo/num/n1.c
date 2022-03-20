#include <_algo_.h>

#if MSVC
#  pragma warning(disable : 4996)
#endif


static int max_sub(int, int, int*, int, int);

int
main(int argc, char **argv)
{
  if (argc < 3)
    {
      printf("input the positive integer and the length of it's subsequence\n");
      return 0;
    }
  int n, m, acc;
  int seq[16];

  sscanf(argv[1], "%i", &n);
  sscanf(argv[2], "%i", &m);

  acc = max_sub(n, m, &seq[0], 0, 0);

  printf("max_sub(%i, %i) = %i\n", n, m, acc);
  return 0;
}


int
max_sub(int n, int m, int *seq, int seqi, int acc)
{
  if (n == 0 && m == 0)
    {
      return acc;
    }
  if (n > 0)
    {
      seq[seqi++] = n % 10;
      qsort(seq, seqi, sizeof(*seq), cmp_int);
      return max_sub(n / 10, m, seq, seqi, acc);
    }
  if (m > 0 && seqi > 0)
    {
      --seqi;
      return max_sub(n, m - 1, seq, seqi, acc * 10 + seq[seqi]);
    }
  return -1;
}
