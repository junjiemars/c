#include <_lang_.h>
#include <stdio.h>
#include <stdlib.h>

#if (LINUX) || (DARWIN)
#  include <unistd.h>
#endif

static void on_exit(void);

void
on_exit(void)
{
    printf("----------\n");
    printf("existing ...\n");
}

int
main(void)
{
    atexit(&on_exit);
    
    printf("calling exit() ...\n");
    _exit(EXIT_SUCCESS);

    return 0;
}
