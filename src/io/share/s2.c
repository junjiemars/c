#include "_io_.h"

/*
 * Parent process and child process:
 * 1. share the same v-node table.
 * 2. but does not share file table.
 * 3. automatic O_APPEND is not same as lseek then write.
 * 4. pwrite should ignore offset when O_APPEND had been specified.
 * 5. pwrite same as write open with O_APPEND on Linux.
 *
 */


#define OFLAGS  (O_WRONLY | O_CREAT | O_APPEND)



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

  pid = fork();
  if (pid == -1)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }
  else if (pid == 0)
    {
      fd = open(argv[1], OFLAGS, S_IRUSR | S_IWUSR);
      if (fd == -1)
        {
          perror("!panic");
          exit(EXIT_FAILURE);
        }

      out(fd, '_');
    }
  else
    {
      fd = open(argv[1], OFLAGS, S_IRUSR | S_IWUSR);
      if (fd == -1)
        {
          perror("!panic");
          exit(EXIT_FAILURE);
        }

      out(fd, '|');
    }
}


void
out(int fd, char w)
{
  ssize_t  n;

  for (int i = 0; i < N; i++)
    {

#if (_PWRITE_)
      n = pwrite(fd, &w, sizeof(char), 0 /* offset */);
#else
      n = write(fd, &w, sizeof(char));

#endif

      if (n == -1)
        {
          perror("!panic");
          break;
        }
    }
}
