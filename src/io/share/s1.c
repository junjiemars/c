#include "_io_.h"

/*
 * Parent process and child process:
 * 1. shared the same file table.
 *
 */

#define OFLAGS  (O_RDWR | O_CREAT)


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

  fd = open(argv[1], OFLAGS, S_IRUSR | S_IWUSR);
  if (fd == -1)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }

  pid = fork();
  if (pid == -1)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }
  else if (pid == 0)
    {
      out(fd, '_');
      exit(EXIT_SUCCESS);
    }
  else
    {
      out(fd, '|');
      exit(EXIT_SUCCESS);
    }
}


void
out(int fd, char w)
{
  for (int i = 0; i < N; i++)
    {
      if ((write(fd, &w, sizeof(char))) == -1)
        {
          perror("!panic");
          break;
        }
    }
}
