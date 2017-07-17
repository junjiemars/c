/* Compile with:
make sizesof CFLAGS="-g -Wall -std=gnu11 -O3"
*/
#include <stdio.h>

/*
 * note:
 * 1)'#' convert expression to string
 * 2)'%g' format double
 * 3) the length of pointer just equals sizeof(int)
 *
 */

#define peval(expr) printf(#expr ": %lu\n", expr);

int main(){
    peval(sizeof(double));
    peval(sizeof(int));
    double *plist = (double[]){1, 2, 3};
    double list[] = {1, 2, 3};
    peval(sizeof(plist)/(sizeof(double)));
    peval(sizeof(list)/(sizeof(double)));
}
