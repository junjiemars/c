#include "_io_.h"

/*
 * 1. if fd1 equals fd2 then returns fd2;
 *
 * 2. if fd2 is already open, then it is first closed.
 *
 * 3. otherwise, the `FD_CLOEXEC' is cleared for fd2.
 *
 * 4. `dup2' is an atomic operation.
 *
 */

static char buf[BUFSIZ];
static int next_fd = 10;

int
main (void)
{
  int n;
  int fd_in, fd_out;

  fd_in = dup2 (STDIN_FILENO, next_fd++);
  if (fd_in == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  assert ((fd_in + 1) == next_fd);

  fd_out = dup2 (STDOUT_FILENO, next_fd++);
  if (fd_out == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  assert ((fd_out + 1) == next_fd);
  assert ((fd_in + 1) == fd_out);

  while ((n = read (fd_in, buf, BUFSIZ)) > 0)
    {
      if (write (fd_out, buf, n) != n)
        {
          perror (NULL);
          exit (EXIT_FAILURE);
        }
    }

#if (NM_HAVE_GETDTABLE_SIZE)
  int fd_size = getdtablesize ();
  int fd_out_of_range = dup2 (STDIN_FILENO, fd_size+1);
  assert (fd_out_of_range == -1);
#endif
  exit (EXIT_SUCCESS);
}
