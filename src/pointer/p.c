#include <stdio.h>

int main(){
    char *list[] = {"first", "second", "third", NULL/*must has*/};
    for (char **p=list; *p != NULL; p++){
        printf("%s\n", p[0]);
    }
}
