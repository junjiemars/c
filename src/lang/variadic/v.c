#include <_lang_.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define BSIZE 64
#define SELF_FPRINTF(stream, ...) self_fprintf((stream), __VA_ARGS__)

int self_fprintf(FILE *stream, const char *fmt, ...);

void test_self_fprintf(void);

int
self_fprintf(FILE *stream, const char *fmt, ...)
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

  while (*fmt && next < BSIZE)
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
          else if (n == 'd' || n == 'i')
            {
              static const char digit[] = "0123456789";
              int i = va_arg(args, int);
              if (i < 0)
                {
                  buf[next++] = '-';
                  i = -i;
                }
              int shift = i;
              int nx = 0;
              do
                {
                  next++;
                  shift /= 10;
                } while (shift);
              shift = i;
              nx = next - 1;
              do
                {
                  buf[nx--] = digit[shift % 10];
                  shift /= 10;
                } while (shift);
              ++fmt;
            }
          else if (n == 'f')
            {
              /* !TODO: float to string in raw */
              double d = va_arg(args, double);
              int len = snprintf(&buf[next], 16, "%f", d);
              next += len;
              ++fmt;
            }
          else if (n == 's')
            {
              char *s = va_arg(args, char *);
              size_t len = strnlen(s, BSIZE);
              strncpy(&buf[next], s, len);
              next += (int) len;
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
  
  rc = fputs(buf, stream);
  if (rc < 0)
    {
      goto clean_exit;
    }
  rc = (int) strlen(buf);

 clean_exit:
  free(buf);
  return rc;
}

void
test_self_fprintf(void)
{
  int rc1, rc2;

  rc1 = fprintf(stdout, "abc\n");
  rc2 = self_fprintf(stdout, "abc\n");
  assert(rc1 == rc2);

  rc1 = fprintf(stdout, "%s\n", "abc");
  rc2 = self_fprintf(stdout, "%s\n", "abc");
  assert(rc1 == rc2);

  rc1 = fprintf(stdout, "%d\n", 123);
  rc2 = self_fprintf(stdout, "%d\n", 123);
  assert(rc1 == rc2);

  rc1 = fprintf(stdout, "%d\n", -123);
  rc2 = self_fprintf(stdout, "%d\n", -123);
  assert(rc1 == rc2);

  rc1 = fprintf(stdout, "%i\n", 0x11223344);
  rc2 = self_fprintf(stdout, "%i\n", 0x11223344);
  assert(rc1 == rc2);

  rc1 = fprintf(stdout, "%f\n", 3.14159);
  rc2 = self_fprintf(stdout, "%f\n", 3.14159);
  assert(rc1 == rc2);

  rc1 = fprintf(stdout, "%c\n", 'A');
  rc2 = fprintf(stdout, "%c\n", 'A');
  assert(rc1 == rc2);
  
  rc1 = fprintf(stdout, "%c %d-dimentional continuum.\n", 'A', 4);
  rc2 = self_fprintf(stdout, "%c %d-dimentional continuum.\n", 'A', 4);
  assert(rc1 == rc2);

  rc1 = fprintf(stdout, "abc, abcd, icjjckkkc, %s\n", "icjjcllllc");
  rc2 = SELF_FPRINTF(stdout, "abc, abcd, icjjckkkc, %s\n", "icjjcllllc");
  assert(rc1 == rc2);
}
  
int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  test_self_fprintf();

  return 0;
}
