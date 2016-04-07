/* Compile with:
export CFLAGS="-g -Wall -std=gnu11 -O3"  #the usual.
make getenv

#Sample usage
reps=10 msg="Ha" ./getenv
msg="Ha" ./getenv
reps=20 msg=" " ./getenv
*/
#include <stdlib.h> //getenv, atoi
#include <stdio.h>  //printf

int main(){
    char *c = getenv("COUNT");
    int count = c ? atoi(c) : 3;

    char *text = getenv("TEXT");
    if (!text)text = "Hello.";

    for (int i=0; i< count; i++)
        printf("%s\n", text);
}
