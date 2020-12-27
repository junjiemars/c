#include "_lang_.h"
#include <stdio.h>

char *s1[] = 
{
	"aaa", "bbb", "ccc", 0,
};

char s2[][3][4] = 
{
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

void
f1(char **args) 
{
	char x = args[1][2];
  _unused_(x);

  printf("**args\n------------\n");
  while (*args)
    {
      printf("%s,", *args);
      args++;
    }
  printf("\n\n");
}

/* illife vector */
void
f2(char *args[]) 
{
	char x = args[1][2];
	_unused_(x);
  
  printf("*args[]\n------------\n");
  while (*args)
    {
      printf("%s,", *args);
      args++;
    }
  printf("\n\n");
}

void 
g1(char (*args)[3][4]) 
{
	char x = args[1][2][3];
	_unused_(x);

  /* printf("(*args)[3][4]\n------------\n"); */
  /* while (*args) */
  /*   { */
  /*     char ss[3][4] = (char (*)[4])(*args); */
  /*     for (int i = 0; i < 3; i++) */
  /*       { */
  /*         printf("%s,", ss[i]); */
  /*       } */
  /*     args++; */
  /*   } */
  /* printf("\n"); */
}

void
g2(char args[][3][4]) 
{
	char x = args[1][2][3];
	_unused_(x);
}

void
h1(int (*i)[4]) 
{
	int x = i[1][2];
	_unused_(x);
}

void
h2(int (*i)[3][4])
{
  int x = i[0][1][2];
  _unused_(x);
}

int
main(int argc, char **argv) 
{
	_unused_(argc);
	_unused_(argv);

	f1(s1);
	f2(s1);
	g1(s2);
	g2(s2);
  h1(i1);
	h2(i2);
	
	return 0;
}
