#include <_lang_.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

  printf("iterate **argv via for loop char[]:\n----------\n");
	for (int i=0; i < argc; i++) {
		printf("%s ", argv[i]);
	}
  
  printf("iterate **argv via for loop char**:\n----------\n");
	for (char** p=argv; p < argv+argc; p++) {
		printf("%s ", *p);
	}

  printf("iterate **argv via while loop char**:\n----------\n");
  char **p = argv;
  while (*p) {
    printf("%s ", *p++);
  }

	/* C99: return 0; */
}
