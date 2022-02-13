#include <stdio.h>

#if defined(_WITH_EXIT_)
#include <stdlib.h>
#endif


/*
 * 1. c99: `main' must return int
 * 2. default exit status is 0
 * 3. start-up routine: exit(main(...));
 * 4. low-order 8 bits as status
 */


#if (_RETURN_INT_)
int
#else
void
#endif /* _RETURN_INT_ */

main(void)
{
  printf("boring\n");


#if (_WITH_RETURN_)
  return 0x1122;

#endif /* _WITH_RETURN_ */


#if (_WITH_EXIT_)
  exit(0x3344);

#endif /* _WITH_EXIT_ */


}
