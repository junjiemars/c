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
static void test_strndup(strndup_fn fn, const char *s);


char *
self_strdup(const char *s)
{
    char    *s1;
    size_t   n;

    n = strlen(s);

    s1 = malloc(n + 1);
    if (s1) {
        memcpy(s1, s, n);
        s1[n] = 0;
        return s1;
    }

    return 0;
}

char *
self_strndup(const char *s, size_t n)
{
    char  *s1;

    s1 = malloc(n + 1);
    if (s1) {
        memcpy(s1, s, n);
        s1[n] = 0;
        return s1;
    }

    return 0;
}

void
test_strdup(strdup_fn fn, const char *s)
{
    char  *s1;

    s1 = fn(s);
    if (!s1) {
        perror(0);
        return;
    }

    printf("dup: %s\n", s1);
    free(s1);
}

void
test_strndup(strndup_fn fn, const char *s)
{
    char    *eq, *gt, *lt;
    size_t   n;

    n = strlen(s);

    eq = fn(s, n);
    if (!eq) {
        perror(0);
        return;
    }
    ASSERT(0 == memcmp(s, eq, n));
    printf("ndup: %s\n", eq);
    free(eq);

    lt = fn(s, n - 1);
    if (!lt) {
        perror(0);
        return;
    }
    ASSERT(0 == memcmp(s, lt, n - 1));
    printf("ndup: %s\n", lt);
    free(lt);

    gt = fn(s, n + 1);
    if (!gt) {
        perror(0);
        return;
    }
    ASSERT(0 == memcmp(s, gt, n + 1));
    printf("ndup: %s\n", gt);
    free(gt);
}

int
main(int argc, char **argv)
{
    const char  *s  =  0;

    if (argc < 2) {
        printf("what the source string to dup\n");
        return 0;
    }

    s = argv[1];


#if (NM_HAVE_STRDUP)
    test_strdup(strdup, s);

#endif  /* NM_HAVE_STRDUP */

    test_strdup(self_strdup, s);

#if (NM_HAVE_STRNDUP)
    test_strndup(strndup, s);

#endif  /* NM_HAVE_STRNDUP */

    test_strndup(self_strndup, s);

    return 0;
}
