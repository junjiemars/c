#include <_lang_.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N  32

static void test_setenv(const char *name, const char *value);


void
test_setenv(const char *name, const char *value)
{
    int    rc;
    char  *env;
    char   new_value[N]  =  {0};
    char   new_env[N]    =  {0};
    
    rc = setenv(name, value, 0);
    if (rc) {
        perror(0);
        return;
    }
    env = getenv(name);
    printf("%s=%s\n", name, env);

    strcpy(new_value, value);
    strcat(new_value, "Zzz");
    rc = setenv(name, new_value, 1);
    if (rc) {
        perror(0);
        return;
    }
    printf("%s=%s\n", name, new_value);

    sprintf(new_env, "%s=%s123", name, new_value);
    rc = putenv(new_env);
    if (rc) {
        perror(0);
        return;
    }
    env = getenv(name);
    printf("%s=%s\n", name, env);

    rc = unsetenv(name);
    if (rc) {
        perror(0);
        return;
    }
    env = getenv(name);
    printf("%s=%s\n", name, env);
}

int 
main(int argc, const char **argv) 
{
    if (argc < 3) {
        fprintf(stderr, "please, input an env, such as NAME VALUE\n");
        return 1;
    }

    test_setenv(argv[1], argv[2]);

    return 0;
}
