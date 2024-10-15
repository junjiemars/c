#include "_unix_.h"
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/resource.h>
#include <sys/signal.h>
#include <sys/stat.h>
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
void daemonize (const char *);
void on_sigterm (int);
void on_sighup (int);

int
main (int __attribute__ ((unused)) argc, char **argv)
{
  char *cmd;
  struct sigaction sa;

  /* command name */
  if ((cmd = strrchr (argv[0], '/')) == NULL)
    cmd = argv[0];
  else
    cmd++;

  openlog (cmd, LOG_CONS, LOG_DAEMON);

  daemonize (cmd);

  if (running ())
    {
      syslog (LOG_ERR, "!panic, %s", "daemon alreay running");
      exit (1);
    }

  sa.sa_handler = on_sigterm;
  sigemptyset (&sa.sa_mask);
  sigaddset (&sa.sa_mask, SIGHUP);
  if (sigaction (SIGTERM, &sa, NULL) < 0)
    {
      syslog (LOG_ERR, "!panic, sigaction: %m");
      exit (1);
    }

  sa.sa_handler = SIGHUP;
  sigemptyset (&sa.sa_mask);
  sigaddset (&sa.sa_mask, SIGTERM);
  sa.sa_flags = 0;
  if (sigaction (SIGHUP, &sa, NULL) < 0)
    {
      syslog (LOG_ERR, "!panic, sigaction: %m");
      exit (1);
    }

  exit (0);
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

void
daemonize (const char *cmd)
{
  pid_t pid;
  rlim_t i;
  int fd0, fd1, fd2;
  struct rlimit no_file;
  struct sigaction sa;

  umask (0);

  if (getrlimit (RLIMIT_NOFILE, &no_file) < 0)
    {
      syslog (LOG_ERR, "!panic, getrlmit: %m");
      exit (1);
    }

  if ((pid = fork ()) < 0)
    {
      syslog (LOG_ERR, "!panic, fork: %m");
      exit (1);
    }
  else if (pid != 0)
    exit (0);

  setsid ();

  sa.sa_handler = SIG_IGN;
  sigemptyset (&sa.sa_mask);
  sa.sa_flags = 0;
  if (sigaction (SIGHUP, &sa, NULL) < 0)
    {
      syslog (LOG_ERR, "!panic, sigaction: %m");
      exit (1);
    }

  if ((pid = fork ()) < 0)
    {
      syslog (LOG_ERR, "!panic, fork: %m");
      exit (1);
    }
  else if (pid != 0)
    exit (0);

  if (chdir ("/") < 0)
    {
      syslog (LOG_ERR, "!panic, chdir: %m");
      exit (1);
    }

  if (no_file.rlim_max == RLIM_INFINITY)
    no_file.rlim_max = 64;
  for (i = 0; i < no_file.rlim_max; i++)
    close (i);

  fd0 = open ("/dev/null", O_RDWR);
  fd1 = dup (0);
  fd2 = dup (0);

  if (fd0 != 0 || fd1 != 1 || fd2 != 2)
    {
      syslog (LOG_ERR, "!panic, %s: %s, %d, %d, %d", cmd, "unexpected fildes",
              fd0, fd1, fd2);
      exit (1);
    }
}

void
on_sigterm (int signo)
{
  syslog (LOG_INFO, "on_sigterm: %d", signo);
  exit (0);
}

void
on_sighup (int signo)
{
  syslog (LOG_INFO, "on_sighup: %d", signo);
  /* !TODO: reread configuration */
}
