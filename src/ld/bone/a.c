#include "_ld_.h"
#include <unistd.h>
#include <string.h>

void a(char *s)
{
  write(STDOUT_FILENO, s, strlen(s));
}
