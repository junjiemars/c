#include "_signal_.h"

extern ssize_t read3 (int, void *, size_t, int);

int
main (int argc, char **argv)
{
  ssize_t n;
  char buf[] = "______________|\n";
  int timeout = 0;
  sigset_t oset1, oset2;

  if (argc > 1)
    {
      timeout = atoi (argv[1]);
    }
  printf ("pid=%d, timeout=%ds\n", getpid (), timeout);

  /* examine `read3' is alarm safe */
  /* alarm (2); */

  /* examine signal mask before call `read3' */
  sigprocmask (0, NULL, &oset1);

  n = read3 (STDIN_FILENO, buf, sizeof (buf) - 1, timeout);

  /* examine signal mask after call `read3' */
  sigprocmask (0, NULL, &oset2);
  assert (oset1 == oset2 && "should signal mask be restored");

  if (n == -1)
    {
      perror (NULL);
    }
  else if (n > 0)
    {
      write (STDOUT_FILENO, buf, sizeof (buf) - 1);
    }

  exit (0);
}
