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

#elif defined(WINNT)
#define WIN32_LEAN_AND_MEAN
#include <malloc.h>
#include <windows.h>

	DWORD buffer_size = 0;
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION *buffer = 0;

	GetLogicalProcessorInformation(0, &buffer_size);
	buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)malloc(buffer_size);
	GetLogicalProcessorInformation(&buffer[0], &buffer_size);

	for (DWORD i = 0; i != buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); ++i) {
		if (buffer[i].Relationship == RelationCache && buffer[i].Cache.Level == 1) {
			size = buffer[i].Cache.LineSize;
			break;
		}
	}
	free(buffer);

#endif

	return size;
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	printf("cache line size: %zu\n", cache_line_size());
}

