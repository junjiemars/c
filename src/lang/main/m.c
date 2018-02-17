#include <_lang_.h>
#include <stdio.h>
#include <stdlib.h>


void
on_exit(void) {
	printf("----------\n");
	printf("exiting...\n");
}


int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	atexit(&on_exit);

  printf("iterate **argv via for loop char[]:\n");
  printf("----------\n");
	for (int i=0; i < argc; i++) {
		printf("%s ", argv[i]);
	}
  printf("\n\n");
  
  printf("iterate **argv via for loop char**:\n");
  printf("----------\n");
	for (char** p=argv; p < argv+argc; p++) {
		printf("%s ", *p);
	}
  printf("\n\n");


  printf("iterate **argv via while loop char**:\n");
  printf("----------\n");
  char **p = argv;
  while (*p) {
    printf("%s ", *p++);
  }
  printf("\n\n");

	/* C99: return 0; */
}
