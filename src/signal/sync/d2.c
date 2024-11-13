#include "psync.h"
#include <_signal_.h>
#include <stdio.h>

#define N 3
static volatile int counter = 0;

int
main (int argc, char **argv)
{
  pid_t pid;
  FILE *file;

  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <path>\n", argv[0]);
      exit (EXIT_FAILURE);
    }
  fprintf (stderr, "%d\n", getpid ());

  if ((file = fopen (argv[1], "w+b")) == NULL)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  setvbuf (file, 0, _IONBF, 0);
  fwrite ((int *)&counter, sizeof (counter), 1, file);

  tell_wait ();

  if ((pid = fork ()) == -1)
    {
      perror (NULL);
      exit (1);
    }
  else if (pid == 0) /* child process */
    {
      for (int i = 0; i < N; i++)
        {
          fseek (file, 0, SEEK_SET);
          fread ((int *)&counter, sizeof (counter), 1, file);
          ++counter;
          fseek (file, 0, SEEK_SET);
          fwrite ((int *)&counter, sizeof (counter), 1, file);
          fprintf (stderr, "--- %8d %02d\n", getpid (), counter);

          tell_parent (getppid ());
          wait_parent ();
        }
    }
  else
    {
      for (int i = 0; i < N; i++)
        {
          tell_child (pid);
          wait_child ();

          fseek (file, 0, SEEK_SET);
          fread ((int *)&counter, sizeof (counter), 1, file);
          ++counter;
          fseek (file, 0, SEEK_SET);
          fwrite ((int *)&counter, sizeof (counter), 1, file);
          fprintf (stderr, "+++ %8d %02d\n", getpid (), counter);
        }
    }

  fclose (file);

  return 0;
}
