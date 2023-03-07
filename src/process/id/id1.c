#include "_process_.h"

/*
 * `user/group id', `effective user/group id'
 *
 */

int
main(void)
{
  pid_t  pid;
  uid_t  uid, euid, gid, egid;

  pid = getpid();

  uid = getuid();
  euid = geteuid();
  gid = getgid();
  egid = getegid();

  printf("uid=%d, euid=%d, gid=%d, egid=%d, pid=%d\n",
         uid, euid, gid, egid, pid);

  exit(EXIT_SUCCESS);
}
