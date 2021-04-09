#include <_os_.h>
#include <stdio.h>


#if (LINUX)
#  include <unistd.h>
#endif  /* LINUX */


static void test_brk(void);


void
test_brk(void)
{
    int rc;
    
    rc = brk(0);
    if (rc) {
        perror(0);
        return;
    }
}

int
main(int argc, char **argv)
{
    _unused_(argc);
    _unused_(argv);

    test_brk();

    return 0;
}
