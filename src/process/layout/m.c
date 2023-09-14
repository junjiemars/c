#include <stdio.h>
#include <stdlib.h>

/* envp */
extern char **environ;

/* initialized data segement */
int ds1 = 0x11223344;
int ds2 = 0x22334455;

/* initialized data segement: read only */
const int ds3 = 0x33445566;
const int ds4 = 0x44556677;

/* uninitialized data segment(bss): block started by symbol */
int bss1[4];
int bss2[4];

int
main (int argc, char **argv)
{
  /* stack */
  int auto1 = 0x55;
  int auto2 = 0x66;
  int *heap1 = NULL;
  int *heap2 = NULL;

  printf ("%-24p envp=%s\n", environ, environ[0]);
  printf ("%-24p argv=%s\n", argv, argv[0]);
  printf ("%-24p argc=%d\n", &argc, argc);

  printf ("%-24p auto1=%#x\n", &auto1, auto1);
  printf ("%-24p auto2=%#x\n", &auto2, auto2);

  heap1 = malloc (sizeof (int));
  heap2 = malloc (sizeof (int));
  *heap1 = 0x11;
  *heap2 = 0x22;

  printf ("%-24p heap2=%#x\n", heap2, *heap2);
  printf ("%-24p heap1=%#x\n", heap1, *heap1);

  printf ("%-24p bss2=%#x\n", bss2, bss2[0]);
  printf ("%-24p bss1=%#x\n", bss1, bss1[0]);

  printf ("%-24p ds2=%#x\n", &ds2, ds2);
  printf ("%-24p ds1=%#x\n", &ds1, ds1);

  printf ("%-24p ds4=%#x (readonly)\n", &ds4, ds4);
  printf ("%-24p ds3=%#x (readonly)\n", &ds3, ds3);

  printf ("%-24p main (text)\n", main);

  free (heap1);
  free (heap2);

  return 0;
}
