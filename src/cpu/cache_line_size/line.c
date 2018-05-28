#include <_cpu_.h>
#include <stdio.h>

size_t
cache_line_size() {
	size_t size = 0;

#if defined(LINUX)
	FILE *f = fopen("/sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size", "r");
	if (f) {
		fscanf(f, "%zu", &size);
		fclose(f);
	}
	
#elif defined(DARWIN)
	#include <sys/sysctl.h>
	size_t size_of = sizeof(size);
	sysctlbyname("hw.cachelinesize", &size_of, &, 0, 0);
#endif

	return size;
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	printf("cache line size: %zu\n", cache_line_size());
}

