#include "_process_.h"

int
main (void)
{
  pid_t pid;
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
      exit (EXIT_SUCCESS);
    }

  if (wait4 (pid, NULL, 0, &ru) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  printf ("rusage:\n"
          "{\n"
          "  ru_utime: { tv_sec: %ld, tv_usec: %ld },\n"
          "  ru_stime: { tv_sec: %ld, tv_usec: %ld },\n"
          "  ru_maxrss: %ld,\n"
          "  ru_nsignal: %ld\n"
          "}\n",
          ru.ru_utime.tv_sec, ru.ru_utime.tv_usec, ru.ru_stime.tv_sec,
          ru.ru_stime.tv_usec, ru.ru_maxrss, ru.ru_nsignals);

  exit (EXIT_SUCCESS);
}
