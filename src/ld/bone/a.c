#include <_ld_.h>

void a(char *s)
{
  write(STDOUT_FILENO, s, strlen(s));
}
