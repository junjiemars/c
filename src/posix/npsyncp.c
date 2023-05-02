#include <npsyn.h>

static int pfd1[2], pfd2[2];

int
need_wait (void)
{
  return pipe (pfd1) || pipe (pfd2);
}

int
tell_parent (__attribute__ ((unused)) pid_t pid)
{
  return write (pfd2[1], "c", 1) != 1;
}

int
tell_child (__attribute__ ((unused)) pid_t pid)
{
  return write (pfd1[1], "p", 1) != 1;
}

int
wait_parent (void)
{
  char c;
  if (read (pfd1[0], &c, 1) != 1)
    {
      return -1;
    }
  return c == 'p';
}

int
wait_child (void)
{
  char c;
  if (read (pfd2[0], &c, 1) != 1)
    {
      return -1;
    }
  return c == 'c';
}
