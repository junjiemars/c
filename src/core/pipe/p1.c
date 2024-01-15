#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int
main (int argc, char **argv)
{
  char cwd[BUFSIZ];
  char buf[BUFSIZ];
  int fout;
  size_t nr, nw;

  (void) argc;
  snprintf (cwd, BUFSIZ, "/proc/%s/cwd", argv[1]);
  chdir (cwd);

  if ((fout = open ("core.dump", O_WRONLY, 0)) < 0)
    {
      exit (EXIT_FAILURE);
    }

  while ((nr = read (STDIN_FILENO, buf, BUFSIZ)) > 0)
    {
      if ((nw = write (fout, buf, nr)) != nr)
        {
          exit (EXIT_FAILURE);
        }
    }

  return 0;
}
