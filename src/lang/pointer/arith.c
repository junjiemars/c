#include "_lang_.h"

void test_null(int);

void
test_null(int c) {
  char *cp;
  cp = 0;
  cp = (char*) &c;
}

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);
  
  test_null('a'); 

  return 0;
}
