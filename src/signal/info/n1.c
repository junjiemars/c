#include <_signal_.h>
#include <ctype.h>

#define N  16

static void strupper(const char*, char*);

extern const char * const  sys_siglist[];
extern const char * const  sys_signame[];


int
main(void)
{
  char  name[N];

  for (unsigned i = 1; i < NSIG; i++)
    {
      strupper(sys_signame[i], name);
      printf("%-16s: %s\n", name, sys_siglist[i]);
    }

  exit(EXIT_SUCCESS);
}

void
strupper(const char *s, char *u)
{
  while ((*u++ = (char) toupper(*s++)) != 0)
    {
      /* void */
    }
}
