#include <_x86_.h>


void
dereference() {
  int i;
  int *p;
  p = &i;
  *(char *)p = 'A';
}

void
average() {
  int total = 0x1122, count = 0x3344;
  float average;
  average = (float)total/(float)count;
}

void
pointer_to_int() {
  char c;
  int *p;
  p = (int *)&c;
  *p = (int)p;
}

void 
int_to_pointer() {
  int i;
  i = 0x11223344;

#ifdef RISKY
  ((struct binky *)i)->b = 'A';
#endif
}


int
main(int argc, const char *argv[]) {
  _unused_(argc);
  _unused_(argv);

  dereference();
  average();
  pointer_to_int();
  int_to_pointer();
}
