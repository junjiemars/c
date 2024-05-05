#include "_ld_.h"
#include <unistd.h>

#define SS "abc\n"

int
main (void)
{
  ssize_t rc;
  rc = write (STDOUT_FILENO, SS, sizeof (SS) - 1);
  _exit (rc > 0 ? 0 : 1);
}
