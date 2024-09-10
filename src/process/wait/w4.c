#include "_process_.h"
#include <stdlib.h>
#include <sys/wait.h>

int
main (void)
{
  pid_t pid;
  int state;
  struct rusage ru;

  if ((pid = fork ()) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  else if (pid == 0)
    {
      int n = 0;
      for (int i = 0; i < 10000; i++)
        {
          n += 1;
        }
      printf ("child: pid=%d, n=%d\n", getpid (), n);
      exit (0x11223344);
    }

  if (wait4 (pid, &state, 0, &ru) == -1)
    {
      perror (0);
      exit (EXIT_FAILURE);
    }
  if (WIFEXITED (state))
    {
      state = WEXITSTATUS (state);
    }
  else if (WIFSIGNALED (state))
    {
      state = WTERMSIG (state);
    }

  printf ("state: 0x%x\n"
          "rusage:\n"
          "{\n"
          "  ru_utime: { tv_sec: %ld, tv_usec: %ld },\n"
          "  ru_stime: { tv_sec: %ld, tv_usec: %ld },\n"
          "  ru_maxrss: %ld,\n"
          "  ru_nsignal: %ld\n"
          "}\n",
          state, ru.ru_utime.tv_sec, (long)ru.ru_utime.tv_usec,
          ru.ru_stime.tv_sec, (long)ru.ru_stime.tv_usec, ru.ru_maxrss,
          ru.ru_nsignals);

  exit (EXIT_SUCCESS);
}
