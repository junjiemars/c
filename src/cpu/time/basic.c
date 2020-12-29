#include "_cpu_.h"
#include <stdio.h>

#if defined(WINNT)
#  include <windows.h>
#  define sleep(x) Sleep((x) * 1000)
#else
#  include <unistd.h>
#endif

int
main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "how much seconds to sleep?\n");
    return 0;
  }

  int s;
  sscanf(argv[1], "%i", &s);
  sleep(s);
  
  return 0;
}
