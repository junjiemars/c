#include <assert.h>
#include <string.h>

int main(int argc, char *argvp[]) {
    int abc[] = { 0, 1, 2};
    int *copy0, copy1[3];
    copy0 = abc;
    memcpy(copy1, abc, sizeof(abc));

    abc[0] = 3;
    assert(copy0[0] == 3);
    assert(copy1[0] == 0);

    return 0;
}
