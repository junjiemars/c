#include "_env_.h"
#include <stdlib.h>
#include <stdio.h>

extern char **environ;

int
main(int argc, char **argv)
{
    _unused_(argc);
    _unused_(argv);

    printf("environ at 0x%zx\n----------\n", (unsigned long) environ);

    while (*environ++) {
        printf("%s\n", *environ);
    }

    return 0;
}
