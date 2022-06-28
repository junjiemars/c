#include <stdio.h>

/* envp */
extern char  **environ;

/* initialized data segement */
int  ds1  =  0x11223344;
int  ds2  =  0x22334455;

/* initialized data segement: read only */
const  int  ds3  =  0x33445566;
const  int  ds4  =  0x44556677;

/* uninitialized data segment(bss): block started by symbol */
int  bss1[4];
int  bss2[4];

int
main(int argc, char **argv)
{
  /* stack */
  int auto1 = 0x55;
  int auto2 = 0x66;

  printf("%-24p envp=%s\n", &environ[0], environ[0]);
  printf("%-24p argv=%s\n", &argv[0], argv[0]);

  printf("%-24p auto2=%#x\n", &auto2, auto2);
  printf("%-24p auto1=%#x\n", &auto1, auto1);

  printf("%-24p ds2=%#x\n", &ds2, ds2);
  printf("%-24p ds1=%#x\n", &ds1, ds1);

  printf("%-24p ds4=%#x (readonly)\n", &ds4, ds4);
  printf("%-24p ds3=%#x (readonly)\n", &ds3, ds3);

  printf("%-24p bss2=%#x\n", &bss2[0], bss2[0]);
  printf("%-24p bss1=%#x\n", &bss1[0], bss1[0]);

  return 0;
}
