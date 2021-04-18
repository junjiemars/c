#include <_lang_.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


int
main(int argc, char **argv)
{
    size_t        n, r;
    unsigned int  seed;

    if (argc < 3) {
        fprintf(stderr, "please input: <SEED>, <N>\n");
        return 1;
    }

    seed = (unsigned int) atoi(argv[1]);
    n = atoi(argv[2]);

    srand(seed);

    printf("raw random [%i, %zu)\n", 0, n);
    printf("--------------------\n");

    for (size_t i = 0; i < n; i++) {
        r = rand() % n;
        printf("%zu ", r);
    }
    putchar('\n');

    return 0;
}
