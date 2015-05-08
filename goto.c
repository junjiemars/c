#include <stdio.h>
#include <stdlib.h>

/*
 * 1) goto idiom for cleanning up
 */

int sum(int *v, size_t size) {
    int c = 0;

    for (int i = 0; i < size; i++) {
        if (v[i] < 0) goto clean_exit;
        c += v[i];
    }

clean_exit:
    free(v);
    return c;
}

int main(int argc, char *argv[]) {
    size_t size = 10;
    int *v = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i<size; i++) {
        v[i] = i;
    }
    v[6] = -1;
    printf("sum of v[] is %i\n", sum(v, size));
}
