#include <stdio.h>
#include <getopt.h>

static struct option longopts[] = {
    {"help",    no_argument,    0,      'h'},
    {"ctypes",  no_argument,    0,      'w'},
    {"raw",     no_argument,    0,      'n'},
    {0,         0,              0,      0}
};

static void usage(const char *p) {
    printf("usage %s\n", p);
    printf("  -h, --help\t\tthis help text\n");
    printf("  -w, --ctypes\t\tinvoke c lib via ctypes\n");
    printf("  -n, --native\t\tinvoke raw c code\n");
}

static void ctypes() {
    printf("hello, ctypes\n");
}

static void raw() {
    printf("hello, raw\n");
}

int main(int argc, char * const argv[]) {
    int ch;
    while (-1 != (ch = getopt_long(argc, argv, "hwn", longopts, 0))) {
        switch (ch) {
            case 'w':
                ctypes();
                goto exit;
            case 'n':
                raw();
                goto exit;
            case 'h':
            default:
                usage(argv[0]);
                goto exit;
        }
    }

    printf("%s: try '%s --help' for more information\n", argv[0], argv[0]);

exit:
    return 0;
}
