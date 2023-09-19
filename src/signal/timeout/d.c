#include "_signal_.h"


extern ssize_t read1 (int, void *, size_t, int);

int
main (int argc, char **argv)
{
  ssize_t n;
  char buf[] = "______________|\n";
  int timeout = 1;

  if (argc > 1)
    {
      timeout = atoi (argv[1]);
    }
  printf ("%d, %d\n", getpid (), timeout);

  alarm (2);

  if ((n = read1 (STDIN_FILENO, buf, sizeof (buf) - 1, timeout)) == -1)
    {
      perror (NULL);
    }

  if (write (STDOUT_FILENO, buf, sizeof (buf) - 1) == -1)
    {
      perror (NULL);
    }

  exit (EXIT_SUCCESS);
}
