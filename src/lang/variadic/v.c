#include <_lang_.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define BSIZE 64
#define SELF_PRINTF(fmt, ...) self_printf((fmt), __VA_ARGS__)

int self_printf(const char *fmt, ...);

int
self_printf(const char *fmt, ...)
{
  char *buf = 0;
  int next = 0;
  int rc = EOF;

  buf = malloc(sizeof(*buf) * BSIZE);
  if (!buf)
    {
      perror(0);
      goto clean_exit;
    }
  
  va_list args;
  va_start(args, fmt);

  while (*fmt)
    {
      if (*fmt == '%')
        {
          char n = *(fmt + 1);
          if (n == 'c')
            {
              int c = va_arg(args, int);
              buf[next++] = (char) c;
              ++fmt;
            }
          else if (n == 'd')
            {
              int d = va_arg(args, int);
              int len = snprintf(&buf[next], 5, "%d", d);
              next += len;
              ++fmt;
            }
          else
            {
              /* do nothing */
            }
        }
      else
        {
          buf[next++] = *fmt;
        }
      ++fmt;
    }
  buf[next] = 0;

  va_end(args);
  
  rc = puts(buf);
  if (rc < 0)
    {
      goto clean_exit;
    }
  rc = (int) strlen(buf);

 clean_exit:
  free(buf);
  return rc;
}
  
int
main(int argc, char **argv)
{
  if (argc < 4)
    {
      printf("please, input a character and an integer.\n");
      return 1;
    }

  int rc1, rc2;
  rc1 = self_printf(argv[1], argv[2][0], atoi(argv[3]));
  rc2 = printf(argv[1], argv[2][0], atoi(argv[3]));
  assert(rc1 == rc2);

  putchar('\n');
  rc1 = SELF_PRINTF(argv[1], argv[2][0], atoi(argv[3]));
  assert(rc1 > 0);

  return 0;
}
