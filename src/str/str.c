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

int main(int argc, const char *argv[]) {
    str_len();
    str_copy();
    return 0;
}
