#include <_ld_.h>

size_t strlen1(const char*);

int
main(void)
{
  static char *ss = "Hi, ASM\n";

  write(STDOUT_FILENO, ss, strlen1(ss));

  return 0;
}

size_t
strlen1(const char *ss)
{
  size_t  n  =  0;

  while (*ss++)
    {
      n++;
    }

  return n;
}
