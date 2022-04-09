#include "_io_.h"

/*
 * Q1: d1 > f1 d2>&d1, shell process command line from left to right.
 * A1:
 * 1. dup2(f1, d1)
 * 2. dup2(d1, d2)
 * so fd(1) and fd(2) point to same f1's file table.
 *
 * Q2: d2>&d1 > f1
 * A2:
 * 1. dup2(d1, d2)
 * 2. dup2(f1, d1)
 * so fd(2) point to d1's file table and fd(1) point to f1's file table.
 *
 */


int
main(void)
{
  char  out[]  =  "stdout output\n";
  char  err[]  =  "stderr output\n";

  if (write(STDOUT_FILENO, out, sizeof(out)-1) != sizeof(out)-1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }


  if (write(STDERR_FILENO, err, sizeof(err)-1) != sizeof(out)-1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);

}
