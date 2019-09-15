#include <_cpu_.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#if ( MSVC )
#  include <intrin.h>
#  pragma warning(disable : 4996)
#endif

static int
check_cpuid(uint32_t fn, uint32_t *buf) {

#if ( MSVC )

	__cpuid((int32_t*) buf, fn);
	return 1

#elif ( __amd64__ ) || ( __x86_64__ )

	uint32_t eax, ebx, ecx, edx;
	__asm__ (
		  "cpuid"
			: "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
			: "a" (fn) );

	buf[0] = eax;
	buf[1] = ebx;
	buf[2] = ecx;
	buf[3] = edx;
	return 1;

#else
	
	_unused_(fn);
	_unused_(buf);
	return 0;
	
#endif
}

static char *
cpu_vendor(const uint32_t *cpuid, char *vendor) {
	const size_t w = sizeof(uint32_t);
	char *p = (char *) vendor;

	/* ebx, edx, ecx */
	strncpy(p, (const char *) &cpuid[1], w);
	strncpy(p += w, (const char *) &cpuid[3], w);
	strncpy(p += w, (const char *) &cpuid[2], w);

	return vendor;
}

static void
test_cpu_vendor(void) {
	uint32_t buf[5];
	memset(buf, 0, sizeof(buf)/sizeof(*buf));
	
	if (check_cpuid(0, buf)) {
		char vendor[sizeof(uint32_t)*3 + 1];
		printf("vendor: %s\n", cpu_vendor(buf, vendor));
	}
}


int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	/* vendor */
	test_cpu_vendor();

	return 0;
}
