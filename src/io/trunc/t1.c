#include "_io_.h"


int
main(int argc, char **argv)
{
  int          len;
  struct stat  s_old, s_new;

  if (argc < 3)
    {
      fprintf(stderr, "usage: <pathname> <length>\n");
      exit(EXIT_FAILURE);
    }
  len = atoi(argv[2]);

  if (lstat(argv[1], &s_old) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (truncate(argv[1], len) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (lstat(argv[1], &s_new) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  assert(s_new.st_size == len);

  if (s_old.st_size < len)
    {
      int   n, fd;
      char  buf[BUFSIZ];
      int   n_read  =  len - s_old.st_size;

      fd = open(argv[1], O_RDONLY);
      if (fd == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
      if (lseek(fd, s_old.st_size, SEEK_SET) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }

      while ((n = read(fd, buf, BUFSIZ)) > 0)
        {
          int  min  =  _min_(n_read, n);
          for (int i = 0; i < min; i++)
            {
              assert('\0' == buf[i]);
            }
          break;
        }

    }

  exit(EXIT_SUCCESS);
}
