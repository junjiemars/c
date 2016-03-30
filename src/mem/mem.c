#include <stdio.h>
#include <string.h>

void mem_cpy() {
    char d[16] = {0};
    char *s = "abc123";
    printf("s = %s memcpy(d, s) = %s\n", s, (char*)memcpy(d, s, strlen(s)));
}

void mem_move() {
    char s[] = "abc123";
    printf("s = %s strlen(s) = %lu memmove(s, s) = %s\n"
            , s
            , strlen(s)
            , (char*)memmove(&s[2], s, strlen(s)/2));
}

int main(int argc, const char *argv[]) {
    mem_cpy();
    mem_move();
    return 0;
}
