#include "_io_.h"

/*
 * Q: Why close the fildes when the fildes greater than 2?
 *
 */

static void usage(char **argv);

int
main(int argc, char **argv)
{
  int  fd;
  int  fd1, fd2, fd3;

  if (argc < 2)
    {
      usage(argv);
      exit(EXIT_FAILURE);
    }

  fd = atoi(argv[1]);

  if (fd > 2)
    {
      if (argc > 2)
        {
          fd = open(argv[1], O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
          if (fd == -1)
            {
              perror(NULL);
              exit(EXIT_FAILURE);
            }
        }
      else
        {
          usage(argv);
          exit(EXIT_FAILURE);
        }
    }


  fd1 = dup2(fd, 0);
  fd2 = dup2(fd, 1);
  fd3 = dup2(fd, 2);

  /* Q */
  if (fd > 2)
    {
      close(fd);
    }

  exit(EXIT_SUCCESS);
}


void
usage(char **argv)
{
  fprintf(stderr, "usage: %s <fildes> [pathname]\n", basename(argv[0]));
}
