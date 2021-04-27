#include <_ld_.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/fs.h>

#if (LINUX)
#include <unistd.h>
extern char **environ;
#endif

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
