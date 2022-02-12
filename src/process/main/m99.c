#include <stdio.h>

#if defined(_WITH_EXIT_)
#include <stdlib.h>
#endif


/*
 * 1. c99: `main' must return int
 * 2. default exit status is 0
 * 3. exit(main(...));
 *
 */


#if defined(_RETURN_INT_)
int
#else
void
#endif /* _RETURN_INT_ */

main(void)
{
  printf("boring\n");

#if defined(_WITH_RETURN_)
  return 0;
#endif /* _WITH_RETURN_ */

#if defined(_WITH_EXIT_)
  exit(0);

#endif /* _WITH_EXIT_ */


}
