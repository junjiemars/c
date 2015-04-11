/* Compile with:
make sizesof CFLAGS="-g -Wall -std=gnu11 -O3"
*/
#include <stdio.h>

/*
 * note:
 * 1)'#' convert expression to string
 * 2)'%g' format double?
 * 3) the point length just equals sizeof(int)
 *
 */

#define peval(cmd) printf(#cmd ": %g\n", cmd);

int main(){
    peval(sizeof(double)+0.0);
    peval(sizeof(int)+0.0);
    double *plist = (double[]){1, 2, 3};
    double list[] = {1, 2, 3};
    peval(sizeof(plist)/(sizeof(double)+0.0));
    peval(sizeof(list)/(sizeof(double)+0.0));
}
