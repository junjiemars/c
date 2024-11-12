#include "psync.h"
#include <_signal_.h>

int
main (void)
{
  pid_t pid;

  setvbuf (stdout, 0, _IONBF, 0);
  tell_wait ();

  if ((pid = fork ()) == -1)
    {
      perror (NULL);
      exit (1);
    }
  else if (pid == 0) /* child process */
    {
      printf ("# child=%0d waiting parent ...\n", getpid ());

      wait_parent ();

      printf ("# child=%0d waited parent\n", getpid ());

      printf ("# child=%0d tell parent\n", getpid ());

      tell_parent (getppid ());
    }
  else
    {
      printf ("# parent=%0d tell child\n", getpid ());

      tell_child (pid);

      printf ("# parent=%0d waiting child ...\n", getpid ());

      wait_child ();

      printf ("# parent=%0d waited child\n", getpid ());
    }
  return 0;
}
