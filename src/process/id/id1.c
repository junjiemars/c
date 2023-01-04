#include "_process_.h"

/*
 * `user id', `effective user id', `saved user id'.
 *
 */

int
main(void)
{
  uid_t  uid, euid;
  pid_t  pid;

  uid = getuid();
  euid = geteuid();

  pid = getpid();

  printf("uid=%d, euid=%d, pid=%d\n", uid, euid, pid);

  exit(EXIT_SUCCESS);
}
