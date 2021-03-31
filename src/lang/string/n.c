#include <_lang_.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef size_t (*strnlen_fn)(const char *src, size_t n);
typedef char *(*strncpy_fn)(char *dst, const char *src, size_t n);
typedef int (*strncmp_fn)(const char *s1, const char *s2, size_t n);


static size_t self_strnlen(const char *src, size_t len);
static char *self_strncpy(char *dst, const char *src, size_t len);


static void test_strnlen(strnlen_fn fn, const char *src);
static void test_strncpy(strncpy_fn fn, char *src);
static void test_strncmp(strncmp_fn fn, const char *s1, const char *s2);

static void fill_str(char *dst, char c, size_t n);

size_t
self_strnlen(const char *s, size_t n)
{
    size_t  len  =  0;

    while (*s++ && n--) {
        len++;
    }

    return len;
}

char *
self_strncpy(char *dst, const char *src, size_t n)
{
    char  *p  =  dst;

    while (n-- && (0 != (*p++ = *src++))) {
        /* void */
    }

    return dst;
}

int
self_strncmp(const char *s1, const char *s2, size_t n)
{
    int  rc;

    while (*s1 && *s2 && (*s1 == *s2) && n > 1) {
        s1++, s2++, n--;
    }

    rc = *(unsigned char *) s1 - *(unsigned char *) s2;

    return rc % 2;
}

void
test_strnlen(strnlen_fn fn, const char *s)
{
    size_t  n, r;
    size_t  eq, gt, lt;

    n = strlen(s);

    eq = n;
    r = fn(s, eq);
    ASSERT(r == eq);
    printf("strnlen | n = %zu, eq = %zu, r = %zu: %s\n", n, eq, r, s);

    lt = n - 1;
    r = fn(s, lt);
    ASSERT(r == lt);
    printf("strnlen | n = %zu, lt = %zu, r = %zu: %s\n", n, lt, r, s);

    gt = n + 1;
    r = fn(s, gt);
    ASSERT(r < gt);
    printf("strnlen | n = %zu, gt = %zu, r = %zu: %s\n", n, gt, r, s);
}

void
test_strncpy(strncpy_fn fn, char *src)
{
    char    *dst  =  0;
    char    *d    =  0;
    size_t   n, r;
    size_t   eq, gt, lt;

    n = strlen(src);
    dst = malloc(n + 1);
    fill_str(dst, '_', n);

    eq = n;
    d = fn(dst, src, n);
    ASSERT(d == dst);
    r = strlen(d);
    printf("strncpy | n = %zu, eq = %zu, r = %zu: %s, %s\n",
           n, eq, r, src, dst);

    lt = n - 1;
    d = fn(dst, src, lt);
    ASSERT(dst[lt] != 0);
    dst[n] = 0;
    r = strlen(d);
    printf("strncpy | n = %zu, lt = %zu, r = %zu: %s, %s\n",
           n, lt, r, src, dst);

    gt = n + 1;
    d = fn(dst, src, gt);
    ASSERT(dst[gt - 1] == 0);
    r = strlen(d);
    printf("strncpy | n = %zu, gt = %zu, r = %zu: %s, %s\n",
           n, gt, r, src, dst);

    free(dst);
}

void
test_strncmp(strncmp_fn fn, const char *s1, const char *s2)
{
    int     r;
    size_t  n, n1, n2;
    size_t  eq, gt, lt;

    n1 = strlen(s1);
    n2 = strlen(s2);
    n = n1 < n2 ? n1 : n2;

    eq = n;
    r = fn(s1, s2, eq);
    ASSERT(r == 0);
    printf("strncmp | n = %zu, eq = %zu, r = %02i: %s, %s\n",
           n, eq, r, s1, s2);

    lt = n - 1;
    r = fn(s1, s2, lt);
    printf("strncmp | n = %zu, lt = %zu, r = %02i: %s, %s\n",
           n, lt, r, s1, s2);

    gt = n + 1;
    r = fn(s1, s2, gt);
    printf("strncmp | n = %zu, gt = %zu, r = %02i: %s, %s\n",
           n, gt, r, s1, s2);
}

void
fill_str(char *dst, char c, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        dst[i] = c;
    }

    dst[n] = 0;
}


int
main(int argc, char **argv)
{
    char  *s1, *s2;

    if (argc < 3) {
        printf("where the lhs and rhs strings\n");
        return 0;
    }

    s1 = argv[1];
    s2 = argv[2];

#if (NM_HAVE_STRNLEN)
    printf("----------\n");
    test_strnlen(strnlen, s1);

#endif  /* NM_HAVE_STRNLEN */

    printf("----------\n");
    test_strnlen(self_strnlen, s1);


#if (NM_HAVE_STRNCPY)
    printf("----------\n");
    test_strncpy(strncpy, s1);

#endif  /* NM_HAVE_STRNCPY */

    printf("----------\n");
    test_strncpy(self_strncpy, s1);


#if (NM_HAVE_STRNCMP)
    printf("----------\n");
    test_strncmp(strncmp, s1, s2);

#endif  /* NM_HAVE_STRNCMP */

    printf("----------\n");
    test_strncmp(self_strncmp, s1, s2);

    return 0;
}
