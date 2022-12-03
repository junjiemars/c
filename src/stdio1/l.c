#include "_stdio1_.h"
#include <termios.h>


extern char  *strerror(int);

#define _IO_INIT_   0x0001



#define _io_is_init_(x)   (((x) & _IO_INIT_) == _IO_INIT_)


static FILE  _stdin_  =
  {
    .fd        =  STDIN_FILENO,
  };

static FILE  _stdout_  =
  {
    .fd        =  STDOUT_FILENO,
  };

static FILE  _stderr_  =
  {
    .fd        =  STDERR_FILENO,
  };

FILE  *stdin   =  &_stdin_;
FILE  *stdout  =  &_stdout_;
FILE  *stderr  =  &_stderr_;

static int   _file_init_(FILE *);
static void  _file_close_(void);

static char *_vsnprint_num_(char *, char *, unsigned long long,
                            char, unsigned int, unsigned int);


int
feof(FILE *stream)
{
  return stream->eof;
}

int
ferror(FILE *stream)
{
  return stream->err;
}


void
clearerr(FILE *stream)
{
  stream->err = stream->eof = 0;
}


int
fileno(FILE *stream)
{
  return stream->fd;
}


int
fclose(FILE *stream)
{
  static int  has_close  =  0;

  if (stream == NULL)
    {
      /* !TODO: should flush and close all opened fd; */
      return 0;
    }

  fflush(stream);

  if (stream == stdin || stream == stdout || stream == stderr)
    {
      if (!has_close)
        {
          if (atexit(_file_close_) == -1)
            {
              stream->err = errno;
              return EOF;
            }
          has_close = 1;
        }
      return 0;
    }

  if (stream->buf != NULL)
    {
      free(stream->buf);
      stream->buf = NULL;
    }

  if (close(stream->fd) == -1)
    {
      return EOF;
    }

  free(stream);

  return 0;

}

int
fflush(FILE *stream)
{
  if (stream->buf_type == _IONBF)
    {
      return 0;
    }

  if (stream->offset > 0)
    {
      if (write(stream->fd, stream->buf, stream->offset) == -1)
        {
          stream->err = errno;
          return EOF;
        }
      stream->offset = 0;
    }

  return 0;
}


FILE *
fopen(const char *restrict path, const char *restrict mode)
{
  FILE  *ss;

  ss = calloc(1, sizeof(FILE));
  if (ss == NULL)
    {
      return NULL;
    }

  if (strcmp("r", mode) == 0 || strcmp("rb", mode) == 0)
    {
      ss->fd = open(path, O_RDONLY);
    }
  else if (strcmp("r+", mode) == 0 || strcmp("rb+", mode) == 0
           || strcmp("r+b", path) == 0)
    {
      ss->fd = open(path, O_RDWR);
    }
  else if (strcmp("w", mode) == 0 || strcmp("wb", mode) == 0)
    {
      ss->fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    }
  else if (strcmp("w+", mode) == 0 || strcmp("wb+", mode) == 0
           || strcmp("w+b", mode) == 0)
    {
      ss->fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0666);
    }
  else if (strcmp("a", path) == 0)
    {
      ss->fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0666);
    }
  else if (strcmp("a+", path) == 0 || strcmp("ab+", path) == 0
           || strcmp("a+b", path) == 0)
    {
      ss->fd = open(path, O_RDWR | O_CREAT | O_APPEND, 0666);
    }
  else
    {
      errno = EINVAL;
      goto clean_exit;
    }

  if (ss->fd == -1)
    {
      goto clean_exit;
    }

  if (_file_init_(ss) == EOF)
    {
      goto clean_exit;
    }

  return ss;

 clean_exit:
  fclose(ss);

  return NULL;
}

int
fgetc(FILE *stream)
{
  ssize_t  n;

  if (stream->eof)
    {
      return stream->eof;
    }

  if (!_io_is_init_(stream->flags))
    {
      if (_file_init_(stream) == EOF)
        {
          return EOF;
        }
    }

  if (stream->buf_type == _IONBF)
    {
      int  c;

      if (read(stream->fd, &c, sizeof(unsigned char)) == -1)
        {
          stream->err = errno;
          return EOF;
        }
      return c;
    }

  if ((stream->buf + stream->offset) < stream->last)
    {
      return stream->buf[stream->offset++];
    }

  n = read(stream->fd, stream->buf, stream->buf_size);

  if (n == -1)
    {
      stream->err = errno;
      return EOF;
    }

  if (n == 0)
    {
      return stream->eof = EOF;
    }

  stream->last = stream->buf + n;
  stream->offset = 0;

  return stream->buf[stream->offset++];
}

