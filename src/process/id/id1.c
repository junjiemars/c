#include "_process_.h"

/*
 * `user/group id', `effective user/group id'
 *
 */

int
main(void)
{
  pid_t  pid, ppid;
  uid_t  uid, euid, gid, egid;

  pid = getpid();
  ppid = getppid();

  uid = getuid();
  euid = geteuid();
  gid = getgid();
  egid = getegid();

  printf("uid=%d, euid=%d, gid=%d, egid=%d, pid=%d, ppid=%d\n",
         uid, euid, gid, egid, pid, ppid);

  exit(EXIT_SUCCESS);
}
