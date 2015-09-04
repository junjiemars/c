#include <stdio.h>
#include <string.h>

/*
 * 1) expression-type macro: parens or avoid double usage
 * 2) block-type macro
 * 3) use: cc -E macro.c just to run preprocessor
 */

#define double0(x) 2*x
#define double1(x) (2*(x))

#define max(a, b) ((a) > (b) ? (a) : (b))

#define need_blocked(a, b)      \
    (a)++;                      \
    (b)++;

#define sum(max, out) {         \
    int total = 0;              \
    for (int i=0; i<max; i++)   \
        total += i;             \
    out = total;                \
}

#define check_blank(a) {                            \
    int v = (strlen(#a)>0) ?(a+0) : 2;              \
    printf("I understand ur input to be %i.\n", v); \
}

#define test(assertion, retvaql) {                               \
    if (!(assertion)) {                                         \
        fprintf(stderr, "(" #assertion ") failed to be true."   \
                "returning " #retval "\n");                     \
        return retval;                                          \
    }                                                           \
}



int main(int argc, char *argv[]) {
    printf("double0(1+1)*8=%i\n", double0(1+1)*8);
    printf("double1(1+1)*8=%i\n", double1(1+1)*8);

    int a = 1, b = 2;
    printf("max(a,b++)=%i\n", max(a,b++));
    if (a < b) need_blocked(a, b);

    int total = 5, out;
    sum(5, out);
    printf("out=%i original total=%i\n", out, total);

    check_blank(0);
    check_blank();

    test(a==b, -1);
    // can't run in cc
    //test(a==b,   );
}
