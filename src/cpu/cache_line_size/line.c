#include <_cpu_.h>

#if defined(LINUX)
#  include <stdio.h>
#elif defined(DARWIN)
#  include <sys/sysctl.h>
#elif defined (WINNT)
#  include <windows.h>
#endif

#include <stdio.h>

size_t
cache_line_size() {
	size_t line_size = 0;

#if defined(LINUX)
	FILE *f = fopen("/sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size", "r");
	if (f) {
		fscanf(f, "%zu", &line_size);
		fclose(f);
	}
	
#elif defined(DARWIN)
	size_t sizeof_line_size = sizeof(line_size);
	sysctlbyname("hw.cachelinesize", &line_size, &sizeof_line_size, 0, 0);

#elif defined(WINNT)
	DWORD buffer_size = 0;
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION *buffer = 0;

	GetLogicalProcessorInformation(0, &buffer_size);
	buffer = malloc(buffer_size);
	GetLogicalProcessorInformation(&buffer[0], &buffer_size);

	for (DWORD i = 0; i != buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); ++i) {
		if (buffer[i].Relationship == RelationCache && buffer[i].Cache.Level == 1) {
			line_size = buffer[i].Cache.LineSize;
			break;
		}
	}
	free(buffer);

#endif

	return line_size;
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	printf("cache line size: %zu\n", cache_line_size());
}

