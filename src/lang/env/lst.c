#include "_env_.h"
#include <stdlib.h>
#include <stdio.h>

extern char **environ;

int
main(int argc, char **argv)
{
    _unused_(argc);
    _unused_(argv);

    printf("environ at 0x%p\n----------\n", (void *) environ);

    for (char *p = *environ; p; p = *++environ) {
        printf("%s\n", *environ);
    }

    return 0;
}
