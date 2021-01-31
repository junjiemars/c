#include <_lang_.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define BSIZE 64

#define BUFFERED_FPRINTF(stream, ...) buffered_fprintf((stream), __VA_ARGS__)
#define STREAM_FPRINTF(stream, ...) stream_fprintf((stream), __VA_ARGS__)

typedef int (*fbsprintf)(FILE *stream, const char *fmt, ...);

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

#define FPUTC(c, stream, inc)                   \
  do                                            \
    {                                           \
      if (EOF == fputc((int) (c), stream))      \
        {                                       \
          return EOF;                           \
        }                                       \
      inc++;                                    \
    } while (0)

#define FPUTS(s, stream, inc)                   \
  do                                            \
    {                                           \
      int _n1_ = fputs((s), stream);            \
      if (EOF == _n1_)                          \
        {                                       \
          return EOF;                           \
        }                                       \
      inc += _n1_;                              \
    } while (0)


int buffered_fprintf(FILE *stream, const char *fmt, ...);
int stream_fprintf(FILE *stream, const char *fmt, ...);
int itos(int i, char *buf);

void test_fprintf_basic(void);
void test_fprintf_macro(void);
void test_fprintf_fn(fbsprintf fn);

int
buffered_fprintf(FILE *stream, const char *fmt, ...)
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
              char ibuf[sizeof(int)*8];
              int i = va_arg(args, int);
              int len = itos(i, ibuf);
              strncpy(&buf[next], ibuf, len);
              next += len;
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

int
stream_fprintf(FILE *stream, const char *fmt, ...)
{
  size_t next = 0;
  char n;

  va_list args;
  va_start(args, fmt);

  while (*fmt)
    {
      if (*fmt == '%')
        {
          n = *(fmt + 1);
          if (n == '%')         /* %% */
            {
              FPUTC('%', stream, next);
              ++fmt;
            }
          else if (n == 'c')    /* %c */
            {
              int c = va_arg(args, int);
              FPUTC(c, stream, next);
              ++fmt;
            }
          else if (n == 'd' || n == 'i') /* %d or %i */
            {
              char buf[sizeof(int)*8];
              int i = va_arg(args, int);
              itos(i, buf);
              FPUTS(buf, stream, next);
              ++fmt;
            }
          else if (n == 's')    /* %s */
            {
              char *s = va_arg(args, char *);
              FPUTS(s, stream, next);
              ++fmt;
            }
          else
            {
              /* do nonthing */
            }
        }
      else
        {
          FPUTC(*fmt, stream, next);
        }
      ++fmt;
    }

  va_end(args);

  return (int) next;
}

int
itos(int i, char *buf)
{
  static const char digit[] = "0123456789";
  int nz = 0;
  if (i < 0)
    {
      buf[nz++] = '-';
      i = -i;
    }
  int shift = i;
  int na = nz;
  while (shift)
    {
      buf[nz++] = digit[shift % 10];
      shift /= 10;
    }
  for (int j = na, k = nz-1; j < k; j++, k--)
    {
      int m = buf[j];
      buf[j] = buf[k];
      buf[k] = (char) m;
    }
  buf[nz] = 0;
  return nz;
}

