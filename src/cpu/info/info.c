#include <_cpu_.h>

#if defined (LINUX)
#  include <stdio.h>
#elif defined (DARWIN)
#  include <sys/sysctl.h>
#elif defined (WINNT)
#  include <windows.h>
#endif

#include <string.h>
#include <stdio.h>

typedef struct cpu_s {
	char machine[64];
	int byte_order;
	int ncpu;
	size_t cache_line_size;
} cpu_s;


cpu_s *
lscpu(cpu_s *cpu) {

#if defined (LINUX)
	FILE *f = fopen("/sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size", "r");
	if (f) {
		fscanf(f, "%zu", &cpu->cache_line_size);
		fclose(f);
	}
	
#elif defined (DARWIN)
	size_t size = 0;

	sysctlbyname("hw.machine", 0, &size, 0, 0);
	sysctlbyname("hw.machine", cpu->machine, &size, 0, 0);

	size = sizeof(cpu->byte_order);
	sysctlbyname("hw.byteorder", &cpu->byte_order, &size, 0, 0);

	size = sizeof(cpu->cache_line_size);
	sysctlbyname("hw.cachelinesize", &cpu->cache_line_size, &size, 0, 0);

#elif defined (WINNT)
	DWORD buffer_size = 0;
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION *buffer = 0;

	GetLogicalProcessorInformation(0, &buffer_size);
	buffer = malloc(buffer_size);
	GetLogicalProcessorInformation(&buffer[0], &buffer_size);

	for (DWORD i = 0; i != buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); ++i) {
		if (buffer[i].Relationship == RelationCache && buffer[i].Cache.Level == 1) {
			cpu->cache_line_size = buffer[i].Cache.LineSize;
			break;
		}
	}
	free(buffer);

#endif

	return cpu;
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	cpu_s cpu;
	memset(&cpu, 0, sizeof(cpu));

	lscpu(&cpu);

	printf("Architecture: %s\n", cpu.machine);
	printf("Byte Order: %s\n", 
				 (1234 == cpu.byte_order ? "Little Endian" : "Big Endian"));
	printf("Cache Line Size: %zu\n", cpu.cache_line_size);
}

