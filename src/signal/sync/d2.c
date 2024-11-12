#include "psync.h"
#include <_signal_.h>

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

  if ((file = fopen (argv[1], "rw")) == NULL)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  fprintf (stderr, "%d\n", getpid ());

  tell_wait ();

  if ((pid = fork ()) == -1)
    {
      perror (NULL);
      exit (1);
    }
  else if (pid == 0) /* child process */
    {
      fsync (fileno (file));
      fscanf (file, "%i", &counter);

      tell_parent (getppid ());
      fprintf (stderr, "--- %d read %02d\n", getpid (), counter);

      wait_parent ();

      ++counter;
      fwrite ((int *)&counter, sizeof (counter), 1, file);
      fsync (fileno (file));

      tell_parent (getppid ());
      fprintf (stderr, "--- %d wrote %02d\n", getpid (), counter);

      tell_parent (getppid ());
      wait_parent ();
    }
  else
    {
      ++counter;
      fwrite ((int *)&counter, sizeof (counter), 1, file);
      fsync (fileno (file));

      tell_child (pid);
      fprintf (stderr, "+++ %d wrote %02d\n", getpid (), counter);

      wait_child ();

      fsync (fileno (file));
      fscanf (file, "%i", &counter);

      tell_child (pid);
      fprintf (stderr, "+++ %d read %02d\n", getpid (), counter);

      wait_child ();
    }

  fclose (file);
  fsync (fileno (file));

  return 0;
}
