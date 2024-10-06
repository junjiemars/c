#include "_unix_.h"
#include <tcpd.h>

int
main (int argc, char **argv)
{
  _unused_ (argc);
  _unused_ (argv);

  hosts_access (0);

  return 0;
}
