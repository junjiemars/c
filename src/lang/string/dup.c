#include <_lang_.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *(*strdup_fn)(const char *s);
typedef char *(*strndup_fn)(const char *s, size_t n);

static char *self_strdup(const char *s);
static char *self_strndup(const char *s, size_t n);

static void test_strdup(strdup_fn fn, const char *s);
static void test_strndup(strndup_fn fn, const char *s, size_t n);

char *
self_strdup(const char *s)
{
    char *s1;

    s1 = malloc(strlen(s) + 1);
    if (s1) {
        strcpy(s1, s);
        return s1;
    }

    return 0;
}

char *
self_strndup(const char *s, size_t n)
{
    char *s1;

    s1 = malloc(n+1);
    if (s1) {
        strncpy(s1, s, n);
        s1[n] = 0;
        return s1;
    }

    return 0;
}

void
test_strdup(strdup_fn fn, const char *s)
{
    char *s1;
    s1 = fn(s);
    if (!s1)
    {
        perror(0);
        return;
    }
    printf("dup: %s\n", s1);
    free(s1);
}

void
test_strndup(strndup_fn fn, const char *s, size_t n)
{
    char *s1;

    s1 = fn(s, n);
    if (!s1) {
        perror(0);
        return;
    }

    printf("ndup: %s\n", s1);
    free(s1);
}

int
main(int argc, char **argv)
{
    const char *s = argv[1];    

    if (argc < 2) {
        printf("what the source string to dup\n");
        return 0;
    }


#if (NM_HAVE_STRDUP)
    test_strdup(strdup, s);

#endif  /* end of NM_HAVE_STRDUP */

#if (NM_HAVE_STRNDUP)
    test_strndup(strndup, s, 5);

#endif  /* end of NM_HAVE_STRNDUP */

    test_strdup(self_strdup, s);
    test_strndup(self_strndup, s, 5);

    return 0;
}
