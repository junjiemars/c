#include "_lang_.h"
#include <time.h>
#include <stdio.h>

char*
to_asctime(const time_t *epoch) {
  char *c = ctime(epoch);
  return c;
}

int
main(int argc, char **argv) {
  if (argc < 2) {
    return 0;
  }
  time_t epoch;
  sscanf(argv[1], "%lu", (unsigned long*)&epoch);
  printf("%s", to_asctime(&epoch));

  return 0;
}
