#include <_ld_.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


extern void *__real_malloc(size_t size);

void *__wrap_malloc(size_t size);



void *
__wrap_malloc(size_t size)
{
  printf("enter __wrap_malloc ...\n");
  return __real_malloc(size);
}

int
main(int argc, char **argv)
{
  char *ss;

  ss = malloc(strlen(argv[0]) + 1);
  if (!ss) {
    perror(NULL);
    goto clean_exit;
  }

  if (argc < 2) {
    strcpy(ss, argv[0]);
    
  } else {
    strcpy(ss, argv[1]);
  }

  printf("copied: %s\n", ss);

 clean_exit:
  free(ss);

  return 0;
}
