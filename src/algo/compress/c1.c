#include <_algo_.h>

char *compress1(char const *ss, int len, char *ds);
void test(char const *ss);

char*
compress1(char const *ss, int len, char *ds)
{
  int di = 0;
  int i = 0;
  while (i < len)
    {
      int j = i;
      while (i < len && ss[i] == ss[i+1])
        {
          ++i;
        }
      di += sprintf(&ds[di], "%c%i", ss[j], (i-j)+1);
      i++;
    }
  return ds;
}

void
test(char const *ss)
{
  char *ds1;
  int len = (int)strlen(ss);

  ds1 = malloc(sizeof(*ds1) * len);
  compress1(ss, len, ds1);
  free(ds1);

  printf("compress:\n------------\n");
  printf("src=%s\ndst=%s\n", ss, ds1);
}

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);
  
  if (argc < 2)
    {
      printf("please, input source string!\n");
      return 0;
    }

  test(argv[1]);

  return 0;
}
