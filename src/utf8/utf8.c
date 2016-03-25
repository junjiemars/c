#include <stdio.h>
#include <locale.h>

/*
 * [Linux Unicode programming](http://www.ibm.com/developerworks/library/l-linuni/)
 * [The Absolute Minimum Every Software Developer Absolutely, Positively Must Know About Unicode and Character Set](http://www.joelonsoftware.com/articles/Unicode.html)
 * [UTF-8](https://en.wikipedia.org/wiki/UTF-8)
 */

int main(int argc, const char *argv[]) {
    printf("Helloi, unicode:%c\n", 0x0024);
    unsigned char u2[] = {0xc2, 0xa2, 0};
    printf("%s\n", u2);
    unsigned char u3[] = {0xe2, 0x82, 0xac, 0};
    printf("%s\n", u3);
    unsigned char u4[] = {0xf0, 0x90, 0x8d, 0x88, 0};
    printf("%s\n", u4);

    return 0;
}
