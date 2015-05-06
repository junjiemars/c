#include <stdio.h>

/*
 * A. automatic variables:
 * 1) automatic variables includes global_auto_i0/i1, i0/i1;
 * 2) uninitialized variables will be set to 0;
 */

int global_auto_i0 = 123;
int global_auto_i1;
static int file_scope_i0 = 345;
static int file_scope_i1;

int main(int argc, char *argv[]) {
    int i0 = 123;
    int i1;
    static int static_i0 = 234;
    static int static_i1;

    printf("i0=%i i1=%i\n", i0, i1);
    printf("global_auto_i0=%i global_auto_i1=%i\n", global_auto_i0, global_auto_i1);
    printf("static_i0=%i static_i1=%i\n", static_i0, static_i1);
    printf("file_scope_i0=%i file_scope_i1=%i\n", file_scope_i0, file_scope_i1);

    return 0;
}
