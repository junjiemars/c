#include <_link_.h>
/* #include <Mach-o/nlist.h> */

int
main(int argc, char **argv)
{
    _unused_(argc);
    _unused_(argv);
    
    int           rc;
    struct nlist  n  =  {0};

    rc = nlist("x", &n);

    return 0;
}
