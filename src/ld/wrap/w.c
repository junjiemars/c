#include <_ld_.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


extern void *__real_malloc(size_t size);
extern void __real_free(void *ptr);

void *__wrap_malloc(size_t size);
void __wrap_free(void *ptr);


void *
__wrap_malloc(size_t size)
{
  printf("enter __wrap_malloc ...\n");
  return __real_malloc(size);
}

void
__wrap_free(void *ptr) {
  printf("enter __wrap_free ...\n");
  __real_free(ptr);
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
  __wrap_free(ss);

  return 0;
}
