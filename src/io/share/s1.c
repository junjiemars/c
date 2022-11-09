#include "_io_.h"


/*
 * Parent process and child process:
 *
 * 1. they shared the same file table.
 *
 */


#define _OFLAGS_  (O_RDWR | O_CREAT)


void out(int fd, char w);


int
main(int argc, char **argv)
{
  int    fd;
  pid_t  pid;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  fd = open(argv[1], _OFLAGS_, S_IRUSR | S_IWUSR);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  pid = fork();
  if (pid == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  else if (pid == 0)
    {
      out(fd, '_');
    }
  else
    {
      out(fd, '|');
      if (waitpid(pid, NULL, 0) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }

      struct stat  ss;
      if (fstat(fd, &ss) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
      /* proved 1st. */
      assert(ss.st_size == (size_t) (_N_ * 2));

      exit(EXIT_SUCCESS);
    }
}


void
out(int fd, char w)
{
  for (int i = 0; i < _N_ /* -D_N_ */; i++)
    {
      if ((write(fd, &w, sizeof(char))) == -1)
        {
          perror(NULL);
          break;
        }
    }
}
