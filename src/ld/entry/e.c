#include <_ld_.h>


extern char **environ;


void
entry(void)
{
    printf("enter the entry ...\n");
    /* char **p = environ; */

    /* while (*p) { */
    /*     printf("%s\n", *p++); */
    /* } */

    /* _unused_(envp); */
    /* if (argc > 1) { */
    /*     printf("enter the entry: %s\n", argv[1]); */

    /* } else { */
    /*     printf("enter the entry ...\n"); */
    /* } */

    exit(0);
}
