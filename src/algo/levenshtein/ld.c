#include "_algo_.h"

/*
 * https://people.cs.pitt.edu/~kirk/cs1501/Pruhs/Spring2006/assignments/editdistance/Levenshtein%20Distance.htm
 *
 * http://www-igm.univ-mlv.fr/~lecroq/seqcomp/node2.html
 *
 */

#define Mij(M, i, j, n) ((M) + (i) + ((j) * ((n)+1)))

typedef void (*dump_fn)(int*, const char*, const char*, int, int);


int   ld1(const char*, const char*, dump_fn);
void  dump_Mij(int*, const char*, const char*, int, int);

static int   min_ld(int, int, int);
static void  test_ld1(const char*, const char*);


int
main(int argc, char **argv)
{
  if (argc < 3)
    {
      fprintf(stderr, "usage: <source> <target>\n");
      return 0;
    }

  test_ld1(argv[1], argv[2]);

  return 0;
}

void
test_ld1(const char *s, const char *t)
{
  printf("s=%s, t=%s\n", s, t);
  printf("ld=%04i\n", ld1(s, t, dump_Mij));
}


int
ld1(const char *s, const char *t, dump_fn dump)
{
  int  *aa;
  int   n, m;
  int   si, tj;
  int   a, b, d, x;

  n = (int) strlen(s);
  m = (int) strlen(t);

  if (n == 0)
    {
      return m;
    }
  if (m == 0)
    {
      return n;
    }

  aa = malloc(sizeof(*aa) * (n+1) * (m+1));

  for (int i = 0; i <= n; i++)
    {
      *Mij(aa, i, 0, n) = i;
    }

  for (int j = 0; j <= m; j++)
    {
      *Mij(aa, 0, j, n) = j;
    }

  for (int i = 1; i <= n; i++)
    {
      si = s[i-1];

      for (int j = 1; j <= m; j++)
        {
          tj = t[j-1];

          a  =  *Mij(aa, i-1, j, n) + 1;
          b  =  *Mij(aa, i, j-1, n) + 1;
          d  =  *Mij(aa, i-1, j-1, n) + (si == tj ? 0 : 1);

          x  =  min_ld(a, b, d);

          *Mij(aa, i, j, n) = x;
        }
    }

  x = *Mij(aa, n, m, n);

  if (dump)
    {
      dump(aa, s, t, n, m);
    }
  free(aa);

  return x;
}

inline int
min_ld(int a, int b, int c)
{
  int  m  =  a;

  if (b < m)
    {
      m = b;
    }
  if (c < m)
    {
      m = c;
    }

  return m;
}

void
dump_Mij(int *M, const char *s, const char *t, int n, int m)
{
  printf("         ");
  for (int i = 0; i < n; i++) {
    printf("%4c ", s[i]);
  }
  printf("\n");

  for (int j = 0; j <= m; j++)
    {
      if (j == 0)
        {
          printf("     ");
        }
      if (j == 1)
        {
          printf("%4c ", t[j-1]);
        }
      if (j > 1)
        {
          printf("%4c ", t[j-1]);
        }

      for (int i = 0; i <= n; i++)
        {
          printf("%04i ", *Mij(M, i, j, n));
        }

      printf("\n");
    }
}
