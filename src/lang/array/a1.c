#include "_lang_.h"

#if (MSVC)
#  pragma warning(disable: 4456)
#elif (GCC)
#  pragma GCC diagnostic ignored "-Wunused-variable"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#elif (CLANG)
#  pragma clang diagnostic ignored "-Wunused-variable"
#  pragma clang diagnostic ignored "-Wunused-parameter"
/* #  pragma clang diagnostic ignored "-Wunused-but-set-variable" */
#endif


/* base, row-index, col-index, col-n, width */
#define Aij(b, r, c, n, w) ((char*) (b) + (r)*(n)*(w) + (c)*(w))

static void f1(char**);
static void f2(char*[]);
static void g1(char (*)[3][4], int);
static void g2(char [][3][4], int);
static void h1(int (*)[4], int);
static void h2(int (*)[3][4]);

char *s1[] =
  {
    "aaa", "bbb", "ccc", 0,
  };

char s2[][3][4] =
  {
    { "a", "b", "c" },
    { "aa", "bb", "cc" },
    { "aaa", "bbb", "ccc" },
  };

int i1[][4] =
  {
    { 0x11, 0x22, 0x33, 0x44, },
    { 0x44, 0x33, 0x22, 0x11, },
  };

int i2[][3][4] =
  {
    { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, },
    { {21,22,23,24}, {25,26,27,28}, {29,30,31,32}, },
  };


int
main(void)
{
	f1(s1);
	f2(s1);
	g1(s2, 3);
	g2(s2, 3);
  h1(i1, sizeof(i1)/sizeof(i1[0]));
	h2(i2);

	return 0;
}

void
f1(char **args)
{
	char  x  =  args[1][2];

  printf("char **args\n------------\n");
  while (*args)
    {
      printf("%s,", *args);
      args++;
    }
  printf("\n\n");
}

void
f2(char *args[])
{
  char x = args[1][2];

  printf("char *args[]\n------------\n");
  while (*args)
    {
      printf("%s,", *args);
      args++;
    }
  printf("\n\n");
}

void
g1(char (*args)[3][4], int n)
{
  char x = args[1][2][3];

  printf("char (*args)[3][4]\n------------\n");
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < 3; j++)
        {
          printf("%4s,", args[i][j]);
        }
      printf("\n");
    }
  printf("\n");
}

void
g2(char args[][3][4], int n)
{
  char x = args[1][2][3];

  printf("char args[][3][4]\n------------\n");
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < 3; j++)
        {
          char *ss = (char*)&args[0] + i*3*4 + j*4;
          printf("%4s, ", ss);
        }
      printf("\n");
    }
  printf("\n");
}

void
h1(int (*i)[4], int n)
{
  int x = i[1][2];

  printf("int (*i)[4]\n------------\n");
  for (int j = 0; j < n; j++)
    {
      for (int k = 0; k < 4; k++)
        {
          printf("0x%02x, ", *(int*)Aij(i, j, k, 4, sizeof(int)));
        }
      printf("\n");
    }
  printf("\n");
}

void
h2(int (*i)[3][4])
{
  int x = i[0][1][2];
}
