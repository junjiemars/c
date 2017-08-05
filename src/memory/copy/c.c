#include <_memory_.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void 
copy() {
    char d[16] = {0};
    char *s = "abc123";
    printf("s=%s memcpy(d,s)=%s\n",s ,(char*)memcpy(d, s, strlen(s)));
}

void 
move() {
    char s[] = "abc123";
    printf("s=%s strlen(s)=%zu memmove(s,s)=%s\n"
            ,s
            ,strlen(s)
            ,(char*)memmove(&s[2], s, strlen(s)/2));
}

int 
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	copy();
	move();
}
