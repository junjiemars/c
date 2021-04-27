#include <_ld_.h>

#if (__x86_64__)
#define sys_exit()                                                           \
    __asm__("mov $60, %rax;"                                                 \
            "mov  $0, %rdi;"                                                 \
            "syscall")

#elif (__aarch64__)
#define sys_exit()                                                           \
    __asm__("mov x0, #0;"                                                    \
            "mov x8, #93;"                                                   \
            "svc #0")
#endif

void
_start(void)
{
    sys_exit();
}
