#include <_lang_.h>


int
main(_unused_(int argc),
     _unused_(char **argv),
     _unused_(char **envp))
{
  char  **p  =  envp;

  printf("char **envp ...\n----------\n");
  while (*p)
    {
      printf("%s\n", *p++);
    }

  return 0;
}
