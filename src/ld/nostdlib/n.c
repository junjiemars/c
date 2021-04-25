#include <_ld_.h>

void
_start(void)
{
    __asm__("mov $60,%rax;"
            "mov $0,%rdi;"
            "syscall");
}
