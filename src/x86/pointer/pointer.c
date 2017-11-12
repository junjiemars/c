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
  int *p;
  p = a; 
  *(p + 3) = 0x11;
  a[3] = 0x22;
}

void structure() {
  struct binky x;
  struct binky *p;
  struct binky **pp;
  p = &x;
  pp = &p;
  p->f = 6;
  (**pp).f = 7;
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