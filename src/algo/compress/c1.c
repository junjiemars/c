#include <_algo_.h>

#if (MSVC)
#  pragma warning(disable : 4996)
#endif

char *compress1(char const *ss, int len, char *ds);
void test(char const *ss);


int
main(int argc, char **argv)
{

  if (argc < 2)
    {
      printf("please, input source string!\n");
      return 0;
    }

  test(argv[1]);

  return 0;
}


char*
compress1(char const *ss, int len, char *ds)
{
  int  i   =  0;
  int  di  =  0;

  while (i < len)
    {
      int j = i;
      while (i < len && ss[i] == ss[i+1])
        {
          ++i;
        }
      int n = sprintf(&ds[di], "%c%i", ss[j], (i-j)+1);
      if (n < 0)
        {
          perror(NULL);
          return NULL;
        }
      di += n;

      i++;
    }
  ds[di] = 0;

  return ds;
}

void
test(char const *ss)
{
  char  *ds1;
  int    len  =  (int) strlen(ss);

  ds1 = malloc(sizeof(*ds1) * len * 2 + 1);
  compress1(ss, len, ds1);

  printf("compress:\n------------\n");
  printf("src=%s\ndst=%s\n", ss, ds1);

  free(ds1);
}
