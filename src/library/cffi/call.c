#include "cffix.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

#if (MSVC)
#  pragma warning(disable: 4996)
#endif

#define N  16

int
main(int argc, char **argv)
{
    int     d, i, n;
    char    s[N];
    size_t  len;
    
    if (argc < 2) {
        printf("input: <number>, '<string>'\n");
        return 0;
    }

    memset(&s[0], 0, N);
    n = sscanf(argv[1], "%d, %s", &d, s);
    if (EOF == n) {
        perror("!panic");
        return errno;
    }
  
    i = inc(d);
    len = str_len(s);
    printf("inc(%i) = %i, str_len(%s) = %zu\n", d, i, s, len);

    return 0;
}
