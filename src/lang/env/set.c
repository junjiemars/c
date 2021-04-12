#include <_lang_.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N  32

static void test_setenv(const char *name, const char *value);


void
test_setenv(const char *name, const char *value)
{
    int          rc;
    char        *env;
    char        *new_value  =  0;
    
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

    strcpy(&new_value[0], value);
    strcat(&new_value[0], "Zzz");
    rc = setenv(name, new_value, 1);
    if (rc) {
        perror(0);
        return;
    }

    printf("%s=%s\n", name, new_value);

clean_exit:
    free(new_value);
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
