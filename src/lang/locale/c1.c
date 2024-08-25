#include "_lang_.h"
#include <locale.h>

int
main (void)
{
  printf ("current locale:\n------------\n");
  for (int cate = LC_ALL; cate < _LC_LAST; cate++)
    {
      printf ("%d %s\n", cate, setlocale (cate, 0));
    }

  printf ("env locale:\n------------\n");
  for (int cate = LC_ALL; cate < _LC_LAST; cate++)
    {
      printf ("%d %s\n", cate, setlocale (cate, ""));
    }
}
