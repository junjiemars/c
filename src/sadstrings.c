/* Compile with:
make sadstrings CFLAGS="-g -Wall -std=gnu11 -O3"
*/

/*
 * note:
 * 1)calling the system function has problem at line:23
 * 2)fixed line:23, the first argument of argv is the name of program itself
 * 3)searching itself may be the what the author want to do
 */

#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h> //malloc, free, system

void get_strings(char const *in){
    char *cmd;
    int len = strlen("strings ") + strlen(in);
    cmd = (char*)malloc(len+1);
    int copied_length = snprintf(cmd, len+1, "strings %s", in);
    printf("copied_length=%i len=%i cmd=%s\n", copied_length, len, cmd);
    if (len == copied_length) {
        system("strings sadstrings.c");
        if (system(cmd)) printf("something went wrong running %s.\n", cmd);
    }
    free(cmd);
}

int main(int argc, char **argv){
    get_strings(argc > 1 ? argv[1] : argv[0]);
    return (0);
}
