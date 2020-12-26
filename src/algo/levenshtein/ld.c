#include <_algo_.h>

#define Mij(M, i, j, n) ((M) + (i) + ((j) * ((n)+1)))

inline int min_ld(int a, int b, int c);
typedef void (*dump_fn)(int *M, const char *s, const char *t, int n, int m);

int ld1(const char *s, const char *t, dump_fn dump);
void dump_Mij(int *M, const char *s, const char *t, int n, int m);
void test_ld1(const char *s, const char *t);


int
ld1(const char *s, const char *t, dump_fn dump)
{
  int n, m;
  int si, tj;
  int cost;
  int *d;
  int above, left, diag, x;

  n = (int)strlen(s);
  m = (int)strlen(t);

  if (n == 0)
    {
      return m;
    }
  if (m == 0)
    {
      return n;
    }

  d = malloc(sizeof(*d) * (n+1) * (m+1));

  for (int i = 0; i <= n; i++)
    {
      *Mij(d, i, 0, n) = i;
    }

  for (int j = 0; j <= m; j++)
    {
      *Mij(d, 0, j, n) = j;
    }

  for (int i = 1; i <= n; i++)
    {
      si = s[i-1];
      
      for (int j = 1; j <= m; j++)
        {
          tj = t[j-1];

          if (si == tj)
            {
              cost = 0;
            }
          else
            {
              cost = 1;
            }

          above = *Mij(d, i, j-1, n) + 1;
          left = *Mij(d, i-1, j, n) + 1;
          diag = *Mij(d, i-1, j-1, n) + cost;
          
          x = min_ld(above, left, diag);
          *Mij(d, i, j, n) = x;
        }
    }

  x = *Mij(d, n, m, n);
  if (dump)
    {
      dump(d, s, t, n, m);
    }
  free(d);
  
  return x;
}

int
min_ld(int a, int b, int c)
{
  int m = a;
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

void
test_ld1(const char *s, const char *t)
{
  printf("s=%s, t=%s\n", s, t);
  printf("ld=%04i\n", ld1(s, t, dump_Mij));
}

int
main(int argc, char **argv)
{
  if (argc < 3)
    {
      printf("please, input source and target\n");
      return 0;
    }

  test_ld1(argv[1], argv[2]);

  return 0;
}
