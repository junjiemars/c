#include <_lang_.h>
#include <stdio.h>
#include <stdlib.h>

void
on_exit(void) {
	printf("----------\n");
	printf("existing ...\n");
}

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);

  atexit(&on_exit);

  printf("_Exit() ...\n");

  _Exit(EXIT_SUCCESS);
}
