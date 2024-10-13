#include "_unix_.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

/* /var/run/d1.pid */
#if !defined(D_LOCK_FILE)
#define D_LOCK_FILE "d1.pid"
#endif /* D_LOCK_FILE */
#define D_LOCK_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

/* /etc/d1.conf */
#if !defined(D_CONF_FILE)
#define D_CONF_FILE "d1.conf"
#endif /* D_CONF_FILE */

int lockfile (int);
int running (void);

int
main (void)
{
  int rc;

  rc = running ();

  return 0;
}

int
lockfile (int fd)
{
  struct flock flck = {
    .l_type = F_WRLCK,
    .l_start = 0,
    .l_whence = SEEK_SET,
    .l_len = 0,
  };
  return fcntl (fd, F_SETLK, &flck);
}

int
running (void)
{
  int fd;
  char buf[sizeof (long) * 2];

  fd = open (D_LOCK_FILE, O_RDWR | O_CREAT, D_LOCK_MODE);
  if (fd < 0)
    {
      syslog (LOG_ERR, "!panic, open %s: %s", D_LOCK_FILE, strerror (errno));
      exit (EXIT_SUCCESS);
    }

  if (lockfile (fd) < 0)
    {
      if (errno == EACCES | errno == EAGAIN)
        {
          close (fd);
          return 1;
        }
      syslog (LOG_ERR, "!panic, lock %s: %s", D_LOCK_FILE, strerror (errno));
      exit (EXIT_FAILURE);
    }

  ftruncate (fd, 0);
  sprintf (buf, "%ld", (long)getpid ());
  write (fd, buf, strnlen (buf, sizeof (buf)) + 1);
  return 0;
}
