#include <_lang_.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define N  32


static void test_putenv(char *env);


void
test_putenv(char *env)
{
    int   rc;
    char  name[N];
    
    rc = putenv(env);
    if (rc) {
        perror(0);
        return;
    }
    
    rc = sscanf(env, "%s=", &name[0]);
    if (1 == rc) {

    } else if (EOF == rc) {
        perror(0);
    }
}

int 
main(int argc, const char **argv) 
{
    const char  *env;

    if (argc < 1) {
        fprintf(stderr, "please, input an env, such as NAME=VALUE");
        return 1;
    }
    env = argv[1];

    test_putenv(env);
  
    return 0;
}