int
fputc(int c, FILE *stream)
{
  if (!_io_is_init_(stream->flags))
    {
      if (_file_init_(stream) == EOF)
        {
          return EOF;
        }
    }

  if (stream->buf_type == _IONBF)
    {
      if (write(stream->fd, (unsigned char*) &c, sizeof(unsigned char)) == -1)
        {
          stream->err = errno;
          return EOF;
        }
      return c;
    }

  if ((size_t) stream->offset == stream->buf_size)
    {
      if (write(stream->fd, stream->buf, stream->buf_size) == -1)
        {
          stream->err = errno;
          return EOF;
        }

      stream->offset = 0;
    }

  stream->buf[stream->offset++] = (unsigned char ) c;

  if (stream->buf_type == _IOLBF && c == '\n')
    {
      if (write(stream->fd, stream->buf, stream->offset) == -1)
        {
          stream->err = errno;
          return EOF;
        }

      stream->offset = 0;
    }

  return c;
}


size_t
fread(void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream)
{
  size_t          n, m, sum;
  ssize_t         r;
  unsigned char  *cur;

  if (size == 0 || nitems == 0)
    {
      return 0;
    }

  n = (size * nitems) / stream->buf_size;
  m = (size * nitems) % stream->buf_size;
  sum = 0;
  cur = (unsigned char *) ptr;

  if (m > 0)
    {
      r = read(stream->fd, cur, m);
      if (r == -1)
        {
          stream->err = errno;
          return 0;
        }
      if (r == 0)
        {
          return 0;
        }

      sum += r;
      cur += r;
    }

  for (size_t i = 0; i < n; i++)
    {
      r = read(stream->fd, cur, stream->buf_size);
      if (r == -1)
        {
          stream->err = errno;
          return 0;
        }
      if (r == 0)
        {
          break;
        }

      sum += r;
      cur += r;
    }

  return (sum / size);
}


size_t
fwrite(const void *restrict ptr, size_t size, size_t nitems,
       FILE *restrict stream)
{
  size_t          n, m, sum;
  ssize_t         w;
  unsigned char  *cur;

  if (size * nitems == 0)
    {
      return 0;
    }

  if (stream->buf_type == _IONBF)
    {
      n = size * nitems;
      w = write(stream->fd, (unsigned char *) ptr, n);
      if (w == -1)
        {
          stream->err = errno;
          return 0;
        }

      return w / size;
    }

  n = (size * nitems) / stream->buf_size;
  m = (size * nitems) % stream->buf_size;
  sum = 0;
  cur = (unsigned char *) ptr;

  if (m > 0)
    {
      w = write(stream->fd, cur, m);
      if (w == -1)
        {
          stream->err = errno;
          return 0;
        }
      if (w == 0)
        {
          return 0;
        }

      sum += w;
      cur += w;
    }


  for (size_t i = 0; i < n; i++)
    {
      w = write(stream->fd, cur, stream->buf_size);
      if (w == -1)
        {
          stream->err = errno;
          return 0;
        }
      if (w == 0)
        {
          return 0;
        }

      cur += w;
      sum += w;
    }

  return (sum / size);
}


int
vsnprintf(char *restrict s, size_t n, const char *restrict format, va_list ap)
{
  char  *ps  =  s;

  while (*format && (size_t) (ps - s) < n)
    {
      char                zero;
      unsigned int        width, sign, ratio;
      long long           ll;
      unsigned long long  ull;

      if (*format == '%')
        {
          zero = *++format == '0' ? '0' : ' ';
          width = 0;
          sign = 1;
          ratio = 0;

          while (*format >= '0' && *format <= '9')
            {
              width = width * 10 + (*format++ - '0');
            }

          for (;;)
            {
              switch (*format)
                {
                case 'u':
                  {
                    sign = 0;
                    format++;
                    continue;
                  }
                case 'x':
                  {
                    ratio = 1;
                    sign = 0;
                    format++;
                    continue;
                  }
                default:
                  {
                    break;
                  }
                }
              break;
            }

          switch (*format)
            {
            case 'd':
              {
                if (sign)
                  {
                    ll = (long long) va_arg(ap, int);
                  }
                else
                  {
                    ull = (unsigned long long) va_arg(ap, unsigned int);
                  }
                break;
              }
            case 'i':
              if (sign) {
                ll = (long long) va_arg(ap, int);
              } else {
                ull = (unsigned long long) va_arg(ap, unsigned int);
              }
              break;
            case 's':
              {
                char *s1 = va_arg(ap, char *);
                while (*s1)
                  {
                    *ps++ = *s1++;
                  }
                format++;
                continue;
              }
            default:
              {
                *ps++ = *format++;
                continue;
              }
            }

          if (sign)
            {
              if (ll < 0)
                {
                  *ps++ = '-';
                  ull = (unsigned long long) -ll;
                }
              else
                {
                  ull = (unsigned long long) ll;
                }
            }

          ps = _vsnprint_num_(ps, s+n, ull, zero, ratio, width);

          format++;
        }
      else
        {
          *ps++ = *format++;
        }
    }

  return (int) (ps - s);
}


