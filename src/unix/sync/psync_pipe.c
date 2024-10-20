#include "psync.h"
#include <errno.h>
#include <nore.h>
#include <sys/errno.h>

static int p_fds[2], c_fds[2];

int
tell_wait (void)
{
  if (pipe (p_fds) < 0 || pipe (c_fds) < 0)
    {
      return errno;
    }
  return 0;
}

int tell_parent (pid_t __attribute__ ((unused)) pid)
{
  if (write (c_fds[1], "c", 1) != 1)
    return errno;
  return 0;
}

int
wait_parent (void)
{
  char c;
  if (read (p_fds[0], &c, 1) != 1)
    return errno;
  if (c != 'p')
    return EINVAL;
  return 0;
}

int
tell_child (pid_t __attribute__ ((unused)) pid)
{
  if (write (p_fds[1], "p", 1) != 1)
    return errno;
  return 0;
}

int
wait_child (void)
{
  char c;
  if (read (c_fds[0], &c, 1) != 1)
    return errno;
  if (c != 'c')
    return EINVAL;
  return 0;
}
