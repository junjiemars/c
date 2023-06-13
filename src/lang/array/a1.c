#include "_lang_.h"

/* base, row-index, col-index, col-n, width */
#define Aij(b, r, c, n, w) ((char *)(b) + (r) * (n) * (w) + (c) * (w))

static void f1 (char **);
static void f2 (char *[]);
static void f3 (char *[], size_t);
static void g1 (char (*)[3][4], size_t);
static void g2 (char[][3][4], size_t);
static void m1 (int (*)[3], int (*)[2]);

char *s1[] = {
  "aaa",
  "bbb",
  "ccc",
  0,
};

char s2[][3][4] = {
  { "a", "b", "c" },
  { "aa", "bb", "cc" },
  { "aaa", "bbb", "ccc" },
};

int a1[2][3] = {
  { 1, 2, 3 },
  { 4, 5, 6 },
};

int b1[3][2] = {
  { 7, 8 },
  { 9, 10 },
  { 11, 12 },
};

int
main (void)
{
  f1 (s1);
  f2 (s1);
  f3 (s1, sizeof (s1) / sizeof (*s1));
  g1 (s2, sizeof (s2) / sizeof (*s2));
  g2 (s2, sizeof (s2) / sizeof (*s2));
  m1 (a1, b1);

  return 0;
}

void
f1 (char **args)
{
  printf ("char **args\n------------\n");

  while (*args)
    {
      printf ("%s,", *args);
      args++;
    }

  printf ("\n\n");
}

void
f2 (char *args[])
{
  printf ("char *args[]\n------------\n");

  for (size_t i = 0; args[i]; i++)
    {
      for (size_t j = 0; args[i][j]; j++)
        {
          putchar (args[i][j]);
        }
      putchar (',');
    }

  printf ("\n\n");
}

void
f3 (char *args[], size_t n)
{
  printf ("char *args[]\n------------\n");

  for (size_t i = 0; i < (n - 1); i++)
    {
      printf ("%s,", args[i]);
    }

  printf ("\n\n");
}

void
g1 (char (*args)[3][4], size_t n)
{
  printf ("char (*args)[3][4]\n------------\n");

  for (size_t i = 0; i < n; i++)
    {
      for (int j = 0; j < 3; j++)
        {
          printf ("%4s,", args[i][j]);
        }
      printf ("\n");
    }

  printf ("\n");
}

void
g2 (char args[][3][4], size_t n)
{
  printf ("char args[][3][4]\n------------\n");

  for (size_t i = 0; i < n; i++)
    {
      for (int j = 0; j < 3; j++)
        {
          printf ("%4s, ", args[i][j]);
        }
      printf ("\n");
    }

  printf ("\n");
}

void
m1 (int a[2][3], int b[3][2])
{
  int c[2][2];

  printf ("A[2,3] x B[3,2] = M\n------------\n");

  for (int i = 0; i < 2; i++)
    {
      for (int j = 0; j < 2; j++)
        {
          int p = 0;

          for (int k = 0; k < 3; k++)
            {
              p += a[i][k] * b[k][j];
            }

          c[i][j] = p;
        }
    }

  for (int i = 0; i < 2; i++)
    {
      for (int j = 0; j < 2; j++)
        {
          printf ("%4d ", c[i][j]);
        }
      putchar ('\n');
    }
}
