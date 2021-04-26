#include <_ld_.h>
#include <stdio.h>


#define SS "enter _start ...\n"


void
_start(void)
{
    printf(SS);

    __asm__("mov $60, %rax;"
            "mov  $0, %rdi;"
            "syscall");
}
