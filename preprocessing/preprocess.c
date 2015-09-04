/* Compile with:
export CFLAGS="-g -Wall -std=gnu11 -O3"  #the usual.
make preprocess
*/

/*
 * 1) ## operator used to concate two identifiers in macro.
 * 2) u can define macro anywhere but avaiable after the defined point.
 * 3) varidic arguments
 */

#include <stdio.h>
#include <math.h> //NAN

#define setup_list(name, ...)                               \
    double *name ## _list = (double []){__VA_ARGS__, NAN};  \
    int name ## _len = 0;                                   \
    for (name ## _len =0;                                   \
            !isnan(name ## _list[name ## _len]);            \
            ) name ## _len ++;


int main(){
    setup_list(items, 1, 2, 4, 8);
    double sum=0;
    for (double *ptr= items_list; !isnan(*ptr); ptr++)
        sum += *ptr;
    printf("total for items list: %g\n", sum);

    //#define Length(in) in ## _len

    setup_list(another, -1, 2.2, 4.8, 0.1);
    for (int i=0, sum=0; i < another_len; i++)
        sum += another_list[i];
    printf("total for another list: %g\n", sum);
}
