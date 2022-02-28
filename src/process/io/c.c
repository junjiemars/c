#include "_process_.h"
#include <stdio.h>

static void char_attime(const char *ss);

int
main(void)
{
  pid_t pid;

  pid = fork();
  if (pid == -1)
    {
      perror("!panic:");
      return 1;
    }

  if (pid == 0)
    {
      char_attime("output from child\n");
    }
  else
    {
      char_attime("output from parent\n");
    }

  return 0;
}

static void
char_attime(const char *ss)
{
  int    c;
  const char  *s;

  setbuf(stdout, NULL);

  for (s = ss; (c = *s++) != 0;)
    {
      putc(c, stdout);
    }
}
