#include <_ld_.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
    if (argc > 1) {
        printf("echo: %s\n", argv[1]);

    } else {
        printf("w r u?\n");
    }

    return 0;
}
