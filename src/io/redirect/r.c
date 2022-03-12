#include "_io_.h"

int
main(void)
{
  char  out[]  =  "stdout output\n";
  char  err[]  =  "stderr output\n";

  write(STDOUT_FILENO, out, sizeof(out) - 1);
  write(STDERR_FILENO, err, sizeof(err) - 1);

  return 0;
}
