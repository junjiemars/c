#include "_ld_.h"
#include <unistd.h>

#define ss "enter start ...\n"

int
main (void)
{
  ssize_t n;
  n = write (STDOUT_FILENO, ss, sizeof (ss) - 1);
  if (n == -1)
    {
      _exit (1);
    }
  _exit (0);
}

void
_start ()
{
#if __x86_64__
  __asm("mov $0, %rbx\n"
        "leaq 8(%rsp), %rdi\n"
        "call _main\n"
        "mov %eax, %edi\n"
        "call _exit\n");
#endif
}
