#include "_stdio1_.h"


extern char  *strerror(int);


static  char  _stdin_buf_[BUFSIZ];
static  char  _stdout_buf_[BUFSIZ];

static FILE  _stdin_  =
  {
    .fd        =  STDIN_FILENO,
    .buf_type  =  _IOLBF,
    .buf_read  =  _stdin_buf_,
    .buf_size  =  BUFSIZ
  };

static FILE  _stdout_  =
  {
    .fd         =  STDOUT_FILENO,
    .buf_type   =  _IOLBF,
    .buf_write  =  _stdout_buf_,
    .buf_size   =  BUFSIZ
  };

static FILE  _stderr_  =
  {
    .fd        =  STDERR_FILENO,
    .buf_type  =  _IONBF,
    .buf_size  =  0
  };

FILE  *stdin   =  &_stdin_;
FILE  *stdout  =  &_stdout_;
FILE  *stderr  =  &_stderr_;



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


int
fileno(FILE *stream)
{
  return stream->fd;
}


int
fclose(FILE *stream)
{
  if (stream == NULL)
    {
      return 0;
    }

  fflush(stream);

  if (stream == stdin || stream == stdout || stream == stderr)
    {
      return 0;
    }

  if (stream->buf_read != NULL)
    {
      free(stream->buf_read);
      stream->buf_read = NULL;
    }

  if (stream->buf_write != NULL)
    {
      free(stream->buf_write);
      stream->buf_write = NULL;
    }

  if (stream->stat != NULL)
    {
      free(stream->stat);
      stream->stat = NULL;
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
  if (stream->ptr_write > 0)
    {
      if (write(stream->fd, stream->buf_write, stream->ptr_write) == -1)
        {
          stream->err = errno;
          return EOF;
        }
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

  ss->stat = calloc(1, sizeof(ss->stat));
  if (ss->stat == NULL)
    {
      ss->err = errno;
      goto clean_exit;
    }

  if (fstat(ss->fd, ss->stat) == -1)
    {
      ss->err = errno;
      goto clean_exit;
    }

  ss->buf_size = ss->stat->st_blksize;

  ss->buf_read = calloc(1, sizeof(ss->buf_size));
  if (ss->buf_read == NULL)
    {
      ss->err = errno;
      goto clean_exit;
    }

  ss->buf_write = calloc(1, sizeof(ss->buf_size));
  if (ss->buf_write == NULL)
    {
      ss->err = errno;
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

  if (stream->ptr_read < stream->n_read)
    {
      return stream->buf_read[stream->ptr_read++];
    }

  n = read(stream->fd, stream->buf_read, stream->buf_size);

  if (n == -1)
    {
      stream->err = errno;
      return EOF;
    }

  if (n == 0)
    {
      return stream->eof = EOF;
    }

  stream->n_read = n;
  stream->ptr_read = 0;

  return stream->buf_read[stream->ptr_read++];
}

int
fputc(int c, FILE *stream)
{
  ssize_t  n;

  if (stream->ptr_write == stream->buf_size)
    {
      n = write(stream->fd, stream->buf_write, stream->buf_size);

      if (n == -1)
        {
          stream->err = errno;
          return EOF;
        }

      stream->ptr_write = 0;
    }

  stream->buf_write[stream->ptr_write++] = c;

  switch (stream->buf_type)
    {
    case _IOLBF:
      if (c == '\n')
        {
          n = write(stream->fd, stream->buf_write, stream->ptr_write);
          if (n == -1)
            {
              stream->err = errno;
              return EOF;
            }
          stream->ptr_write = 0;
        }
      break;

    case _IONBF:
      n = write(stream->fd, stream->buf_write, 1);
      if (n == -1)
        {
          stream->err = errno;
          return EOF;
        }
      stream->ptr_write = 0;
      break;
    }

  return c;
}


size_t
fread(void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream)
{
  size_t  n  =  0;

  if (size == 0 || nitems == 0)
    {
      return 0;
    }

  for (size_t i = 0; i < nitems; i++)
    {
      n++;

      for (size_t j = 0; j < size; j++)
        {
          int  c  =  fgetc(stream);

          if (stream->err || stream->eof)
            {
              return 0;
            }

          ((char *) ptr) [i * size + j] = c;
        }
    }

  return n;
}


size_t
fwrite(const void *restrict ptr, size_t size, size_t nitems,
       FILE *restrict stream)
{
  size_t  n  =  0;

  for (size_t i = 0; i < nitems; i++)
    {
      n++;

      for (size_t j = 0; j < size; j++)
        {
          int  c  =  fputc(((char *) ptr) [i * size + j], stream);

          if (c == EOF)
            {
              return 0;
            }
        }
    }

  return n;
}