void
test_fprintf_basic(void)
{
  int rc1, rc2, rc3;
  _unused_(rc1);
  _unused_(rc2);
  _unused_(rc3);

  /* escape % */
  rc1 = fprintf(stdout, "%%\n");
  rc2 = buffered_fprintf(stdout, "%%\n");
  rc3 = stream_fprintf(stdout, "%%\n");
  assert(rc1 == rc2 && rc2 == rc3);

  /* raw */
  rc1 = fprintf(stdout, "abc\n");
  rc2 = buffered_fprintf(stdout, "abc\n");
  rc3 = stream_fprintf(stdout, "abc\n");
  assert(rc1 == rc2 && rc2 == rc3);

  /* %c */
  rc1 = fprintf(stdout, "%c\n", 'A');
  rc2 = buffered_fprintf(stdout, "%c\n", 'A');
  rc3 = stream_fprintf(stdout, "%c\n", 'A');
  assert(rc1 == rc2 && rc2 == rc3);

  /* %s */
  rc1 = fprintf(stdout, "%s\n", "abc");
  rc2 = buffered_fprintf(stdout, "%s\n", "abc");
  rc3 = stream_fprintf(stdout, "%s\n", "abc");
  assert(rc1 == rc2 && rc2 == rc3);

  /* %d */
  rc1 = fprintf(stdout, "%d\n", 123);
  rc2 = buffered_fprintf(stdout, "%d\n", 123);
  rc3 = stream_fprintf(stdout, "%d\n", 123);
  assert(rc1 == rc2 && rc2 == rc3);

  /* %d */
  rc1 = fprintf(stdout, "%d\n", -123);
  rc2 = buffered_fprintf(stdout, "%d\n", -123);
  rc3 = stream_fprintf(stdout, "%d\n", -123);
  assert(rc1 == rc2 && rc2 == rc3);

  /* %i */
  rc1 = fprintf(stdout, "%d\n", 012);
  rc2 = buffered_fprintf(stdout, "%d\n", 012);
  rc3 = stream_fprintf(stdout, "%d\n", 012);
  assert(rc1 == rc2 && rc2 == rc3);

  /* %i */
  rc1 = fprintf(stdout, "%i\n", 0x11223344);
  rc2 = buffered_fprintf(stdout, "%i\n", 0x11223344);
  rc3 = stream_fprintf(stdout, "%i\n", 0x11223344);
  assert(rc1 == rc2 && rc2 == rc3);

  /* %f */
  rc1 = fprintf(stdout, "%f\n", 3.14159);
  rc2 = buffered_fprintf(stdout, "%f\n", 3.14159);
  assert(rc1 == rc2);

  /* %s */
  rc1 = fprintf(stdout, "%c %d-dimentional continuum.\n", 'A', 4);
  rc2 = buffered_fprintf(stdout, "%c %d-dimentional continuum.\n", 'A', 4);
  rc3 = stream_fprintf(stdout, "%c %d-dimentional continuum.\n", 'A', 4);
  assert(rc1 == rc2 && rc2 == rc3);

  /* %s */
  rc1 = fprintf(stdout, "abc, abcd, icjjckkkc, %s\n", "icjjcllllc");
  rc2 = buffered_fprintf(stdout, "abc, abcd, icjjckkkc, %s\n", "icjjcllllc");
  rc3 = stream_fprintf(stdout, "abc, abcd, icjjckkkc, %s\n", "icjjcllllc");
  assert(rc1 == rc2 && rc2 == rc3);

  /* %s */
  char *s36 = "abcdefghijklmnopqrstuvwxyz0123456789";
  rc1 = fprintf(stdout, "%s, %s\n", s36, s36);
  rc2 = buffered_fprintf(stdout, "%s, %s\n", s36, s36);
  rc3 = stream_fprintf(stdout, "%s, %s\n", s36, s36);
  assert(rc1 == rc2 && rc2 == rc3);
}

void
test_fprintf_macro(void)
{
  int rc1, rc2, rc3;
  _unused_(rc1);
  _unused_(rc2);
  _unused_(rc3);

  /* %d */
  rc1 = fprintf(stdout, "%d\n", -123);
  rc2 = BUFFERED_FPRINTF(stdout, "%d\n", -123);
  rc3 = STREAM_FPRINTF(stdout, "%d\n", -123);
  assert(rc1 == rc2 && rc2 == rc3);
}

void
test_fprintf_fn(fbsprintf fn)
{
  int rc1, rc2;
  _unused_(rc1);
  _unused_(rc2);

  /* %d */
  rc1 = fprintf(stdout, "%d\n", -123);
  rc2 = fn(stdout, "%d\n", -123);
  assert(rc1 == rc2);
}

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  test_fprintf_basic();
  test_fprintf_macro();
  test_fprintf_fn(buffered_fprintf);
  test_fprintf_fn(stream_fprintf);

  return 0;
}
