#include <_lang_.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


static void test_setenv(const char *name, const char *value, int overwrite);


void
test_setenv(const char *name, const char *value, int overwrite)
{
    int    rc;
    char  *var;
    
    rc = setenv(name, value, overwrite);
    if (rc) {
        perror(0);
        return;
    }

    var = getenv(name);
    printf("%s=%s\n", name, var);
}

int 
main(int argc, const char **argv) 
{
    const char  *name, *value;

    if (argc < 3) {
        fprintf(stderr, "please, input an env, such as NAME VALUE\n");
        return 1;
    }

    name = argv[1];
    value = argv[2];

    test_setenv(name, value, 0);
  
    return 0;
}
