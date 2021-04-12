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
    char  *new_value  =  0;
    char  *new_env    =  0;
    
    rc = setenv(name, value, 0);
    if (rc) {
        perror(0);
        return;
    }
    env = getenv(name);
    printf("%s=%s\n", name, env);

    new_value = malloc(N + 1);
    if (!new_value) {
        perror(0);
        goto clean_exit;
    }

    new_env = malloc(N + 1);
    if (!new_env) {
        perror(0);
        goto clean_exit;
    }

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
        goto clean_exit;
    }
    env = getenv(name);
    printf("%s=%s\n", name, env);

    rc = unsetenv(name);
    if (rc) {
        perror(0);
        goto clean_exit;
    }
    env = getenv(name);
    printf("%s=%s\n", name, env);
    
clean_exit:
    free(new_value);
    free(new_env);
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
