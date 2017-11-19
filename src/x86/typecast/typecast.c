#include <_x86_.h>


void
pointer1() {
  int i;
  int *p = &i;
  *(char *)p = 'A';
}

void
average() {
  int total = 0x1122, count = 0x3344;
  float average;
  average = (float)total/(float)count;
}

void
pointer2() {
  char c;
  int *p;
  p = (int *)&c;
  *p = (int)p;
}


int
main(int argc, const char *argv[]) {
  _unused_(argc);
  _unused_(argv);

  pointer1();
  average();
  pointer2();
}
