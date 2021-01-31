#include <_lang_.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define BSIZE 64
#define SELF_FPRINTF(stream, ...) self_fprintf((stream), __VA_ARGS__)
#define RESIZE(ptr, size)                       \
  do                                            \
    {                                           \
      size += BSIZE;                            \
      ptr = realloc(ptr, size);                 \
      if (!ptr)                                 \
        {                                       \
          perror(0);                            \
          goto clean_exit;                      \
        }                                       \
    } while (0)

int self_fprintf(FILE *stream, const char *fmt, ...);

void test_self_fprintf(void);

int
self_fprintf(FILE *stream, const char *fmt, ...)
{
  char *buf = 0;
  size_t bsize = BSIZE;
  size_t next = 0;
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
      if (*fmt == '%')          /* % as format specifier */
        {
          char n = *(fmt + 1);
          if (n == '%')         /* escape % */
            {
              if ((next + 1) >= bsize)
                {
                  RESIZE(buf, bsize);
                }
              buf[next++] = '%';
              ++fmt;
            }
          else if (n == 'c')         /* %c */
            {
              int c = va_arg(args, int);
              if ((next + 1) >= bsize)
                {
                  RESIZE(buf, bsize);
                }
              buf[next++] = (char) c;
              ++fmt;
            }
          else if (n == 'd' || n == 'i') /* %d or %i */
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
          else if (n == 'f')    /* %f */
            {
              /* !TODO: float to string in raw */
              double d = va_arg(args, double);
              int len = snprintf(&buf[next], 16, "%f", d);
              next += len;
              ++fmt;
            }
          else if (n == 's')    /* %s */
            {
              char *s = va_arg(args, char *);
              size_t len = strnlen(s, BSIZE);
              size_t total = len;
              while (len > (bsize - next) || len == BSIZE)
                {
                  RESIZE(buf, bsize);
                  len = strnlen(s+total, BSIZE);
                  total += len;
                }
              strncpy(&buf[next], s, total);
              next += total;
              ++fmt;
            }
          else
            {
              /* do nothing */
            }
        }
      else
        {
          if ((next + 1) >= bsize)
            {
              RESIZE(buf, bsize);
            }
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

  /* escape % */
  rc1 = fprintf(stdout, "%%\n");
  rc2 = self_fprintf(stdout, "%%\n");
  assert(rc1 == rc2);

  /* raw */
  rc1 = fprintf(stdout, "abc\n");
  rc2 = self_fprintf(stdout, "abc\n");
  assert(rc1 == rc2);

  /* %c */
  rc1 = fprintf(stdout, "%c\n", 'A');
  rc2 = fprintf(stdout, "%c\n", 'A');
  assert(rc1 == rc2);

  /* %s */
  rc1 = fprintf(stdout, "%s\n", "abc");
  rc2 = self_fprintf(stdout, "%s\n", "abc");
  assert(rc1 == rc2);

  /* %d */
  rc1 = fprintf(stdout, "%d\n", 123);
  rc2 = self_fprintf(stdout, "%d\n", 123);
  assert(rc1 == rc2);

  /* %d */
  rc1 = fprintf(stdout, "%d\n", -123);
  rc2 = self_fprintf(stdout, "%d\n", -123);
  assert(rc1 == rc2);

  /* %i */
  rc1 = fprintf(stdout, "%d\n", 012);
  rc2 = self_fprintf(stdout, "%d\n", 012);
  assert(rc1 == rc2);
  
  /* %i */
  rc1 = fprintf(stdout, "%i\n", 0x11223344);
  rc2 = self_fprintf(stdout, "%i\n", 0x11223344);
  assert(rc1 == rc2);

  /* %f */
  rc1 = fprintf(stdout, "%f\n", 3.14159);
  rc2 = self_fprintf(stdout, "%f\n", 3.14159);
  assert(rc1 == rc2);

  /* %s */
  rc1 = fprintf(stdout, "%c %d-dimentional continuum.\n", 'A', 4);
  rc2 = self_fprintf(stdout, "%c %d-dimentional continuum.\n", 'A', 4);
  assert(rc1 == rc2);

  /* %s, resize buffer */
  rc1 = fprintf(stdout, "abc, abcd, icjjckkkc, %s\n", "icjjcllllc");
  rc2 = SELF_FPRINTF(stdout, "abc, abcd, icjjckkkc, %s\n", "icjjcllllc");
  assert(rc1 == rc2);

  /* %s, resize buffer */
  char *s36 = "abcdefghijklmnopqrstuvwxyz0123456789";
  rc1 = fprintf(stdout, "%s, %s\n", s36, s36);
  rc2 = self_fprintf(stdout, "%s, %s\n", s36, s36);
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
