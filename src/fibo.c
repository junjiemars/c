/* Compile with:
make fibo CFLAGS="-g -Wall -std=gnu11 -O3"
*/
#include <stdio.h>

/*
 * 1) if function exists then static vars in which exists;
 * 2) C11 include a _Thread_local memory type for thread safe reson;
 * 3) static vars initialized before main;
 */

long long int fibonacci(){
    static /*_Thread_local*/ long long int first = 0;
    static /*_Thread_local*/ long long int second = 1;
    long long int out = first+second;
    first=second;
    second=out;
    return out;
}

int main(){
    for (int i=0; i< 50; i++)
        printf("%lli\n", fibonacci());
}
