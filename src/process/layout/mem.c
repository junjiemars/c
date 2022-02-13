#include <stdio.h>


/* initialized data segement */
int ds1 = 0x11223344;

/* uninitialized data segment(bss): block started by symbol */
int bss1[4];

int
main(void)
{
  /* stack */
  int auto1 = 0x55;

  printf("ds1 = %d, bss = %d, auto = %d\n", ds1, bss1[0], auto1);
  return 0;
}
