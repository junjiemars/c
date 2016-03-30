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
    double y = x;
    printf("is x = set_na() NA? %i\n", is_na(x));
    printf("is x = set_na() NAN? %i\n", isnan(x));
    printf("is y = x NA? %i\n", is_na(y));
    printf("is 0/0 NA? %i\n", is_na(0/0.));
    printf("is 8 NA? %i\n", is_na(8));

    return 0;
}
