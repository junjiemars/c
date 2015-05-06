/* Compile with
make arithmetic CFLAGS="-g -Wall -std=gnu11 -O3"
*/
#include <stdio.h>

/*
 * 1) automatic pointer main::evens
 */

int main(){
    // the evens is an automatic pointer
    int evens[5] = {0, 2, 4, 6, 8};

    // so *evens == evens[0], the first element == the pointer begins
    printf("The first even number is, of course, %i\n", *evens);

    int *positive_evens = &evens[1];
    printf("The first positive even number is %i\n", positive_evens[0]);
}


