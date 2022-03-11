#include "_data_.h"
#include <sys/utsname.h>


int
main(void)
{
  int             rc;
  struct utsname  un;

  rc = uname(&un);
  if (rc == -1)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }

  printf("sysname: %s\n"
         "nodename: %s\n"
         "release: %s\n"
         "version: %s\n"
         "machine: %s\n",
         un.sysname, un.nodename, un.release, un.version, un.machine);

  exit(EXIT_SUCCESS);
}
