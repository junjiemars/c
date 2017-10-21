#include <_str_.h>
#include <stdio.h>
#include <string.h>

void str_len() {
    char *s[] = {"abc123", "abc123中文", 0};
    char **i = s;
    while (*i) {
        printf("strlen(%s) = %lu\n", *i, strlen(*i));
        i++;
    }
}

void str_copy() {
    char s[16] = "abc123";
    char d[16] = {0};
    printf("s = %s strlen(s) = %lu\n", s, strlen(s));
    printf("strncpy(d, s, %lu) = %s\n", sizeof(s), strncpy(d, s, sizeof(s)));
}

void str_cat() {
    char d[16] = "abc123";
    char s[16] = "def";
    printf("d = %s strlen(d) = %lu sizeof(d) = %lu\n",
           d, strlen(d), sizeof(d));
    printf("s = %s strlen(s) = %lu sizeof(s) = %lu\n",
           s, strlen(s), sizeof(s));

    if (strlen(d) + 1 <= sizeof(s) + strlen(s)) {
        char *n = strncat(d, s, sizeof(s) - strlen(s) - 1);
        printf("n = %s strlen(n)=%lu sizeof(n) = %lu\n",
               n, strlen(n), sizeof(d));
    }
}

void str_chr() {
     const char *s = "abc123";
     printf("strchr(s, %c) = %s\n", 'b', strchr(s, 'b'));
     printf("strchr(s, %c) = %s\n", '\0', strchr(s, '\0'));
}


void str_cmp() {
    const char *l = "abc123";
    const char *r = "abc1234";
    const char *r1 = "abc122";
    printf("strcmp(%s, %s) = %i\n", l, r, strcmp(l, r));
    printf("strcmp(%s, %s) = %i\n", l, r1, strcmp(l, r1));
}

int 
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

    str_len();
    str_copy();
    str_cat();
    str_chr();
    str_cmp();
    return 0;
}
