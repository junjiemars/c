#include <_lang_.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


typedef char *(*strcat_fn)(char *s1, const char *s2);

static char *self_strcat(char *s1, const char *s2);

static void test_strcat(strcat_fn, char *s1, const char *s2);


void
test_strcat(strcat_fn fn, char *s1, const char *s2)
{
    char *ss;

    ss = fn(s1, s2);
    fprintf(stdout, "%s\n", ss);
}

char *
self_strcat(char *s1, const char *s2)
{
    char *ss;

    ss = strchr(s1, 0);
    strcpy(ss, s2);
    
    return s1;
}


int
main(int argc, char **argv)
{
    char    *s1  =  0, *s2 = 0;
    size_t   s1_len, s2_len;

    if (argc < 3) {
        printf("!panic, concate s2 to s1.\n");
        return 0;
    }

    s1_len = strlen(argv[1]);
    s2_len = strlen(argv[2]);
    
    s1 = malloc(s1_len + s2_len + 1);
    if (!s1) {
        perror(s1);
        goto clean_exit;
    }
    s2 = malloc(s2_len + 1);
    if (!s2) {
        perror(s2);
        goto clean_exit;
    }

    strcpy(s1, argv[1]);
    strcpy(s2, argv[2]);
    test_strcat(strcat, s1, s2);

    strcpy(s1, argv[1]);
    strcpy(s2, argv[2]);
    test_strcat(self_strcat, s1, s2);
    
clean_exit:
    free(s1);
    free(s2);

    return 0;
}
