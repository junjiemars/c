#include <nustd.h>
#include <BaseTsd.h>
#include <process.h>
#include <windows.h>
#include <stdio.h>

static void f (void);

int
main (void)
{
#if defined(has_attribute)
	printf ("defined has_attribute\n");
#endif
  int x = 0;
  switch (x)
    {
    case 0:
			__attribute__ ((fallthrough));
		case 1:
			f ();
			__attribute__ ((fallthrough));
		case 2:
			printf ("x=%d\n", x);
      break;
    }

  return 0;
}

void
f (void)
{
}
