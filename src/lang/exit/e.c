#include <_lang_.h>
#include <stdio.h>
#include <stdlib.h>

void
on_exit_first(void) {
	printf("----------\n");
	printf("existing first ...\n");
}

void 
on_exit_second(void) {
	printf("----------\n");
	printf("existing second ...\n");
}

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);

  atexit(&on_exit_second);
  atexit(&on_exit_first);

  printf("calling exit() ...\n");
  exit(EXIT_SUCCESS);
}
