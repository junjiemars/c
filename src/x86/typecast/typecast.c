#include <_x86_.h>


void
dereference()
{
  int i;
  int *p;
  p = &i;
  *(char *)p = 'A';
}

void
average()
{
  int total = 0x1122, count = 0x3344;
  float average;
  average = (float)total/(float)count;
}

void
pointer_to_int()
{
  char c;
  int *p;
  p = (int *)&c;

#if defined (RISKY) && (RISKY) > 0

  *p = (int)p;

#endif
}

void 
int_to_pointer()
{
  int i;
  i = 0x11223344;

#if defined (RISKY) && (RISKY) > 0

  ((struct binky *)i)->b = 'A';

#endif
}


int
main(void)
{
  dereference();
  average();
  pointer_to_int();
  int_to_pointer();
}
