#include "_io_.h"


/*
 * 1. It's unseekable when fd point to a pipe, FIFO, or socket.
 *
 */


static char get_filetype(mode_t);


int
main(int argc, char **argv)
{
  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <fileno...>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  for (int i = 1; i < argc; i++)
    {
      int          fd;
      struct stat  ss;

      fd = atoi(argv[i]);

      if (fstat(fd, &ss) == -1)
        {
          perror(NULL);
          continue;
        }

      char ft = get_filetype(ss.st_mode);
      off_t offset = lseek(fd, 0, SEEK_CUR);

      printf("%d: %c(%c)\n", fd, ft, (offset == -1) ? '_' : '*');
    }

  exit(EXIT_SUCCESS);
}


char
get_filetype(mode_t m)
{
  if (S_ISREG(m))
    {
      return 'r';
    }
  else if (S_ISDIR(m))
    {
      return 'd';
    }
  else if (S_ISCHR(m))
    {
      return 'c';
    }
  else if (S_ISBLK(m))
    {
      return 'b';
    }
  else if (S_ISFIFO(m))
    {
      return 'p';
    }
  else if (S_ISSOCK(m))
    {
      return 's';
    }
  else
    {
      return '?';
    }
}