int
fprintf(FILE * restrict stream, const char * restrict format, ...)
{
  static char  buf[NM_LINE_MAX];
  int          len;
  size_t       n;

  va_list ap;
  va_start(ap, format);

  len = vsnprintf(buf, NM_LINE_MAX-1, format, ap);
  va_end(ap);

  n = fwrite(buf, sizeof(*buf), len, stream);

  return n;
}

int
_file_init_(FILE *stream)
{
  struct stat  ss;

  if (_io_is_init_(stream->flags))
    {
      return 0;
    }

  if (stream == stdin || stream == stdout || stream == stderr)
    {
      if (stream == stderr)
        {
          stream->buf_type = _IONBF;
          stream->buf_size = 0;
          stream->buf = NULL;
        }
      else if (isatty(stream->fd))
        {
          stream->buf_type = _IOLBF;
          stream->buf_size = NM_LINE_MAX;

          stream->buf = malloc(stream->buf_size);
          if (stream->buf == NULL)
            {
              stream->err = errno;
              return EOF;
            }
        }
      else
        {
          if (fstat(stream->fd, &ss) == -1)
            {
              stream->err = errno;
              return EOF;
            }

          stream->buf_type = _IOFBF;
          stream->buf_size = ss.st_blksize;

          stream->buf = malloc(stream->buf_size);
          if (stream->buf == NULL)
            {
              stream->err = errno;
              return EOF;
            }
        }
    }
  else
    {
      if (fstat(stream->fd, &ss) == -1)
        {
          stream->err = errno;
          return EOF;
        }

      stream->buf_type = _IOFBF;
      stream->buf_size = ss.st_blksize;

      stream->buf = malloc(stream->buf_size);
      if (stream->buf == NULL)
        {
          stream->err = errno;
          return EOF;
        }
    }

  stream->flags |= _IO_INIT_;

  return 0;
}

void
_file_close_(void)
{
  if (stdin != NULL && stdin->buf != NULL)
    {
      free(stdin->buf);
      stdin->buf = NULL;
    }

  if (stdout != NULL && stdout->buf != NULL)
    {
      free(stdout->buf);
      stdout->buf = NULL;
    }

  if (stderr != NULL && stderr->buf != NULL)
    {
      free(stderr->buf);
      stderr->buf = NULL;
    }
}

char *
_vsnprint_num_(char *buf, char *last, unsigned long long ull,
               char zero, unsigned int ratio, unsigned int width)
{
  unsigned int   len;
  char          *p, b[sizeof(long long)+1];
  static  char   hex[]  =  "0123456789abcdef";
  static  char   HEX[]  =  "0123456789ABCDEF";

  p = b + sizeof(long long);

  if (ratio == 0)
    {
      do
        {
          *--p = (char) (ull % 10 + '0');
        }
      while (ull /= 10);
    }
  else if (ratio == 1)
    {
      do
        {
          *--p = (char) (hex[ull & 0xf]);
        }
      while (ull >>= 4);
    }
  else
    {
      do
        {
          *--p = (char) (HEX[ull & 0xf]);
        }
      while (ull >>= 4);
    }

  len = (b + sizeof(long long)) - p;

  while (len++ < width && buf < last)
    {
      *buf++ = zero;
    }

  len = (b + sizeof(long long)) - p;

  if (buf + len > last)
    {
      len = last - buf;
    }

  while (len-- > 0)
    {
      *buf++ = *p++;
    }

  return buf;
}
