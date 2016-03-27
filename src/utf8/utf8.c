#include <stdio.h>
#include <locale.h>

#define TO_BASE_N (sizeof(unsigned)*8 + 1)
#define TO_BASE(n, b) to_base((unsigned char [TO_BASE_N]){""}, (n), (b))

const unsigned char *to_base(unsigned char *o, unsigned i, unsigned base) {
    unsigned char *s = &o[TO_BASE_N - 1];
    *s = '\0';
    do {
        s--;
        *s = "0123456789ABCDEF"[i % base];
        i /= base;
    } while (i);

    return s;
}

void out(const char *s, unsigned c) {
    if (c < 0x80) {
        printf("%s: 0x%08x %s\n", s, c, TO_BASE(c, 2));
    } else if (c < 0x0080) {
        printf("%s: 0x%08x %s\n", s, c, TO_BASE(c, 2));
    } else if (c < 0x0800) {
        // need character to utf8 encoding
    }
}

int main(int argc, const char *argv[]) {
    out("$", 0x0024u);
    out("00a2", 0x00a2u);
    unsigned char u2[] = {0xc2, 0xa2, 0};
    printf("%s\n", u2);
    unsigned char u3[] = {0xe2, 0x82, 0xac, 0};
    printf("%s\n", u3);
    unsigned char u4[] = {0xf0, 0x90, 0x8d, 0x88, 0};
    printf("%s\n", u4);

    return 0;
}
