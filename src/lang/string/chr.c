#include <_lang_.h>
#include <string.h>
#include <stdio.h>


/* #if (MSVC) */
/* #pragma warning(disable : 4996) */
/* #endif  /\* MSVC *\/ */


typedef char *(*strchr_fn)(const char *s, int);
typedef char *(*strrchr_fn)(const char *s, int);


static char *self_strchr(const char *s, int);
static char *self_strrchr(const char *s, int);

static void test_strchr(strchr_fn, char *s, int);


void
test_strchr(strchr_fn fn, char *ss, int c)
{
    char  *s1;

    s1 = fn(ss, c);
    if (s1) {
        fprintf(stdout, "%s\n", s1);

    } else {
        fprintf(stdout, "%c: no found\n", c);
    }
}

char *
self_strchr(const char *s, int c)
{
    while (*s) {
        if (c == *s) {
            return (char *) s;
        }
        s++;
    }
    return 0;
}

char *
self_strrchr(const char *s, int c) {
    const char  *pre  =  0;

    while (*s) {
        if (c == *s) {
            pre = s;
        }
        s++;
    }
    return (char *) pre;
}

int
main(int argc, char **argv)
{
    char  *ss;
    int    c;

    if (argc < 2) {
        printf("what string and found what\n");
        return 1;
    }

    ss = argv[1];
    c = argv[2][0];
  
    test_strchr(strchr, ss, c);
    test_strchr(strrchr, ss, c);
  
    test_strchr(self_strchr, ss, c);
    test_strchr(self_strrchr, ss, c);

    return 0;
}
