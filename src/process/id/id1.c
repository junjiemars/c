#include "_process_.h"

int
main(void)
{
  uid_t  uid, euid;
  gid_t  gid;
  pid_t  pid;

  uid = getuid();
  euid = geteuid();

  gid = getgid();
  pid = getpid();

  printf("uid=%d, euid=%d, gid=%d, pid=%d\n", uid, euid, gid, pid);

  exit(EXIT_SUCCESS);
}
