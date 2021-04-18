#include <_lang_.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <limits.h>


#if (NM_HAVE_ARC4RANDOM_UNIFORM) || (NM_HAVE_CRT_RAND_S)
#  define NM_HAVE_RAND_S 1
#endif


#if (NM_HAVE_CRT_RAND_S)
#  define _CRT_RAND_S
#endif  /* NM_HAVE_CRT_RAND_S */


#include <stdlib.h>


static unsigned int __rand_s(unsigned int *u);


unsigned int
__rand_s(unsigned int *u)
{
#if (NM_HAVE_ARC4RANDOM_UNIFORM)
    return arc4random_uniform(*u);

#endif  /* NM_HAVE_ARC4RANDOM_UNIFORM */


#if (NM_HAVE_CRT_RAND_S)
    (error_t) rand_s(u);
    return *u;

#endif  /* NM_HAVE_RAND_S */ 

    return (unsigned int) 0;
}


int
main(int argc, char **argv)
{
    size_t        n;
    unsigned int  u = 10, r;

    if (argc < 2) {
        fprintf(stderr, "please input: <N>\n");
        return 1;
    }

    n = atoi(argv[1]);


#if (NM_HAVE_RAND_S)

    printf("raw random [%i, %zu)\n", 0, (size_t) u);
    printf("--------------------\n");

    for (size_t i = 0; i < n; i++) {
        r = __rand_s(&u);
        printf("%i ", r);
    }
    putchar('\n');


#endif  /* NM_HAVE_RAND_S */
	
    return 0;
}
