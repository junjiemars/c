#include <_lang_.h>
#include <stdio.h>

/*
 * note:
 * 1)'#' convert expression to string
 * 2)'%g' format double
 * 3) the length of pointer just equals sizeof(int)
 *
 */

#define peval(expr) printf(#expr ": %zu\n", expr);

int main(){
    peval(sizeof(double));
    peval(sizeof(int));
    /* double *plist = (double[]){1, 2, 3}; */
    double list[] = {1, 2, 3};
    /* peval(sizeof(plist)/(sizeof(double))); */
    peval(sizeof(list)/(sizeof(double)));
}
