#include <stdio.h>
#include <math.h>

double ref;

double set_na(){
    if (!ref) {
        ref = 0/0.;
        char *cr = (char *)(&ref);
        cr[2]='a';
    }
    return ref;
}

int is_na(double in){
    if (!ref) return 0;  //set_na was never called==>no NAs yet.

    char *cc = (char *)(&in);
    char *cr = (char *)(&ref);
    for (int i=0; i< sizeof(double); i++)
        if (cc[i] != cr[i]) return 0;
    return 1;
}

int main(){
    double x = set_na();
    printf("8 is not a number = %i\n", is_na(8));
    printf("0/0. is not a number = %i\n", isnan(0/0.));
    printf("nan spec: 0x%08x\n", *(unsigned int*)&x);
    printf("0x%08x is not a number = %i, via self:is_na\n", *(unsigned int*)&x, is_na(x));
    printf("0x%08x is not a number = %i, via stdc:isnan\n", *(unsigned int*)&x, isnan(x));

    return 0;
}
