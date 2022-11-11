#include "_io_.h"

/*
 * Parent process and child process:
 *
 * 1. share the same v-node table.
 * 2. but does not share file table via `open'.
 * 3. atomic O_APPEND is not same as lseek then write.
 * 4. pwrite should ignore offset when O_APPEND had been specified.
 * 5. pwrite same as write open with O_APPEND on Linux.
 *
 *
 * References:
 *
 * POSIX requires that opening a file with the O_APPEND flag should
 * have no affect on the location at which pwrite() writes
 * data. However, on Linux, if a file is opened with O_APPEND,
 * pwrite() appends data to the end of the file, regardless of the
 * value of offset.
 *
 */


#define _OFLAGS_  (O_WRONLY | O_CREAT | O_APPEND)


void out(int fd, char w);


int
main(int argc, char **argv)
{
  pid_t  pid;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname>\n", basename(argv[0]));
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
      int  fd;
      fd = open(argv[1], _OFLAGS_, S_IRUSR | S_IWUSR);
      if (fd == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
      out(fd, '_');
    }
  else
    {
      int  fd;
      fd = open(argv[1], _OFLAGS_, S_IRUSR | S_IWUSR);
      if (fd == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
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

#if defined(_PWRITE_)

#  if (LINUX)
      assert(ss.st_size == (_N_ * 2));
#  endif

#  if (DARWIN)
      assert(ss.st_size == 1);
#  endif

#else
      /* O_APPEND ensure */
      assert(ss.st_size == (_N_ * 2));
#endif

    }
}


void
out(int fd, char w)
{
  ssize_t  n;

  for (int i = 0; i < _N_ /* -D_N_ */; i++)
    {

#if defined(_PWRITE_)

      n = pwrite(fd, &w, sizeof(char), 0 /* offset */);

#else

      n = write(fd, &w, sizeof(char));

#endif

      if (n == -1)
        {
          perror(NULL);
          break;
        }

    }
}
