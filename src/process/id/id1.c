#include "_process_.h"

int
main(void)
{
  uid_t  uid;
  gid_t  gid;
  pid_t  pid;

  uid = getuid();
  gid = getgid();
  pid = getpid();

  printf("uid = %d, gid = %d, pid = %d\n", uid, gid, pid);

  exit(EXIT_SUCCESS);
}
