#include <_cpu_.h>
#include <stdint.h>
#include <string.h>


static void
check_cpuid(uint32_t i, uint32_t *buf) {
	uint32_t eax, ebx, ecx, edx;

	__asm__ (
		  "cpuid"
			: "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
			: "a" (i) );

	buf[0] = eax;
	buf[1] = ebx;
	buf[2] = edx;
	buf[3] = ecx;
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	uint32_t vbuf[5];
	memset(vbuf, 0, sizeof(vbuf)/sizeof(*vbuf));
	
	check_cpuid(0, vbuf);
	
	return 0;
}
