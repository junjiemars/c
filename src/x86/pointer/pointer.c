#include <_x86_.h>

void
dereference() {
  int i;
  int *ptr;
  ptr = &i;
  *ptr = 0x22;
}

void
address() {
  int i;
  int *s;
  i = 0x11223344;
  s = &i;
  s++;
}

void array() {
  int a[] = { 1,2,3,4,5,6,7,8,9, };
  *(a + 3) = 0x33;
  a[2] = 0x22;
  *a = 0x00;
  *(a + 8) = 0x88;
}

void structure() {
  struct binky x;
  struct binky *p;
  struct binky **pp;
  p = &x;
  pp = &p;
  p->f = 0x0f;
  (**pp).f = 0xff;
}


int 
main(int argc, const char *argv[]) {
  _unused_(argc);
  _unused_(argv);

  dereference();
  address();
  array();
  structure();
}