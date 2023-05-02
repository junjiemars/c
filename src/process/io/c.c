#include "_process_.h"
#include <npsyn.h>

static void out (const char *ss);

int
main (void)
{
  pid_t pid;

#if (_SYN_)
  printf ("sync\n");
  need_wait ();
#else
  printf ("async\n");
#endif /* _SYN_ */

  if ((pid = fork ()) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  else if (pid == 0)
    {
      out ("# output from child\n");
#if (_SYN_)
      tell_parent (getppid ());
#endif /* _SYN_ */
    }

  else
    {
#if (_SYN_)
      wait_child ();
#endif /* _SYN_ */
      out ("# OUTPUT FROM PARENT\n");
    }

  exit (EXIT_SUCCESS);
}

static void
out (const char *ss)
{
  int c;
  const char *s;

  /* unbuffered */
  setbuf (stdout, NULL);

  for (s = ss; (c = *s++) != 0;)
    {
      usleep (100000); /* 1/10 second */
      putc (c, stdout);
    }
}
