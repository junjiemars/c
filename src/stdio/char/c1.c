#include "../_stdio_.h"
#include <ctype.h>

int
main (void)
{
  int c;
  int n = 16;

  while (n-- > 0)
    {
      if ((c = getc (stdin)) == EOF)
        {
          break;
        }

      if (ferror (stdin))
        {
          return errno;
        }

      putc (c, stdout);

      if ((c & 1) == 0)
        {
          ungetc (toupper (c + 1), stdin);
        }
    };

  return 0;
}
