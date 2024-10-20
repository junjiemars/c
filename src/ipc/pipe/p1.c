#include <_ipc_.h>
#include <string.h>

#define _TXT_ "hello pipe\n"

int
main (void)
{
  ssize_t n;
  int fildes[2];
  struct stat fs;
  pid_t pid;
  char line[NM_LINE_MAX];

  if (pipe (fildes) == -1)
    {
      perror (0);
      exit (1);
    }

  for (int i = 0; i < (int)_nof_ (fildes); i++)
    {
      if (fstat (fildes[i], &fs) == -1)
        {
          perror (NULL);
          exit (1);
        }
      if (S_ISFIFO (fs.st_mode))
        {
          printf ("fildes[%i]=%i fifo\n", i, fildes[i]);
        }
      printf ("fildes[%i]=%i size %zu\n", i, fildes[i], (size_t)fs.st_size);
    }

  if ((pid = fork ()) == -1)
    {
      perror (0);
      exit (1);
    }
  else if (pid > 0)
    {
      close (fildes[0]); /* close read fd */
      write (fildes[1], _TXT_, sizeof (_TXT_) - 1);
      waitpid (pid, NULL, 0);
    }
  else
    {
      close (fildes[1]); /* close write fd */
      n = snprintf (line, NM_LINE_MAX,
                    "%zi received from %zi: ", (size_t)getpid (),
                    (size_t)getppid ());
      n += read (fildes[0], line + n, NM_LINE_MAX);
      write (STDOUT_FILENO, line, n);
    }

  exit (0);
}
